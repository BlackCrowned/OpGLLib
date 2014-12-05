/*
 * FileLoader.h
 *
 *  Created on: 16.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_FILELOADER_H_
#define OPGLLIB_FILELOADER_H_

#include <OpGLLib/internal.h>

class FileLoader {
public:
	FileLoader();
	FileLoader(std::string name, std::ios::openmode openmode = std::ios::in);
	~FileLoader();

	std::fstream *open(std::string name, std::ios::openmode openmode = std::ios::in);
	void close();

	const std::string toString();

	std::fstream *getFile();
	std::string getFileType();

private:
	std::fstream file;
	std::string fileType;
};


#endif /* OPGLLIB_FILELOADER_H_ */
