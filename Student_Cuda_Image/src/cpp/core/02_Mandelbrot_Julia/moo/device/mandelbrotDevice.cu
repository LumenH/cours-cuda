#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "IndiceTools_GPU.h"
#include "DomaineMath_GPU.h"
#include "MandelbrotMath.h"

using namespace gpu;

__device__ void workPixel(uchar4* ptrColorIJ, int i, int j, const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath, float t){
    double x, y;
    domaineMath.toXY(i, j, &x, &y);

    ptrMandelbrotMath->colorXY(ptrColorIJ, x, y, t);
}

__global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, float t, const uint n,  DomaineMath domaineMath);

__global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, float t, const uint n, DomaineMath domaineMath){
    MandelbrotMath mandelbrotMath(n);

    const int WH = w*h;
    const int NB_THREAD = Indice2D::nbThread();
    const int TID = Indice2D::tid();

    int i, j;
    int s = TID;

    while(s < WH){
        IndiceTools::toIJ(s, w, &i, &j);
        workPixel(&ptrDevPixels[s], i, j, domaineMath, &mandelbrotMath, t);
        s += NB_THREAD;
    }
}


