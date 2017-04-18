#include "MontecarloMultiGPU.h"
#include "Device.h"
#include "MontecarloMulti.h"

MontecarloMultiGPU::MontecarloMultiGPU(const Grid& grid, const int nbFlechetteTotale){
    this->nbDevice = Device::getDeviceCount();
    this->grid = grid;
    this->nbFlechetteTotale = nbFlechetteTotale;
    this->result = 0;
}

void MontecarloMultiGPU::runMulti(){
    int nbFlechetteGPU = nbFlechetteTotale/this->nbDevice;

    long sumTotal = 0;

    #pragma omp parallel for reduction(+:sumTotal)
    for(int idDevice = 0; idDevice < this->nbDevice; idDevice++){
	cudaSetDevice(idDevice);
	MontecarloMulti montecarlomulti(this->grid, nbFlechetteGPU);
	montecarlomulti.run();
	sumTotal += montecarlomulti.getNbFlechette();
    }

    //this->result = sumTotal;
    float delta = fabsf(-1.0f-1.0f);
    float area = 1.0f*delta;
    float ratio = (float)sumTotal/(float)nbFlechetteTotale;
    this->result = 2*area*ratio;
}

float MontecarloMultiGPU::getResult(){
    return this->result;
}

