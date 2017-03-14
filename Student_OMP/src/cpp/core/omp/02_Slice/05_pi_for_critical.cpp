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

bool isPiOMPforCritical_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforCritique(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforCritical_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforCritique, n, "Pi OMP for critique");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * synchronisation couteuse!
 */
double piOMPforCritique(int n)
{
    /*double sum = 0;
    const double DX = 1/(double)n;
    double xi;

    #pragma omp parallel for private(xi)// On lui dis de faire une boucle for en parallele sans se soucier de comment il fait
    for(int i=0; i<=n;i++)
    {
    	xi = i*DX;
	#pragma omp critical (blabla)
    	{
    	    sum += fpi(xi);
    	}
    }
    return sum*DX;*/

    double sum = 0;
    const double DX = 1 / (double) n;

    #pragma omp parallel for// On lui dis de faire une boucle for en parallele sans se soucier de comment il fait
    for (int i = 0; i <= n; i++)
    {
	double xi = i * DX;
	#pragma omp critical (blabla)
	{
	    sum += fpi(xi);
	}
    }
    return sum * DX;
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

