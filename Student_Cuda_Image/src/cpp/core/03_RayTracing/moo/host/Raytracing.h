#pragma once

#include "cudaTools.h"
#include "MathTools.h"
#include "Sphere.h"

#include "Animable_I_GPU.h"

using namespace gpu;


class Raytracing: public Animable_I<uchar4>{
    public:
	Raytracing(const Grid& grid, uint w, uint h, float dt, int nbSphere); //Add parameters
	void toGM(Sphere* ptrDevTabSphere);
	virtual void process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath);
	virtual void animationStep();
	virtual ~Raytracing(void);

    private:
	float dt;
	dim3 dg, db;
	int nbSphere;

	size_t sizeOctet;
	Sphere* ptrDevTabSphere;

};


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
