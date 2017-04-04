#pragma once

#include "cudaTools.h"
#include "Grid.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
class Montecarlo{

    public :
	Montecarlo(const Grid& grid, float* ptrResult, int nbFlechette);
	virtual ~Montecarlo(void);

	void run();

    private:
	dim3 dg, db;

	int nbFlechette;

	float* ptrResult;
	float* ptrDevResult;

	size_t sizeOctetGM;
	size_t sizeOctetSM;
	size_t sizeOctetGeneratorGM;

	curandState* ptrTabDevGenerator;
};



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
