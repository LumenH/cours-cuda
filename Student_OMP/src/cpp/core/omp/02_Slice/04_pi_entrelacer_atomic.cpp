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

bool isPiOMPEntrelacerAtomic_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPEntrelacerAtomic(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerAtomic_Ok(int n)
    {
    return isAlgoPI_OK(piOMPEntrelacerAtomic,  n, "Pi OMP Entrelacer atomic");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Bonne performance, si!
 */
double piOMPEntrelacerAtomic(int n)
{
    const int NB_THREAD = OmpTools::setAndGetNaturalGranularity();

    double sumGlobal = 0;
    const double DX = 1/(double)n;

    #pragma omp parallel shared(sumGlobal) //La variale sumGlobal est partage par tous les threads, optionnelle car comportement par défaut
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

	#pragma omp atomic //Protege uniquement le prochain operateur mathematique
	sumGlobal += sumLocal;
    }//Barriere de synchronisation implicite

    return sumGlobal*DX;
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

