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
	    float dz = 0;
	    float brightness = 0;
	    float hue = 0;
	    float distance = 0;
	    float nearestDistance = 100000;


	    for(int k = 0; k < nbSphere; k++){
		Sphere sphereK = ptrTabSphere[k];
		hCarre = sphereK.hCarre(xySol);

		int blackOrColor = (int) sphereK.isEnDessous(hCarre);

		dz = sphereK.dz(hCarre);
		distance = sphereK.distance(dz);

		if(distance * blackOrColor < nearestDistance * blackOrColor){
		    nearestSphere = SphereK;
		    nearestDistance = distance;
		}

		hCarre = nearestSphere.hCarre(xySol);
		dz = nearestSphere.dz(hCarre);
		brightness = nearestSphere.brightness(dz);
		hue = nearestSphere.getHueStart() + nearestSphere.hue(t);
		ColorTools::HSB_TO_RVB(hue, 1, brightness, ptrColor);
	    }
	}

    private:
	Sphere* ptrTabSphere;
	int nbSphere;
};
