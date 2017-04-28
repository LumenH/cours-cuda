#include "Indice1D.h"
#include "cudaTools.h"
#include "reductionADD.h"


__global__ void slice(float* ptrDevResult, int nbSlice);
static __device__ void reductionIntraThread(float* tabSM, int nbSlice);
__device__ float fpi(float x);

__global__ void slice(float* ptrDevResult, int nbSlice){
    __shared__ extern float tabSM[];
    reductionIntraThread(tabSM, nbSlice);
    __syncthreads();//barrière pour les threads d'un même bloc
    reductionADD<float>(tabSM, ptrDevResult);//méthode générique
}

static __device__ void reductionIntraThread(float* tabSM, int nbSlice){
    //const int TID_Local = threadIdx.x;

    const int NB_THREAD=Indice1D::nbThread();
    const int TID=Indice1D::tid();
    const int TID_LOCAL=Indice1D::tidLocal();
    const float DX = 1.f / (float) nbSlice;

    int s = TID;
    float tmp = 0;
    while(s < nbSlice)
    {
    	tmp += fpi(s * DX);
    	s += NB_THREAD;
    }

    tabSM[TID_LOCAL] = tmp * DX;
}

__device__ float fpi(float x)
{
    return 4.f / (1.f + x * x);
}
