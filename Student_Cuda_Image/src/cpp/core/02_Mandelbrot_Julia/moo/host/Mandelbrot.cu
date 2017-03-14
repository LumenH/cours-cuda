#include "Mandelbrot.h"
#include "MandelbrotMath.h"
#include "DomaineMath_GPU.h"

#include <iostream>
#include <assert.h>
#include "Device.h"

using std::cout;
using std::endl;
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
extern __global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, float t, const uint n, DomaineMath domaineMath);
//extern __device__ void workPixel(uchar4* ptrColorIJ, int i, int j, const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath);
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

Mandelbrot::Mandelbrot(const Grid& grid, uint w, uint h, int dt, uint n, const DomaineMath& domaineMath) :
	Animable_I<uchar4>(grid, w, h, "Damier_OMP_rgba_uchar4",domaineMath), variateurAnimation(Interval<int>(30, n), dt)
{
	this->n = n;
	this->t = 0;
}

Mandelbrot::~Mandelbrot(){

}


void Mandelbrot::animationStep(){
    this->t = variateurAnimation.varierAndGet();
}

void Mandelbrot::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath){
    Device::lastCudaError("Mandelbrot before kernel");

    mandelbrot<<<dg,db>>>(ptrDevPixels, w, h, t, n, domaineMath );

    Device::lastCudaError("Mandelbrot after kernel");
}
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

