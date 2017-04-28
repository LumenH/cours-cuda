#include <stdio.h>

#include "Indice2D.h"
#include "cudaTools.h"

__global__ void histogramme(int* ptrTabData, int sizeTab, int* ptrDevResult);
static __device__ void reductionIntraThread(int* ptrTabData, int sizeTab, int *tabSM);
__device__ void reductionInterBlock(int* TAB_SM, int* ptrGM);

__global__ void histogramme(int* ptrTabData, int sizeTab, int* ptrDevResult){
    extern __shared__ int tabSM[];

    if (Indice2D::tidLocal() == 0){
	for (int i = 0; i < 256; i++){
	    tabSM[i] = 0;
	}
    }

    __syncthreads();

    reductionIntraThread(ptrTabData, sizeTab, tabSM);
    __syncthreads();
    reductionInterBlock(tabSM, ptrDevResult);

}

__device__ void reductionInterBlock(int* tabSM, int* tabGM){
    if (Indice2D::tidLocal() == 0){
	for (int i = 0; i < 256; i++){
	    atomicAdd(&tabGM[i], tabSM[i]);
    	}
    }
}

__device__ void reductionIntraThread(int* ptrTabData, int sizeTab, int* tabSM){
    const int NB_THREAD = Indice2D::nbThread();
    const int TID_LOCAL = Indice2D::tidLocalBlock();
    const int TID = Indice2D::tid();

    int s = TID;

    while(s < sizeTab){
	atomicAdd(&tabSM[ptrTabData[s]], 1);
	s+= NB_THREAD;
    }
}
