#include "MontecarloMultiGPU.h"
#include "Device.h"
#include "MontecarloMulti.h"

MontecarloMultiGPU::MontecarloMultiGPU(const Grid& grid, const int nbFlechetteTotale){
    this->nbDevice = Device::getDeviceCount();
    this->grid = grid;
    this->nbFlechetteTotale = nbFlechetteTotale;
    this->result = 100;
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
 //il manque les formules de finition
}

float MontecarloMultiGPU::getResult(){
    return this->result;
}

