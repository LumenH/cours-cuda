#include <omp.h>
#include "MathTools.h"
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

bool isPiOMPforPromotionTab_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforPromotionTab(int n);
static void syntaxeSimplifier(double* tabSumThread,int n);
static void syntaxeFull(double* tabSumThread,int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforPromotionTab_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforPromotionTab, n, "Pi OMP for promotion tab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * De-synchronisation avec PromotionTab
 */
double piOMPforPromotionTab(int n)
{
    const double DX = 1 / (double) n;
    const int NB_THREAD = OmpTools::setAndGetNaturalGranularity();

    double* tab = new double[NB_THREAD]; //Tableau creer sur le tas, a faire un maximum

    #pragma omp parallel for
    for(int i = 0; i < NB_THREAD; i++){
	tab[i] = 0;
    }

    #pragma omp parallel for// On lui dis de faire une boucle for en parallele sans se soucier de comment il fait
    for (int i = 0; i < n; i++)
    {
	int TID = OmpTools::getTid();
	double xi = i * DX;
        tab[TID] += fpi(xi);
    }

    //Reduction additive sequentielle
    double sum = 0;
    for(int i = 0; i < NB_THREAD; i++)
    {
	sum += tab[i];
    }
    delete[] tab;
    return sum * DX;
}



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

