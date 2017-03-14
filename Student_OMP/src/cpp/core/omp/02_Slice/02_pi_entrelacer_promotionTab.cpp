#include <omp.h>
#include "OmpTools.h"
#include "../02_Slice/00_pi_tools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerPromotionTab_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPEntrelacerPromotionTab(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerPromotionTab_Ok(int n)
    {
    return isAlgoPI_OK(piOMPEntrelacerPromotionTab,  n, "Pi OMP Entrelacer promotionTab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * pattern cuda : excellent!
 */
double piOMPEntrelacerPromotionTab(int n)
    {
	const int NB_THREAD = OmpTools::setAndGetNaturalGranularity();

	double tabSum[NB_THREAD];
	const double DX = 1/(double)n;

	#pragma omp parallel
	{
	    const int TID = OmpTools::getTid();
	    int s = TID;

	    tabSum[TID] = 0; //Init in parallel

	    while(s < n)
	    {
		double xs = s*DX;
		tabSum[TID] += fpi(xs);
		s += NB_THREAD;
	    }
	}//Barriere de synchronisation implicite

	//Reduction séquentielle
	double sumGlobal = 0;
	for(int i = 0; i < NB_THREAD; i++)
	{
	    sumGlobal += tabSum[i];
	}
	return sumGlobal*DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

