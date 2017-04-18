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
static __device__ void reductionIntraThread(int* tabSM, int nbFlechette, curandState* ptrTabDevGenerator, float a, float b, float M);
__global__ void montecarlo(int* ptrDevResult, curandState* ptrTabDevGenerator, int nbFlechette, float a, float b, float M);
__device__ int work(float xAlea, float yAlea);
__device__ float toAB(float x, float a, float b);
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void montecarlo(int* ptrDevResult, curandState* ptrTabDevGenerator, int nbFlechette, float a, float b, float M){
    __shared__ extern int tabSM[];
    reductionIntraThread(tabSM, nbFlechette, ptrTabDevGenerator, a, b, M);
    __syncthreads();//barrière pour les threads d'un même bloc
    reductionADD<int>(tabSM, ptrDevResult);//méthode générique
}

__device__ float toAB(float x, float a, float b){
    return (b - a) / 1.0f * x + a;
}

__device__ float f(float x){
    return sqrtf(1.0f - x * x);
}

static __device__ void reductionIntraThread(int* tabSM, int nbFlechette, curandState* ptrTabDevGenerator, float a, float b, float M){
    const int TID_Local = Indice1D::tidLocal();
    //tabSM[TID_Local] = 1;
    const int TID = Indice1D::tid();

    curandState localGenerator = ptrTabDevGenerator[TID];

    float xAlea, yAlea;
    //float y;
    int n = 0;

    for(long i = 1; i <= nbFlechette; i++){
	xAlea = toAB(curand_uniform(&localGenerator), a, b);
	yAlea = toAB(curand_uniform(&localGenerator), a, b);
	if(yAlea < f(xAlea)){
	    n++;
	}
    }

    tabSM[TID_Local]=n;
    ptrTabDevGenerator[TID] = localGenerator;
}


__device__ int work(float xAlea, float yAlea){
    float fPi = (1.0 /(1.0 +xAlea*xAlea))*4;
    return (int) (fPi >= yAlea);
    //return (4.0/(1.0 + xAlea * xAlea));
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

