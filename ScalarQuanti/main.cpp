#include <iostream>
#include "fileReadWrite.h"
#include <cmath>
#include <vector>
#include <fstream>
#include <stdlib.h>//use rand for test
#include "lloydmax.h"
using namespace std;
double findInterval(int data, vector<double> center) {
	if (center.size() < 1) { return -1; }//for safety
	int interval = 0;
	double distance = data - center.at(0);
	for (int i = 1; i < center.size(); i++) {
		if (abs(data - center.at(i)) < distance) {
			distance = data - center.at(i);
			interval = i;
		}
	}
	return center.at(interval);
}

vector<double> scaleData(vector<int> data, vector<double> center) {
	vector<double> scaledData;
	for (int i = 0; i < data.size(); i++) {
		scaledData.push_back(findInterval(data.at(i), center));
	}
	return scaledData;
}
int main(int argc, char** argv) {
	vector<int> trainData;
	//=====================actural train data====================//
	FileReadWrite file = FileReadWrite("../data/house.256");
	std::string content;
	content.assign(file.content, file.length);
	std::string imageData = content.substr(0, file.length);
	FileReadWrite file2 = FileReadWrite("../data/moon.256");
	std::string content2;
	content2.assign(file2.content, file2.length);
	imageData += content2.substr(0, file2.length);
	FileReadWrite file3 = FileReadWrite("../data/chem.256");
	std::string content3;
	content3.assign(file3.content, file3.length);
	imageData += content3.substr(0, file3.length);
	for (auto symbol : imageData) {
		int mag = (int)symbol;
		if (mag < 0) {
			mag += 256;
		}
		trainData.push_back(mag);
	}
	cout << "train data size:" << trainData.size() << "\\\\" << endl;
	//=============================================================//


	//======================test data=============================//
	vector<int> testData;
	FileReadWrite file4 = FileReadWrite("../data/f16.256");
	std::string content4;
	content4.assign(file4.content, file4.length);
	std::string testimageData = content4.substr(0, file4.length);
	FileReadWrite file5 = FileReadWrite("../data/couple.256");
	std::string content5;
	content5.assign(file5.content, file5.length);
	testimageData += content5.substr(0, file5.length);
	FileReadWrite file6 = FileReadWrite("../data/elaine.256");
	std::string content6;
	content6.assign(file6.content, file6.length);
	testimageData += content6.substr(0, file6.length);

	ofstream datafile("../data/Imagedata.txt");
	if (!datafile.is_open()) {
		return -1;
	}

	for (auto symbol : testimageData) {
		int mag = (int)symbol;
		if (mag < 0) {
			mag += 256;
		}
		testData.push_back(mag);
		datafile << mag << endl;
	}
	datafile.close();
	cout << "test data size:" << testData.size() << "\\\\" << endl;
	//=============================================================//
	
	lloydMax atest = lloydMax(4);
	atest.classify(trainData);
	vector<double> centroids = atest.getCentroids();
	vector<double> scaledData;
	for (int i = 0; i < trainData.size(); i++) {
		scaledData.push_back(findInterval(trainData.at(i), centroids));
	}
	for (int i = 0; i < testData.size(); i++) {
		scaledData.push_back(findInterval(testData.at(i), centroids));
	}

	//output data
	ofstream myfile("../data/scaledImagedata2bits.txt");

	if (myfile.is_open()) {
		for (int i = 0; i < scaledData.size(); i++) {
			myfile << scaledData.at(i) << " " << endl;
		}
		myfile.close();
	}

	for (auto it = atest.PSNRs.begin(); it != atest.PSNRs.end(); it++) {
		cout << *it << " " << endl;
	}
	return 0;
}