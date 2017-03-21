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
	    xySol.x = i;
	    xySol.y = j;

	    float hCarre = 0;
	    float brightness = 0;
	    float dz = 0;

	    float hue = ptrTabSphere[0].getHueStart();

	    ptrColor->x = 0;
	    ptrColor->y = 0;
	    ptrColor->z = 0;
	    ptrColor->w = 255;

	    int k = 0;
	    for(k = 0; k < nbSphere; k++){
		hCarre = ptrTabSphere[k].hCarre(xySol);

		if(ptrTabSphere[k].isEnDessous)
	    }
	}
};
