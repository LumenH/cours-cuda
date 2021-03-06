#include <iostream>
#include "Grid.h"
#include "Device.h"
#include "Slice.h"

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

bool useSlice(){
    int nbSlice = 1000000;

    float Result;

    int mp = 256;

    dim3 dg = dim3(mp,1,1);
    dim3 db = dim3(1024,1,1);
    Grid grid(dg, db);

    Slice slice(grid, &Result, nbSlice);
    slice.run();

    cout<<Result<<endl;

    return true;
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

