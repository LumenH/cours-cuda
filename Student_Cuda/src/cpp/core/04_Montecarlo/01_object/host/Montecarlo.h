#pragma once

#include "cudaTools.h"
#include "Grid.h"
#include <curand_kernel.h>



/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
class Montecarlo{

    public :
	Montecarlo(const Grid& grid, int nbFlechette);
	virtual ~Montecarlo(void);

	void run();
	float getResult();

    private:
	dim3 dg, db;
	int nbFlechette;

	float M;
	float a, b;

	int nbFlechetteDessous;
	float result;
	int* ptrDevResult;

	size_t sizeOctetGM;
	size_t sizeOctetSM;
	size_t sizeOctetGeneratorGM;

	curandState* ptrTabDevGenerator;
};



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
