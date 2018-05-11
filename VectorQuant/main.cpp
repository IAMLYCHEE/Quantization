#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
using namespace std;

// Here we assume the image is of size 256*256 and is of raw format
// You will need to make corresponding changes to accommodate images of different sizes and types

#define Size 256
using namespace std;

int main(int argc, char *argv[])

{

	//block size
	//if (argc!= 2) {
	//	cout << "in put block size" << endl;
	//	return -1;
	//}

	//int n = atoi(argv[2]);
	int n = 8;
	// file pointer three training file
	FILE *file1;
	FILE *file2;
	FILE *file3;
	if (!(file1 = fopen("./data/f16.256","rb")))
	{
		cout << "Cannot open file: " << endl;
		return -1;
	}
	if (!(file2 = fopen("./data/couple.256", "rb")))
	{
		cout << "Cannot open file: " << endl;
		return -1;
	}
	if (!(file3 = fopen("./data/elaine.256", "rb")))
	{
		cout << "Cannot open file: " << endl;
		return -1;
	}

	// image data array
	unsigned char imagedata1[Size][Size];
	unsigned char imagedata2[Size][Size];
	unsigned char imagedata3[Size][Size];

	// read image "ride.raw" into image data matrix
	//if (!(file = fopen(argv[1], "rb")))
	//{
	//	cout << "Cannot open file: " << argv[1] << endl;
	//	exit(1);
	//}
	fread(imagedata1, sizeof(unsigned char), Size*Size, file1);
	fclose(file1);
	fread(imagedata2, sizeof(unsigned char), Size*Size, file2);
	fclose(file2);	
	fread(imagedata3, sizeof(unsigned char), Size*Size, file3);
	fclose(file3);



	ofstream outfile("outblock8.raw", ios::binary);
	// do some image processing task...
	for (int i = 0; i < 257-n; i += n) {
		for (int j = 0; j < 257-n; j += n) {
			for (int u = 0; u < n; u++) {
				for (int v = 0; v < n; v++) {
					unsigned char temp = imagedata1[i + u][j + v];
					outfile.write((char*)&temp,sizeof(temp));
					//cout << "(" << i + u << "," << v + j << ")"; //for debug
				}
			}
			//cout << endl; // for debug
		}
	}

	for (int i = 0; i < 257-n; i += n) {
		for (int j = 0; j < 257-n; j += n) {
			for (int u = 0; u < n; u++) {
				for (int v = 0; v < n; v++) {
					unsigned char temp = imagedata2[i + u][j + v];
					outfile.write((char*)&temp, sizeof(temp));
				}
			}
		}
	}
	for (int i = 0; i < 257-n; i += n) {
		for (int j = 0; j < 257-n; j += n) {
			for (int u = 0; u < n; u++) {
				for (int v = 0; v < n; v++) {
					unsigned char temp = imagedata3[i + u][j + v];
					outfile.write((char*)&temp, sizeof(temp));
				}
			}
		}
	}
	// write image data to "~.raw"

	outfile.close();

	return 0;
}









