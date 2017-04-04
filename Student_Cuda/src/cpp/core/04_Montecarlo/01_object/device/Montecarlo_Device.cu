#include <curand_kernel.h>
#include <limits.h>
#include <Indice1D.h>
#include "reductionADD.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
__global__ void setup_kernel_rand(curandState* ptrTabDevGenerator, int deviceId);
static __device__ void reductionIntraThread(int* tabSM, int nbFlechette, curandState* ptrTabDevGenerator);
__global__ void montecarlo(int* ptrDevResult, curandState* ptrTabDevGenerator, int nbFlechette);
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void montecarlo(int* ptrDevResult, curandState* ptrTabDevGenerator, int nbFlechette){
    __shared__ extern int tabSM[];
    reductionIntraThread(tabSM, nbFlechette, ptrTabDevGenerator);
    __syncthreads();//barrière pour les threads d'un même bloc
    reductionADD<int>(tabSM, ptrDevResult);//méthode générique
}

static __device__ void reductionIntraThread(int* tabSM, int nbFlechette, curandState* ptrTabDevGenerator){
    //const int TID_Local = threadIdx.x;
    //tabSM[TID_Local] = 1;
    const int TID = Indice1D::tid();

    curandState localGenerator = ptrTabDevGenerator[TID];

    float xAlea, yAlea;

    for(long i = 1; i <= nbFlechette; i++){
	xAlea = curand_uniform(&localGenerator);
	yAlea = curand_uniform(&localGenerator);
	work(xAlea, yAlea);
    }

    ptrTabDevGenerator[TID] = localGenerator;
}

void work(xAlea, yAlea){

}

__global__ void setup_kernel_rand(curandState* ptrTabDevGenerator, int deviceId)
{
// Customisation du generator:
// Proposition, au lecteur de faire mieux !
// Contrainte : Doit etre différent d'un GPU à l'autre
// Contrainte : Doit etre différent d’un thread à l’autre
    const int TID = Indice1D::tid();
    int deltaSeed = deviceId * INT_MAX / 10000;
    int deltaSequence = deviceId * 100;
    int deltaOffset = deviceId * 100;
    int seed = 1234 + deltaSeed;
    int sequenceNumber = TID + deltaSequence;
    int offset = deltaOffset;
    curand_init(seed, sequenceNumber, offset, &ptrTabDevGenerator[TID]);
}


/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
