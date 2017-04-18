#include "Montecarlo.h"
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

Montecarlo::Montecarlo(const Grid& grid,int nbFlechette){
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
    this->M = 1;
    this->a = (float) -1;
    this->b = (float) 1;

    Device::malloc(&ptrDevResult, sizeOctetGM);
    Device::memclear(ptrDevResult, sizeOctetGM);

    Device::malloc(&ptrTabDevGenerator, sizeOctetGeneratorGM);
    Device::memclear(ptrTabDevGenerator, sizeOctetGeneratorGM);

    int deviceId = Device::getDeviceId();

    setup_kernel_rand<<<dg, db>>>(ptrTabDevGenerator, deviceId);//a check pour ce qui est entre les triples chevrons
}

Montecarlo::~Montecarlo(void){
    Device::free(ptrDevResult);
    Device::free(ptrTabDevGenerator);
}

void Montecarlo::run(){
    montecarlo<<<dg, db, sizeOctetSM>>>(ptrDevResult, ptrTabDevGenerator, nbFlechette, a, b, M);
    Device::memcpyDToH(&nbFlechetteDessous, ptrDevResult, sizeOctetGM);
    float delta = fabs(b-a);
    float area = M*delta;
    float ratio = nbFlechetteDessous/nbFlechette;
    this->result = 2*area*ratio;
}

float Montecarlo::getResult(){
    return this->result;
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

