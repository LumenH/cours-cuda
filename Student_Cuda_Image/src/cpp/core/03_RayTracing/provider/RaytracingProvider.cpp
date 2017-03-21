#include "RaytracingProvider.h"
#include "Raytracing.h"

#include "MathTools.h"
#include "Grid.h"

Animable_I<uchar4>* RaytracingProvider::createAnimable(){
    int nbSphere = 20;

    //Peut animation
    int dw = 16*60;
    int dh = 16*60;
    //float dt = 2.f * PI_FLOAT / 1000;
    float dt = 1;
    int mp = Device::getMPCount();
    int coreMP = Device::getCoreCountMP();

    dim3 db = dim3(coreMP, 2, 1); //A switch pour le 2 et 1
    dim3 dg = dim3(mp, 2, 1);

    Grid grid(dg, db);

    return new Raytracing(grid, dw, dh, dt, nbSphere);
}

Image_I* RaytracingProvider::createImageGL(void){
    ColorRGB_01 colorTexte(0,0,0);
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
}

