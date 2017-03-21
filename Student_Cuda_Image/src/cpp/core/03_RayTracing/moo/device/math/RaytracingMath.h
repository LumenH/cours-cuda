#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_GPU.h"
#include "ColorTools_GPU.h"

using namespace gpu;

class RaytracingMath{
    public:
	__device__ RaytracingMath(Sphere* ptrDevTabSphere, int nbSphere){
	    this->ptrTabSphere = ptrDevTabSphere;
	    this->nbSphere = nbSphere;
	}

	__device__ virtual ~RaytracingMath(){}

	__device__ void colorIJ(uchar4* ptrColor, int i, int j, float t){
	    float2 xySol;
	    xySol.x = j;
	    xySol.y = i;

	    float hCarre = 0;
	    float brightness = 0;
	    float dz = 0;

	    ptrColor->x = 0;
	    ptrColor->y = 0;
	    ptrColor->z = 0;
	    ptrColor->w = 255;

	    for(int k = 0; k < nbSphere; k++){
		Sphere sphereK = ptrTabSphere[k];
		hCarre = sphereK.hCarre(xySol);

		if(sphereK.isEnDessous(hCarre)){
		    dz = sphereK.dz(hCarre);
		    brightness = sphereK.brightness(t);
		    float hue = sphereK.hue(t);
		    ColorTools::HSB_TO_RVB(hue, 1, brightness, ptrColor);

		    //ptrColor->x = 0;
		    ptrColor->y = 255;
		    //ptrColor->z = 255;
		    ptrColor->w = 255;

		    k = nbSphere + 1;
		}
	    }
	}

    private:
	Sphere* ptrTabSphere;
	int nbSphere;
};
