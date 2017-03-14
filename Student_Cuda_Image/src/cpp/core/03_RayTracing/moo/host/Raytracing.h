#ifndef SRC_CPP_CORE_03_RAYTRACING_MOO_HOST_RAYTRACING_H_
#define SRC_CPP_CORE_03_RAYTRACING_MOO_HOST_RAYTRACING_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Raytracing{
    public:
	Raytracing(int nbSphere, int w, int h); //Add parameters
	void toGM(Sphere* ptrTabSphere);
	void toCM(Sphere* ptrTabSphere);
	virtual ~Raytracing(void);

    private:
	size_t sizeOctet;
	Sphere* ptrDevTabSphere;

};

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
