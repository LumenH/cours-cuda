#include "Mandelbrot.h"
#include "MandelbrotMath.h"

#include <iostream>
#include <omp.h>
#include "OmpTools.h"

#include "IndiceTools_CPU.h"
using cpu::IndiceTools;

using std::cout;
using std::endl;
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

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

Mandelbrot::Mandelbrot(uint w, uint h, int dt, uint n, const DomaineMath& domaineMath) :
	Animable_I<uchar4>(w, h, "Damier_OMP_rgba_uchar4",domaineMath), variateurAnimation(Interval<int>(30, n), dt)
{
	this->n = n;
	this->t = 0;

	this->parallelPatern = ParallelPatern::OMP_MIXTE;
	cout << "\n[Mandelbrot] : OMP : nbThread = " << this->nbThread << endl;

}

Mandelbrot::~Mandelbrot(){

}


void Mandelbrot::animationStep(){
    this->t = variateurAnimation.varierAndGet();
}

void Mandelbrot::processForAutoOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath){
    MandelbrotMath mandelbrotMath(n);

    #pragma omp parallel for
    for(int i = 0; i < h; i++){
	for(int j = 0; j < w; j++){
	    int s = IndiceTools::toS(w, i, j);

	    workPixel(&ptrTabPixels[s], i, j, domaineMath, &mandelbrotMath);
	}
    }
}

void Mandelbrot::processEntrelacementOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath){
    MandelbrotMath mandelbrotMath(n);

    const int WH = w*h;

    #pragma omp parallel
    {
	const int NB_THREAD = OmpTools::getNbThread();
	const int TID = OmpTools::getTid();

	int i, j;
	int s = TID;

	while(s < WH){
	    IndiceTools::toIJ(s, w, &i, &j);
	    workPixel(&ptrTabPixels[s], i, j, domaineMath, &mandelbrotMath);
	    s += NB_THREAD;
	}
    }
}
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
void Mandelbrot::workPixel(uchar4* ptrColorIJ, int i, int j, const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath){
    double x, y;
    domaineMath.toXY(i, j, &x, &y);

    ptrMandelbrotMath->colorXY(ptrColorIJ, x, y, t);
}
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

