#include <iostream>
#include "Grid.h"
#include "Device.h"
#include "MontecarloMultiGPU.h"

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

bool useMontecarloMulti(){
    int nbFlechette = INT_MAX/10;
    float result;

    int mp = 64;

    dim3 dg = dim3(mp, 1, 1);
    dim3 db = dim3(1024, 1, 1);
    Grid grid(dg, db);

    MontecarloMultiGPU montecarlomultigpu(grid, nbFlechette);
    montecarlomultigpu.runMulti();

    result = montecarlomultigpu.getResult();
    cout<<result<<endl;

    return true;
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

