/*
 * FileLoader.h
 *
 *  Created on: 16.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_FILELOADER_H_
#define OPGLLIB_FILELOADER_H_

#include <fstream>
#include <string>
#include <sstream>
#include <OpGLLib/Allocators.h>

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

	std::fstream *getFile();
	std::string getFileType();

private:
	std::fstream *file;
	std::string fileType;
};

#endif /* OPGLLIB_FILELOADER_H_ */
