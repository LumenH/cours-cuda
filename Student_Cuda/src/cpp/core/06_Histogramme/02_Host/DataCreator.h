#pragma once

class DataCreator{
    public:
	DataCreator(int dataMax);
	virtual ~DataCreator(void);

	int* getTabData();
	void print();
	int getLength();

    private:
	void createDataTriangulaire();
	void melangeData();
	void swap(int i, int j);

	int dataMax;
	int n;
	int nbMelange;
	int* tabData;
};


