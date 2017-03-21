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


	    ptrColor->x = 0;
	    ptrColor->y = 0;
	    ptrColor->z = 0;
	    ptrColor->w = 255;

	    for(int k = 0; k < nbSphere; k++){
		Sphere sphereK = ptrTabSphere[k];
		float hCarre = sphereK.hCarre(xySol);

		if(sphereK.isEnDessous(hCarre)){
		    float hue = sphereK.getHueStart();

		    float dz = sphereK.dz(hCarre);
		    float distance = sphereK.distance(dz);
		    float brightness = sphereK.brightness(dz);

		    ColorTools::HSB_TO_RVB(hue, 1, brightness, ptrColor);

		    ptrColor->w = 255;

		    k = nbSphere + 1;
		}
	    }
	}

    private:
	Sphere* ptrTabSphere;
	int nbSphere;
};
