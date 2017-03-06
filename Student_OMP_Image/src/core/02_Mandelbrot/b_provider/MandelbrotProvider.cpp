#include "MandelbrotProvider.h"
#include "Mandelbrot.h"

#include "MathTools.h"

#include "ImageAnimable_CPU.h"
#include "DomaineMath_CPU.h"

using namespace cpu;
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
Animable_I<uchar4>* MandelbrotProvider::createAnimable(void){
    DomaineMath domaineMath = DomaineMath(-2.1, -1.3, 0.8, 1.3);

    float dt = 1;//OSEF ca change la precision de lanimation
    int n = 0;

    int dw = 16 * 80;
    int dh = 16 * 60;

    return new Mandelbrot(dw, dh, dt, n, domaineMath);
}

Image_I* MandelbrotProvider::createImageGL(void){
    ColorRGB_01 colorTexte(0, 0, 0);
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
}
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

