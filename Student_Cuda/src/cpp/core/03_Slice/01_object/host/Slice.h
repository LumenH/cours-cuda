#pragma once

#include "cudaTools.h"
#include "Grid.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Slice
    {
    public:

	Slice(const Grid& grid,float* ptrResult, int nbSlice);
	virtual ~Slice(void);

	void run();

    private:
	dim3 dg;
	dim3 db;

	int nbSlice;

	float* ptrResult;
	float* ptrDevResult;
	size_t sizeOctetGM;
	size_t sizeOctetSM;

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
