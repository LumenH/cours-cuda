#include "MontecarloMulti.h"

#include "Device.h"
#include <curand_kernel.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

extern __global__ void montecarlo(int* ptrDevResult, curandState* ptrTabDevGenerator, int nbFlechette, float a, float b, float M);
extern __global__ void setup_kernel_rand(curandState* ptrTabDevGenerator, int deviceId);
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

MontecarloMulti::MontecarloMulti(const Grid& grid,int nbFlechette){
    this->sizeOctetGM = sizeof(int);
    this->sizeOctetSM = sizeof(int) * grid.db.x;
    this->sizeOctetGeneratorGM = sizeof(curandState) * grid.threadCounts();

    this->result = 0;
    this->nbFlechetteDessous = 0;
    this->nbFlechette = nbFlechette;

    this->ptrDevResult = NULL;
    this->ptrTabDevGenerator = NULL;

    this->dg = grid.dg;
    this->db = grid.db;

    this->a = (float) -1;
    this->b = (float) 1;
    this->M = 1.0f;

    Device::malloc(&ptrDevResult, sizeOctetGM);
    Device::memclear(ptrDevResult, sizeOctetGM);

    Device::malloc(&ptrTabDevGenerator, sizeOctetGeneratorGM);
    Device::memclear(ptrTabDevGenerator, sizeOctetGeneratorGM);

    int deviceId = Device::getDeviceId();

    setup_kernel_rand<<<dg, db>>>(ptrTabDevGenerator, deviceId);//a check pour ce qui est entre les triples chevrons
}

MontecarloMulti::~MontecarloMulti(void){
    Device::free(ptrDevResult);
    Device::free(ptrTabDevGenerator);
}

void MontecarloMulti::run(){
    montecarlo<<<dg, db, sizeOctetSM>>>(ptrDevResult, ptrTabDevGenerator, nbFlechette, a, b, M);
    Device::memcpyDToH(&nbFlechetteDessous, ptrDevResult, sizeOctetGM);
    float delta = fabsf(b-a);
    float area = M*delta;
    float ratio = (float)nbFlechetteDessous/(float)nbFlechette;
    this->result = 2*area*ratio;
}

float MontecarloMulti::getResult(){
    return this->result;
}

int MontecarloMulti::getNbFlechette(){
    return this->nbFlechetteDessous;
}


/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

