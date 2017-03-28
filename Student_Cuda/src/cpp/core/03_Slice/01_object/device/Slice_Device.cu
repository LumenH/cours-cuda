#include "Indice1D.h"
#include "cudaTools.h"
#include "reductionADD.h"


__global__ void slice(float* ptrDevResult, int nbSlice);
static __device__ void reductionIntraThread(float* tabSM, int nbSlice);

__global__ void slice(float* ptrDevResult, int nbSlice){
    __shared__ extern float tabSM[];
    reductionIntraThread(tabSM, nbSlice);
    __syncthreads();//barrière pour les threads d'un même bloc
    reductionADD<float>(tabSM, ptrDevResult);//méthode générique
}

static __device__ void reductionIntraThread(float* tabSM, int nbSlice){
    const int TID_Local = threadIdx.x;
    tabSM[TID_Local] = threadIdx.x + blockIdx.x*blockDim.x; //On remplit de 1.
}
