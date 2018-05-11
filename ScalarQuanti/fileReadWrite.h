#pragma once
//author : Li Yicheng 8/27/2017
#ifndef FILEREADWRITE_H_
#define FILEREADWRITE_H_

#include<iostream>
#include<string>
class FileReadWrite {
public:
	FileReadWrite(std::string filename);
	std::string filename;
	char * content;
	long length;
private:
	char * fileRead(const std::string fileName);
};

#endif
