#ifndef LLOYDMAX_H_
#define LLOYDMAX_H_

//THIS IS INDIVIDUAL WORK DONE BY 
//LI YICHENG AT USC
//9/24/2017
#include <iostream>
#include "fileReadWrite.h"
#include <cmath>
#include <vector>
#include <stdlib.h>

using namespace std;
class lloydMax {
private :
	int bits = 2;
	int nlabels = pow(2, bits);
	std::vector<double> centroids = vector<double>(nlabels);
	vector<int> trainData;
	vector<vector<int>> drawers = vector<vector<int>>(nlabels);
	double MSE = 0;
	
private:
	double calDistance(double a, double b);

	double average(vector<int> data);

	double stdDev(vector<int> data);

	int classify(int data);

	void generNewCentroid();

	void initialization();
	
public:
	lloydMax();
	lloydMax(int n);
	void classify(vector<int> inputdata);
	double getMSE() { return MSE; }
	vector<double> getCentroids() { return centroids; }
	vector<double> PSNRs;

};

#endif