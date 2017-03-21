#include "cudaTools.h"
#include "Indice2D.h"

#include "IndiceTools_GPU.h"
#include "Sphere.h"
#include "RaytracingMath.h"

using namespace gpu;

__global__ void raytracing(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrDevTabSphere, int nbSphere){
    RaytracingMath rm = RaytracingMath(ptrDevTabSphere, nbSphere);

    const int NB_THREAD = Indice2D::nbThread();
    const int TID = Indice2D::tid();
    const int WH = w*h;

    int s = TID;
    //int n = nbSphere;
    int i, j;
    //float hcarree = 0;

    while(s < WH){
	IndiceTools::toIJ(s, w, &i,  &j);
	rm.colorIJ(&ptrDevPixels[s], i, j, t);
	s += NB_THREAD;
    }
}
