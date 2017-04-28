#include <iostream>

#include "Histogramme.h"
#include "Device.h"

const int SIZE_TAB_SM = 256;

extern __global__ void histogramme(int* ptrTabData, int sizeTab, int* ptrDevResult);

Histogramme::Histogramme(const Grid& grid, int sizeTab){

    this->datacreator = new DataCreator(sizeTab);
    this->ptrTabData = this->datacreator->getTabData();
    this->n = this->datacreator->getLength();

    this->ptrTabResult = new int[SIZE_TAB_SM];

    this->sizeOctet= sizeof(int)*this->n;
    this->sizeOctetResult = sizeof(int)*SIZE_TAB_SM;

    this->dg = grid.dg;
    this->db = grid.db;
    this->sizeTab = sizeTab;

    DataCreator dataCreator(SIZE_TAB_SM-1);

    Device::malloc(&ptrDevData, sizeOctet);
    Device::memclear(ptrDevData, sizeOctet);

    Device::malloc(&ptrDevResult, sizeOctetResult);
    Device::memclear(ptrDevResult, sizeOctetResult);

    Device::memcpyHToD(this->ptrDevData, this->ptrTabData, this->sizeOctet);

}

int* Histogramme::run(void){
    histogramme<<<dg, db, sizeOctetResult>>>(this->ptrDevData, this->n, this->ptrDevResult);
    Device::synchronize();
    Device::memcpyDToH(ptrTabResult, ptrDevResult, sizeOctetResult);
    return ptrTabResult;
}

Histogramme::~Histogramme(void){
    Device::free(ptrDevResult);
    Device::free(ptrDevData);
}
