#pragma once

#include "cudaTools.h"
#include "DataCreator.h"
#include "Grid.h"

class Histogramme{
    public:
	Histogramme(const Grid& grid, int SizeTab);
	virtual ~Histogramme(void);

	int* run();

    private:
	DataCreator *datacreator;
	int sizeTab;
	int n;

	int* ptrTabData;
	int* ptrTabResult;

	dim3 dg, db;
	int* ptrDevResult;
	int* ptrDevData;

	size_t sizeOctet;
	size_t sizeOctetResult;


};
