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

bool isPiOMPEntrelacerCritical_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPEntrelacerCritical(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerCritical_Ok(int n)
    {
    return isAlgoPI_OK(piOMPEntrelacerCritical, n, "Pi OMP Entrelacer critical");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

double piOMPEntrelacerCritical(int n)
{
    const int NB_THREAD = OmpTools::setAndGetNaturalGranularity();

    double sumGlobal = 0;
    const double DX = 1/(double)n;

    #pragma omp parallel
    {
        const int TID = OmpTools::getTid();
        int s = TID;
        double sumLocal = 0;

        while(s < n)
        {
            double xs = s*DX;

            sumLocal += fpi(xs);
            s += NB_THREAD;
    	}

	#pragma omp critical (blabla)
        {
	    sumGlobal += sumLocal;
        }
    }//Barriere de synchronisation implicite

    return sumGlobal*DX;
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

