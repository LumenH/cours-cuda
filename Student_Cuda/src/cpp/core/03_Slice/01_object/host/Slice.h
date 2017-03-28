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

	Slice(const Grid& grid,float* ptrResult, int n);
	virtual ~Slice(void);

	void run();

    private:
	dim3 dg;
	dim3 db;

	int n;

	float* ptrResult;
	float* ptrDevResult;
	size_t sizeOctet;
	size_t sizeOctetSM;

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
