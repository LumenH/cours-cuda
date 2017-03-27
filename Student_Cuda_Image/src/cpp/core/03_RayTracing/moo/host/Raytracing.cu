#include <iostream>
#include <assert.h>

#include "Raytracing.h"
#include "SphereCreator.h"
#include "Device.h"

#include "length_cm.h"

using std::cout;
using std::endl;


//Global memory part
extern __global__ void raytracing(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrDevTabSphere, int nbSphere);
extern __host__ void uploadGPU(Sphere* tabValue);
extern __global__ void raytracingGM(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrDevTabSphere, int nbSphere);
extern __global__ void raytracingCM(uchar4* ptrDevPixels, uint w, uint h, float t, int nbSphere);
extern __global__ void raytracingSM(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrDevTabSphere, int nbSphere);
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
    uploadGPU(ptrTabSphere);
}

void Raytracing::toGM(Sphere* ptrTabSphere){
   Device::malloc(&ptrDevTabSphere, sizeOctet);
   Device::memclear(ptrDevTabSphere, sizeOctet);
   Device::memcpyHToD(ptrDevTabSphere, ptrTabSphere, sizeOctet);

}

void Raytracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath){
    static int i=0;
    //Device::lastCudaError("Before raytracing");
    if (i%3 == 0){
	raytracingGM<<<dg, db>>>(ptrDevPixels, w, h, t, ptrDevTabSphere, nbSphere);
    }
    else if (i%3 == 1){
	raytracingCM<<<dg, db>>>(ptrDevPixels, w, h, t, nbSphere);
    }
    else if (i%3 == 2){
	raytracingSM<<<dg, db, sizeOctet>>>(ptrDevPixels, w, h, t, ptrDevTabSphere, nbSphere);
    }
    //Device::lastCudaError("After raytracing");
    i++;

    //Ajouter barriere synchro implicite
}



Raytracing::~Raytracing(){
    Device::free(ptrDevTabSphere);
}

void Raytracing::animationStep(){
    t += dt;
}


