#include "Slice.h"

#include "Device.h"

extern __global__ void slice(float* ptrDevRseult, int nbSlice);

Slice::Slice(const Grid& grid,float* ptrResult, int n){
    this->sizeOctet = sizeof(float);
    this->ptrDevResult = NULL;

    {
	Device::malloc(&ptrDevResult, sizeOctet);
	Device::memclear(ptrDevResult, sizeOctet);
	Device::memcpyHToD(ptrDevResult, ptrResult, sizeOctet);

    }

    {
    this->dg = grid.dg;
    this->db = grid.db;
    }

    this->sizeOctetSM = sizeof(float)*db.x;//taille de float * nbThread
}

Slice::~Slice(){
    Device::free(ptrDevResult);
}

void Slice::run(){
    slice<<<dg, db, sizeOctetSM>>>(ptrDevResult, n);
}
