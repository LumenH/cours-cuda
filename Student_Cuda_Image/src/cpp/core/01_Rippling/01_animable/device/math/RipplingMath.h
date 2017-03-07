#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ RipplingMath(int w, int h)
	    {
	    this->dim2 = w / 2;
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	__device__
	   virtual ~RipplingMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColor, int i, int j, float t)
	    {
	    uchar levelGris;

	    f(&levelGris, i, j, t); // update levelGris

	    ptrColor->x = levelGris;
	    ptrColor->y = levelGris;
	    ptrColor->z = levelGris;

	    ptrColor->w = 255; // opaque
	    }

    private:

	__device__
	void f(uchar* ptrLevelGris, int i, int j, float t)
	    {
	    // TODO cf fonction math pdf
	    // use focntion dij ci-dessous

	    // Note
	    //		Si code OMP focntionnel:
	    // 			Step1 : Delete le contenur de ce fichier (si!),
	    // 			Step2 : Copie-past le contenu de RipplingMath.h de omp,
	    // 			Step3 : Ajouter __device__  devant methode et constructeur!
	    float ptrResult = dij(i, j);
	    float numerateur = cosf((ptrResult / 10) - (t/7));
	    float denominateur =  ptrResult / 10 + 1;
	    *ptrLevelGris = 128 + 127 * (numerateur/denominateur);
	    }

	__device__
	float  dij(int i, int j)
	    {
	    //TODO cf fonction math pdf
	    // return ...
	    float fi = i - dim2;
	    float fj = j - dim2;
	    return sqrtf(fi*fi + fj*fj);
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	float dim2;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
