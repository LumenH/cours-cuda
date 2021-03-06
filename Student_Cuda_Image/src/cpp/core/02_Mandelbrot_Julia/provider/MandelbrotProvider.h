#pragma once
#include "cudaTools.h"
#include "Animable_I_GPU.h"
#include "Provider_I_GPU.h"

using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotProvider : public Provider_I<uchar4>
{
    public:
	virtual ~MandelbrotProvider(){
	//rien
	}

	Animable_I<uchar4>* createAnimable(void);
	Image_I* createImageGL(void);
};


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
