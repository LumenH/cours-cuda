#include "cudaTools.h"
#include "Indice2D.h"

#include "IndiceTools_GPU.h"
#include "Sphere.h"

using namespace gpu;

__global__ void raytracing(uchar4* ptrDevPixels, uint w, uint h, float t, Sphere* ptrDevtabSphere, int nbSphere){
    const int NB_THREAD = Indice2D::nbThread();
    const int TID = Indice2D::tid();
    const int WH = w*h;

    int s = TID;
    //int n = nbSphere;
    int i, j;
    //float hcarree = 0;

    while(s < WH){
	IndiceTools::toIJ(s, w, &i,  &j);
	//todo workpixel

	s += NB_THREAD;
    }
}
