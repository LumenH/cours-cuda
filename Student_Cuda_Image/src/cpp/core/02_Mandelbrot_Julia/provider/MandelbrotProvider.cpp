#include "MandelbrotProvider.h"
#include "Mandelbrot.h"

#include "MathTools.h"
#include "Grid.h"

#include "ImageAnimable_GPU.h"
#include "DomaineMath_GPU.h"

using namespace gpu;
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

    int dt = 1;
    int n = 120;

    int dw = 16 * 80;
    int dh = 16 * 60;

    int mp = Device::getMPCount();
    int coreMP= Device::getCoreCountMP();

    dim3 dg = dim3(mp, 2, 1);
    dim3 db = dim3(coreMP, 2, 1);

    Grid grid(dg, db);

    return new Mandelbrot(grid, dw, dh, dt, n, domaineMath);
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

