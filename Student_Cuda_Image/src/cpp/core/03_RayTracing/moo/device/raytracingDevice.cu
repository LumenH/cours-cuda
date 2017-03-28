#include "cudaTools.h"
#include "Indice2D.h"

#include "IndiceTools_GPU.h"
#include "RaytracingMath.h"

#include "length_cm.h"

using namespace gpu;
__constant__ Sphere TAB_CM[LENGTH_CM];

__device__ void work(uchar4* ptrDevPixels, Sphere* ptrDevTabSphere, int nbSphere, const int NB_THREAD, const int TID, uint w, uint h, float t){
    RaytracingMath rm = RaytracingMath(ptrDevTabSphere, nbSphere);
    const int WH = w*h;
    int s = TID;
    int i, j;

    while(s < WH){
	IndiceTools::toIJ(s, w, &i,  &j);
	rm.colorIJ(&ptrDevPixels[s], i, j, t);
	s += NB_THREAD;
    }
}

__global__ void raytracingGM(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrDevTabSphere, int nbSphere){

    const int NB_THREAD = Indice2D::nbThread();
    const int TID = Indice2D::tid();

    work(ptrDevPixels, ptrDevTabSphere, nbSphere, NB_THREAD, TID, w, h, t);
}

__global__ void raytracingCM(uchar4* ptrDevPixels, uint w, uint h, float t, int nbSphere){

    const int NB_THREAD = Indice2D::nbThread();
    const int TID = Indice2D::tid();

    work(ptrDevPixels, TAB_CM, nbSphere, NB_THREAD, TID, w, h, t);
}

__global__ void raytracingSM(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrDevTabSphere, int nbSphere){
    extern __shared__ Sphere ptrDevTabSphereSM[];

    //Attention changement TID et NB_THREAD
    const int NB_THREAD_Local = Indice2D::nbThreadLocal();
    const int TID_Local = Indice2D::tidLocal();

    int s = TID_Local;
    while(s < nbSphere){
	ptrDevTabSphereSM[s] = ptrDevTabSphere[s];
	s++;
    }

    work(ptrDevPixels, ptrDevTabSphereSM, nbSphere, NB_THREAD_Local, TID_Local, w, h, t);
}


__host__ void uploadGPU(Sphere* tabValue){
    size_t size= LENGTH_CM *sizeof(Sphere);
    int offset=0;
    HANDLE_ERROR(cudaMemcpyToSymbol(TAB_CM, tabValue, size, offset, cudaMemcpyHostToDevice));
}

