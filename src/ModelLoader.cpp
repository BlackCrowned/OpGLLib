/*
 * ModelLoader.cpp
 *
 *  Created on: 30.11.2014
 *      Author: Michael
 */

#include <OpGLLib/ModelLoader.h>

using namespace std;

ModelLoader::ModelLoader() :
		FileLoader() {

}

ModelLoader::ModelLoader(string name, int id) :
		FileLoader(name) {
	load(name, id);
}

ModelLoader::~ModelLoader() {

}

int ModelLoader::load(string name, int id) {
	if (open(name) == NULL) {
		return -1;
	}
	if (getFileType() == "obj") {
		//--> Parse obj files;
	}
	else {
		cerr << "Unknow fileType: " << getFileType() << endl;
		return -2;
	}
	return id;
}

Model &ModelLoader::getModel(int id) {
	return models[id];
}
