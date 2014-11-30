/*
 * ModelLoader.cpp
 *
 *  Created on: 30.11.2014
 *      Author: Michael
 */

#include <OpGLLib/ModelLoader.h>
#include <regex>

using namespace std;

map<unsigned int, Model> ModelLoader::models;

ModelLoader::ModelLoader() :
		FileLoader() {

}

ModelLoader::ModelLoader(const string& name, unsigned int id) :
		FileLoader(name) {
	load(name, id);
}

ModelLoader::~ModelLoader() {

}

unsigned int ModelLoader::load(const string& name, unsigned int id) {
	Model model;
	if (open(name) == NULL) {
		return -1;
	}
	if (getFileType() == "obj") {
		//--> Parse obj files:
		model = parseObj(name, id);
	}
	else {
		cerr << "Unknown fileType: " << getFileType() << endl;
		close();
		return -2;
	}
	close();
	models[id] = model;
	return id;
}

Model &ModelLoader::getModel(unsigned int id) {
	return models[id];
}

Model ModelLoader::parseObj(const string& name, unsigned int id) {
	Model model;

	model.name = name;
	model.id = id;

	string line;
	while(!getFile()->eof()) {
		getline(*getFile(), line);
		for (unsigned int i = 0; i < line.length(); i++) {
			stringstream ss;
			int x, xT, xN, y, yT, yN, z, zT, zN;
			switch(line[i]) {
			//Comment
			case '#':
				i = line.length();
				break;
			//TODO
			case 'm':
				i = line.length();
				break;
			//Object Name
			case 'o':
				//New Object
				model.count++;
				model.objects.emplace_back();
				model.objects[model.count - 1].name.assign(line.substr(i + 1));
				i = line.length();
				break;
			//Vertex
			case 'v':
				if (model.count == 0) {
					model.count++;
					model.objects.emplace_back();
				}
				if (line[i + 1] == ' ') {
					float x, y, z, w = 1.0f;
					ss.str(line.substr(i + 1));
					ss >> x >> y >> z >> w;
					model.objects[model.count - 1].count++;
					model.objects[model.count - 1].vertices.push_back(glm::vec4(x, y, z, w));
				}
				else if (line[i + 1] == 't') {
					float x, y;
					ss.str(line.substr(i + 2));
					ss >> x >> y;
					model.objects[model.count - 1].textureVertices.push_back(glm::vec2(x, y));
				}
				else if (line[i + 1] == 'n') {
					float x, y, z;
					ss.str(line.substr(i + 2));
					ss >> x >> y >> z;
					model.objects[model.count - 1].normals.push_back(glm::vec3(x, y, z));
				}
				break;
				//Edge smoothing
			case 's':
				if (model.count == 0) {
					model.count++;
					model.objects.emplace_back();
				}
				x = 0;
				ss.str(line.substr(i + 1));
				ss >> x;
				model.objects[model.count - 1].lineSmoothing = x;
				i = line.length();
				break;
			case 'f':
				if (model.count == 0) {
					model.count++;
					model.objects.emplace_back();
				}
				string str = line.substr(i + 1);
				regex pattern("\\d\\s\\d\\s\\d");
				smatch match;
				if (regex_search(str, match, pattern)) {
					ss.str(match[0].str());
					ss >> x >> y >> z;
					model.objects[model.count - 1].indicies.push_back(glm::ivec3(x, y, z));
				}
				else if (regex_search(str, match, pattern.assign("\\d/\\d\\s\\d/\\d\\s\\d/\\d"))) {
					ss.str(match[0].str());
					ss >> x;
					ss.get();
					ss >> xT;
					ss >> y;
					ss.get();
					ss >> yT;
					ss >> z;
					ss.get();
					ss >> zT;
					model.objects[model.count - 1].indicies.push_back(glm::ivec3(x, y, z));
					model.objects[model.count - 1].textureIndicies.push_back(glm::ivec3(xT, yT, zT));
				}
				else if (regex_search(str, match, pattern.assign("\\d//\\d\\s\\d//\\d\\s\\d//\\d"))) {
					ss.str(match[0].str());
					ss >> x;
					ss.get();
					ss.get();
					ss >> xN;
					ss >> y;
					ss.get();
					ss.get();
					ss >> yN;
					ss >> z;
					ss.get();
					ss.get();
					ss >> zN;
					model.objects[model.count - 1].indicies.push_back(glm::ivec3(x, y, z));
					model.objects[model.count - 1].normalIndicies.push_back(glm::ivec3(xN, yN, zN));
				}
				else if (regex_search(str, match, pattern.assign("\\d/\\d/\\d\\s\\d/\\d/\\d\\s\\d/\\d/\\d"))) {
					ss.str(match[0].str());
					ss >> x;
					ss.get();
					ss >> xT;
					ss.get();
					ss >> xN;
					ss >> y;
					ss.get();
					ss >> yT;
					ss.get();
					ss >> yN;
					ss >> z;
					ss.get();
					ss >> zT;
					ss.get();
					ss >> zN;
					model.objects[model.count - 1].indicies.push_back(glm::ivec3(x, y, z));
					model.objects[model.count - 1].textureIndicies.push_back(glm::ivec3(xT, yT, zT));
					model.objects[model.count - 1].normalIndicies.push_back(glm::ivec3(xN, yN, zN));
				}
				i = line.length();
			}
		}
	}

	return model;
}
