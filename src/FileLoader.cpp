/*
 * FileLoader.cpp
 *
 *  Created on: 16.11.2014
 *      Author: Michael
 */

#include <OpGLLib/FileLoader.h>

using namespace std;

FileLoader::FileLoader() :
		FileAllocator() {
	file = construct();
}

FileLoader::FileLoader(string name, ios::openmode openmode) {
	file = openFile(name, openmode);
}

FileLoader::FileLoader(FileLoader&& other) {
	file = other.file;
	fileType = std::move(other.fileType);
}

FileLoader::~FileLoader() {
	closeFile(file);
}

fstream *FileLoader::open(string name, ios::openmode openmode) {
	file = openFile(file, name, openmode);

	if (!file->good()) {
		cerr << "Failed to open file: '" << name << "'" << endl;
		return NULL;
	}
	fileType = name.substr(name.find_last_of('.') + 1);

	return file;
}

void FileLoader::close() {
	closeFile(file);
}

const string FileLoader::toString() {
	stringstream datastream;
	if (!file->is_open()) {
		return "";
	}

	file->seekg(0, ios::beg);

	datastream << file->rdbuf();

	return datastream.str();
}

const char *FileLoader::toCString() {
	const string &string = toString();
	char *cStr = new char[string.length() + 1];

	string.copy(cStr, string.length());
	cStr[string.length()] = '\0';

	return cStr;
}

fstream *FileLoader::getFile() {
	return file;
}

string FileLoader::getFileType() {
	return fileType;
}
