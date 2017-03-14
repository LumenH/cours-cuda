#include "Raytracing.h"
#include "SphereCreator.h"

Raytracing::Raytracing(int nbSphere, int w, int h){
    //todo des trucs qu'on sait pas
    SphereCreator sphereCreator(nbSphere, w, h);
    Sphere* ptrTabSphere = sphereCreator.getTab();

    this->sizeOctet = sizeof(Sphere)*nbSphere;

    //Transfert to Global Memory
    toGM(ptrTabSphere);

    //Transfert to CM
    //toCM(ptrTabSphere);
}

Raytracing::toGM(Sphere* ptrTabSphere){
    Device::malloc(ptrDevTabSphere, sizeOctet);
    Device::memclear(ptrDevTabSphere, sizeOctet);
    Device::memcpyHToD(ptrDevTabSphere, ptrTabSphere, sizeOctet);

}

Raytracing::~Raytracing(){
    Device::free(ptrDevTabSphere);
}

/*Raytracing::ToCM(Sphere* ptrTabSphere){

}*/

