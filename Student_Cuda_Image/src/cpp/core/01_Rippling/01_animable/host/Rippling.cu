#include <iostream>
#include <assert.h>

#include "Device.h"
#include "Rippling.h"
#include <assert.h>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void rippling(uchar4* ptrDevPixels,uint w, uint h,float t);

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

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

Rippling::Rippling(const Grid& grid, uint w, uint h, float dt) :
	Animable_I<uchar4>(grid, w, h, "Rippling_Cuda_RGBA_uchar4")
    {
    assert(w == h); // specific rippling

    // Inputs
    this->dt = dt;

    // Tools
    this->t = 0; // protected dans Animable
    }

Rippling::~Rippling()
    {
    // rien
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */
void Rippling::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    Device::lastCudaError("rippling rgba uchar4 (before kernel)"); // facultatif, for debug only, remove for release

    // TODO lancer le kernel avec <<<dg,db>>>
    // le kernel est importer ci-dessus (ligne 19)
<<<<<<< HEAD
=======
    rippling<<<dg,db>>>(ptrDevPixels, w, h, t);
>>>>>>> 1e91cebe3b4b949c7e3d13a3e5f185d4131eae5d

    Device::lastCudaError("rippling rgba uchar4 (after kernel)"); // facultatif, for debug only, remove for release
    }

/**
 * Override
 * Call periodicly by the API
 */
void Rippling::animationStep()
    {
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

