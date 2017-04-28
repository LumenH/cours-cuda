#include "Slice.h"

#include "Device.h"

extern __global__ void slice(float* ptrDevRseult, int nbSlice);

Slice::Slice(const Grid& grid,float* ptrResult, int nbSlice){

    this->sizeOctetGM = sizeof(float);
    this->sizeOctetSM = sizeof(float) * grid.db.x;
    this->ptrDevResult = NULL;
    this->ptrResult = ptrResult;
    this->nbSlice = nbSlice;

    Device::malloc(&ptrDevResult, sizeOctetGM);
    Device::memclear(ptrDevResult, sizeOctetGM);

    this->dg = grid.dg;
    this->db = grid.db;
}

Slice::~Slice(){
    Device::free(ptrDevResult);
}

void Slice::run(){
    slice<<<dg, db, sizeOctetSM>>>(ptrDevResult, nbSlice);
    Device::memcpyDToH(ptrResult, ptrDevResult, sizeOctetGM);
}
