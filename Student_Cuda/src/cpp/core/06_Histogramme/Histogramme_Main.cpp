#include <iostream>
#include "Grid.h"
#include "Device.h"

#include "Histogramme.h"

using std::cout;
using std::endl;

bool useHistogramme(){

    const int SIZE_TAB = 256;
    int* result;

    int mp = Device::getMPCount();
    dim3 dg = dim3(mp, 1, 1);
    dim3 db = dim3(64, 1, 1);
    Grid grid(dg, db);

    Histogramme h(grid, SIZE_TAB);
    result = h.run();

    cout << "Resultat: " <<endl;
    for(int i = 0; i < SIZE_TAB; i++){
	cout<<result[i]<<", ";
    }
    cout << endl << "Fin du tableau de résultat"<<endl;
    return true;
}
