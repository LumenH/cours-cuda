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
class MontecarloMulti{

    public :
	MontecarloMulti(const Grid& grid, int nbFlechette);
	virtual ~MontecarloMulti(void);

	void run();
	float getResult();
	int getNbFlechette();

    private:
	dim3 dg, db;

	int nbFlechette;

	int nbFlechetteDessous;
	float result, a, b;
	float M;
	int* ptrDevResult;

	size_t sizeOctetGM;
	size_t sizeOctetSM;
	size_t sizeOctetGeneratorGM;

	curandState* ptrTabDevGenerator;
};



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
