#pragma once

#include "Grid.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MontecarloMultiGPU{
    public:
	MontecarloMultiGPU(const Grid& grid, const int nbFlechetteTotale);
	virtual ~MontecarloMultiGPU(){};
	void runMulti();
	float getResult();

    private:
	int nbDevice;
	Grid grid;
	int nbFlechetteTotale;
	float result;

};


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
