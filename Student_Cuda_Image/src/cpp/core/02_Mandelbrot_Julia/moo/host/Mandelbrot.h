#pragma once

#include "MandelbrotMath.h"
#include "cudaTools.h"

#include "Variateur_GPU.h"
#include "Animable_I_GPU.h"
using namespace gpu;


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Mandelbrot : public Animable_I<uchar4>{
    public:
	Mandelbrot(const Grid& grid, uint w, uint h, int dt, uint n, const DomaineMath& domaineMath);
	virtual ~Mandelbrot(void);

	/*-------------------------*\
	|*   Override Animable_I   *|
	\*------------------------*/

	/**
	 * Call periodicly by the api
	 */
	virtual void process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath);


	/**
	 * Call periodicly by the api
	 */
	virtual void animationStep();

    private:
	void workPixel(uchar4* ptrColorIJ, int i, int j, const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath);

	uint n;

	// Tools
	Variateur<int> variateurAnimation;

};



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
