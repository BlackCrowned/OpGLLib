/*
 * FileLoader.h
 *
 *  Created on: 16.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_FILELOADER_H_
#define OPGLLIB_FILELOADER_H_

#include <OpGLLib/DefaultDelete.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>

namespace OpGLLib {
class FileLoader {
public:
	FileLoader();
	FileLoader(std::string name, std::ios::openmode openmode = std::ios::in);
	FileLoader(FileLoader const& other) = delete;
	FileLoader(FileLoader&& other);
	~FileLoader();

	std::fstream *open(std::string name, std::ios::openmode openmode = std::ios::in);
	void close();

	const std::string toString();
	const char *toCString();
	std::shared_ptr<char> toCString__();

	std::fstream *getFile();
	std::string getFileType();

	operator bool();

private:
	std::fstream *file;
	std::string fileType;
};

namespace files {
size_t size(std::fstream& file);

char* dataPtr(std::fstream& file);
std::shared_ptr<char> dataSharedPtr(std::fstream& file);
std::string dataString(std::fstream& file);

std::string fileType(std::string const& file);

std::string filePath(std::string const& file);
std::string fileName(std::string const& path);
}
}

#endif /* OPGLLIB_FILELOADER_H_ */
