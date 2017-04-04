#include "Montecarlo.h"
#include "Device.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

extern __global__ void montecarlo(float* ptrDevResult, curandState* ptrTabDevGenerator, int nbFlechette);
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

Montecarlo::Montecarlo(const &Grid grid, float* ptrResult, int nbFlechette){
    this->sizeOctetGM = sizeof(float);
    this->sizeOctetSM = sizeof(float) * nbFlechette;//grid.db.x;
    this->sizeOctetGeneratorGM = sizeof(curandState) * grid.threadCounts();

    this->ptrDevResult = NULL;
    this->ptrResult = ptrResult;
    this->nbFlechette = nbFlechette;
    this->dg = grid.dg;
    this->db = grid.db;

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
    montecarlo<<<dg, db, sizeOctetSM>>(ptrDevResult, ptrTabDevGenerator, nbFlechette);
    Device::memcpyHToD(ptrDevResult, ptrResult, sizeOctetGM);
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

