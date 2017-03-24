#include <iostream>
#include <assert.h>

#include "Raytracing.h"
#include "SphereCreator.h"
#include "Device.h"

using std::cout;
using std::endl;

extern __global__ void raytracing(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrDevTabSphere, int nbSphere);

Raytracing::Raytracing(const Grid& grid, uint w, uint h, float dt, int nbSphere): Animable_I<uchar4>(grid, w, h, "Raytracing_CUDA"){
    this->dt = dt;
    this->t = 0;
    this->nbSphere = nbSphere;

    SphereCreator sphereCreator(nbSphere, w, h);
    Sphere* ptrTabSphere = sphereCreator.getTabSphere();

    this->sizeOctet = sizeof(Sphere)*nbSphere;

    //Transfert to Global Memory
    toGM(ptrTabSphere);

    //Transfert to CM
    //toCM(ptrTabSphere);
}

void Raytracing::toGM(Sphere* ptrTabSphere){
    Device::malloc(&ptrDevTabSphere, sizeOctet);
    Device::memclear(ptrDevTabSphere, sizeOctet);
    Device::memcpyHToD(ptrDevTabSphere, ptrTabSphere, sizeOctet);

}

void Raytracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath){
    //Device::lastCudaError("Before raytracing");
    raytracing<<<dg, db>>>(ptrDevPixels, w, h, t, ptrDevTabSphere, nbSphere);
    //Device::lastCudaError("After raytracing");

    //Ajouter barriere synchro implicite
}



Raytracing::~Raytracing(){
    Device::free(ptrDevTabSphere);
}

void Raytracing::animationStep(){
    t += dt;
}

