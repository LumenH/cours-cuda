#pragma once

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "MathTools.h"

#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"

using namespace cpu;
using std::cout;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
class MandelbrotMath{
    public:
	MandelbrotMath(uint n) : calibreur(Interval<float>(1, n), Interval<float>(0, 1)){ //Check premier intervalle in pdf
	    this->n = n;
	}

	virtual ~MandelbrotMath(){
	    //rien
	}

	void colorXY(uchar4* ptrColor, float x, float y, float t){
	    float z = f(x, y, t);

	    if(z == -1){
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;

	    }else{
		calibreur.calibrer(z);
		float hue01 = z;

		ColorTools::HSB_TO_RVB(hue01, ptrColor);
	    }


	    ptrColor->w = 255;
	}

    private:
	float f(float x, float y, float t){
	    float a = 0;
	    float b = 0;
	    float aCopy = 0;
	    int k = 0;

	    while(a*a+b*b < 4){//Conditions inverses que dans le PDF
	    	if(k > t){
	    		return -1;
	    	}
	    	else{
	    		aCopy = a;
		    	a = (a*a - b*b)+x;
		    	b = 2*aCopy*b+y;
		    	k++;
	    	}

	    }

	    return k;
	}

	uint n;
	Calibreur<float> calibreur;
};



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
