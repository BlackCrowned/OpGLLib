/*
 * FileLoader.cpp
 *
 *  Created on: 16.11.2014
 *      Author: Michael
 */

#include <OpGLLib/FileLoader.h>

using namespace std;

namespace OpGLLib {
FileLoader::FileLoader() {
	file = new fstream();
}

FileLoader::FileLoader(string name, ios::openmode openmode) {
	file = new fstream(name, openmode);
}

FileLoader::FileLoader(FileLoader&& other) {
	file = other.file;
	other.file = nullptr;
	fileType = std::move(other.fileType);
}

FileLoader::~FileLoader() {
	delete file;
}

fstream *FileLoader::open(string name, ios::openmode openmode) {
	file->open(name, openmode);

	if (!file->good()) {
		cerr << "Failed to open file: '" << name << "'" << endl;
		return NULL;
	}
	fileType = name.substr(name.find_last_of('.') + 1);

	return file;
}

void FileLoader::close() {
	if (file->is_open()) {
		file->close();
	}
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

shared_ptr<char> FileLoader::toCString__() {
	const string &string = toString();
	shared_ptr<char> cStr(new char[string.length() + 1], OpGLLib::default_delete<char>());

	string.copy(cStr.get(), string.length());
	cStr.get()[string.length()] = '\0';

	return cStr;
}

fstream *FileLoader::getFile() {
	return file;
}

string FileLoader::getFileType() {
	return fileType;
}

FileLoader::operator bool() {
	return file->good();
}

namespace files {
size_t size(std::fstream& file) {
	//Save current get pointer
	size_t const& currg = file.tellg();
	//Get file size
	file.seekg(0, file.end);
	size_t const& size = file.tellg();
	//Reset to previous get pointer
	file.seekg(currg, file.beg);
	return size;
}

char *dataPtr(std::fstream& file) {
	//Get file size
	size_t const& size = files::size(file);
	//Allocate memory
	char* buf = new char[size + 1];
	//Read data
	file.seekg(0, file.beg);
	file.read(buf, size);
	//Add terminating Null-Byte
	buf[file.gcount()] = '\0';
	//Return buffer
	return buf;
}
std::shared_ptr<char> dataSharedPtr(std::fstream& file) {
	//Return pointer as shared_ptr with custom deleter
	return shared_ptr<char>(dataPtr(file), OpGLLib::default_delete<char[]>());
}
std::string dataString(std::fstream& file) {
	return std::string(dataPtr(file), size(file));
}
}
}

