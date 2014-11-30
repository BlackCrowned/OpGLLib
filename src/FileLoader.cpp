/*
 * FileLoader.cpp
 *
 *  Created on: 16.11.2014
 *      Author: Michael
 */

#include <OpGLLib/FileLoader.h>

using namespace std;

FileLoader::FileLoader() {

}

FileLoader::FileLoader(string name, ios::openmode openmode) {
	open(name, openmode);
}

FileLoader::~FileLoader() {
	if (file.is_open()) {
		file.close();
	}
}

fstream *FileLoader::open(string name, ios::openmode openmode) {

	file.open(name.c_str(), openmode);

	if (!file.good()) {
		cerr << "Failed to open file: '" << name << "'" << endl;
		return NULL;
	}
	fileType = name.substr(name.find_last_of('.') + 1);

	return &file;
}

void FileLoader::close() {
	file.close();
}

string FileLoader::toString() {
	stringstream datastream;
	if (!file.is_open()) {
		return "";
	}

	datastream << file.rdbuf();

	return datastream.str();
}

fstream *FileLoader::getFile() {
	return &file;
}

string FileLoader::getFileType() {
	return fileType;
}
