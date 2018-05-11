//Li Yicheng
#include "lloydmax.h"

double lloydMax::calDistance(double a, double b)
{
	return pow(a - b, 2);
}

double lloydMax::average(vector<int> data)
{
	double sum = 0;
	for (int i = 0; i < data.size(); i++) {
		sum += data.at(i);
	}
	return sum / (double)data.size();
}

double lloydMax::stdDev(vector<int> data)
{
	double expectation = average(data);
	double sum = 0;
	for (int i = 0; i < data.size(); i++) {
		sum += pow(data.at(i) - expectation, 2);
	}
	return sqrt(sum / (double)data.size());
}

int lloydMax::classify(int data)
{
	int label = 0;
	double distance = calDistance((double)data, centroids.at(0));
	for (int i = 1; i < nlabels; i++) {
		double ithDistance = calDistance((double)data, centroids.at(i));
		if (ithDistance < distance) {
			distance = ithDistance;
			label = i;
		}
	}
	MSE += distance;
	drawers.at(label).push_back(data);
	return label;
}

void lloydMax::generNewCentroid()
{
	for (int i = 0; i < nlabels; i++) {
		centroids.at(i) = average(drawers.at(i));
	}
}

void lloydMax::initialization()
{
	double exp = average(trainData);
	double stdev = stdDev(trainData);
	for (int i = 0; i < nlabels / 2; i++) {
		centroids.at(nlabels / 2 + i) = exp + stdev*(i + 1) / nlabels * 2;
		centroids.at(nlabels / 2 - 1 - i) = exp - stdev*(i + 1) / nlabels * 2;
	}
}

lloydMax::lloydMax()
{
}

lloydMax::lloydMax(int n)
{
	this->bits = n;
	this->nlabels = pow(2, bits);
	this->centroids = vector<double>(nlabels);
	this->drawers = vector<vector<int>>(nlabels);
}

void lloydMax::classify(vector<int> inputdata)
{
	trainData = inputdata;
	//initialize:
	initialization();
	//out initialize centroid
	cout << "initial centers:" << "\\\\" << endl;
	for (int i = 0; i < nlabels; i++) {
		cout << centroids.at(i) << " ";
	}
	cout << "\\\\" << endl;

	//classification
	double tempMSE = 0;
	int trialCount = 1;
	while (1) {
		cout << "training " << trialCount << ":" << "\\\\" << endl;
		for (int i = 0; i < trainData.size(); i++) {
			classify(trainData.at(i));
		}
		//out new centroid and MSE
		for (int i = 0; i < nlabels; i++) {
			generNewCentroid();
			cout << centroids.at(i) << " ";
		}
		//cout << "\\\\" << endl;
		MSE = MSE / trainData.size();
		//cout << "MSE:" << MSE << "\\\\" <<endl;
		double PSNR = 10 * log10(255 * 255 / MSE);
		cout << "PSNR:" << PSNR << "\\\\" << endl;
		PSNRs.push_back(PSNR);
		if (abs(MSE - tempMSE) < 0.001) {
			cout << "end of traning!\\\\" << endl;
			break;
		}
		trialCount++;
		tempMSE = MSE;
		MSE = 0;
		drawers.clear();//clear the prevoius classify
		drawers = vector<vector<int>>(nlabels);
	}
}
