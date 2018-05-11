#include "fileReadWrite.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


FileReadWrite::FileReadWrite(std::string filename)
{
	this->content = fileRead(filename);
	this->filename = filename;
}

char * FileReadWrite::fileRead(const std::string fileName)
{
	ifstream fin;
	fin.open(fileName, ios_base::in | ios_base::binary);

	if (!fin.is_open()) {
		cout << "can not locate file!" << endl;
	}
	else {
		fin.seekg(0, fin.end);
		this->length = fin.tellg();
		fin.seekg(0, fin.beg);
		char * buffer = new char[length];
		cout << "Reading" << length << "characters ...." << endl;
		fin.read(buffer, length);

		if (fin) {
			cout << "all characters read successfully" << endl;
		}
		else {
			cout << "error:" << fin.gcount() << "could be read";
		}

		fin.close();
		return buffer;
	}

	return nullptr;
}
