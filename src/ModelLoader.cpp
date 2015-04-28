/*
 * ModelLoader.cpp
 *
 *  Created on: 30.11.2014
 *      Author: Michael
 */

#include <OpGLLib/ModelLoader.h>

using namespace std;

ObjectBase::~ObjectBase() {

}

ModelBase::~ModelBase() {

}

std::string& Object::getName() {
	return name;
}
int& Object::getVerticesCount() {
	return count;
}
int& Object::getLineSmoothing() {
	return lineSmoothing;
}
std::vector<glm::vec4>& Object::getVertices() {
	return vertices;
}
std::vector<glm::vec2>& Object::getTextureVertices() {
	return textureVertices;
}
std::vector<glm::vec3>& Object::getNormals() {
	return normals;
}
std::vector<glm::uvec3>& Object::getIndicies() {
	return indicies;
}
gl::GLenum Object::getIndiciesType() {
	return gl::GL_UNSIGNED_INT;
}
const void* Object::getIndiciesOffset() {
	return static_cast<const void*>(0);
}
std::vector<glm::uvec3>& Object::getTextureIndicies() {
	return textureIndicies;
}
std::vector<glm::uvec3>& Object::getNormalIndicies() {
	return normalIndicies;
}

void Object::setName(std::string name) {
	Object::name = std::move(name);
}
void Object::setVerticesCount(int count) {
	Object::count = count;
}
void Object::setLineSmoothing(int lineSmoothing) {
	Object::lineSmoothing = lineSmoothing;
}
void Object::setVertices(std::vector<glm::vec4> vertices) {
	Object::vertices = std::move(vertices);
}
void Object::setTextureVertices(std::vector<glm::vec2> textureVertices) {
	Object::textureVertices = std::move(textureVertices);
}
void Object::setNormals(std::vector<glm::vec3> normals) {
	Object::normals = std::move(normals);
}
void Object::setIndicies(std::vector<glm::uvec3> indicies) {
	Object::indicies = std::move(indicies);
}
void Object::setIndiciesType(gl::GLenum indiciesType) {
	//HardCoded
}
void Object::setIndiciesOffset(const void* indiciesOffset) {
	//HardCoded
}
void Object::setTextureIndicies(std::vector<glm::uvec3> textureIndicies) {
	Object::textureIndicies = std::move(textureIndicies);
}
void Object::setNormalIndicies(std::vector<glm::uvec3> normalIndicies) {
	Object::normalIndicies = std::move(normalIndicies);
}

std::string& Model::getName() {
	return name;
}
unsigned int Model::getId() {
	return id;
}
int& Model::getObjectCount() {
	return count;
}
int& Model::getLoadedState() {
	return loaded;
}
std::shared_ptr<ObjectBase> Model::getObject(int id) {
	return objects[id];
}

void Model::setName(std::string name) {
	Model::name = std::move(name);
}
void Model::setId(unsigned int id) {
	Model::id = id;
}
void Model::setObjectCount(int count) {
	Model::count = count;
}
void Model::setLoadedState(int loadedState) {
	Model::loaded = loadedState;
}
void Model::setObject(int id, std::shared_ptr<ObjectBase> object) {
	objects[id] = object;
}

void Model::addObject(std::shared_ptr<ObjectBase> object) {
	objects.push_back(object);
}

ModelLoader::ModelLoader() :
		FileLoader() {

}

ModelLoader::ModelLoader(const string& name, unsigned int id) :
		FileLoader(name) {
	load(name, id);
}

ModelLoader::~ModelLoader() {

}

unsigned int ModelLoader::reserve(const string& name, unsigned int id) {
	if (open(name) == NULL) {
		return -1;
	}
	close();
	std::shared_ptr<ModelBase>& model = models[id];
	if (!model) {
		model.reset(new Model, OpGLLib::default_delete<ModelBase>());
		model->setName(name);
		model->setId(id);
		model->setLoadedState(false);
	}
	return id;
}

unsigned int ModelLoader::load(const string& name, unsigned int id) {
	std::shared_ptr<ModelBase>& model = models[id];
	if (!model) {
		model.reset(new Model, OpGLLib::default_delete<ModelBase>());
	}
	if (open(name) == NULL) {
		return -1;
	}
	if (getFileType() == "obj") {
		//--> Parse obj files:
		parseObj(model, name, id);
	}
	else {
		cerr << "Unknown fileType: " << getFileType() << endl;
		close();
		return -2;
	}

	close();
	model->setLoadedState(true);
	return id;
}

unsigned int ModelLoader::unload(unsigned int id) {
	models.erase(id);
	return id;
}

std::shared_ptr<ModelBase> ModelLoader::getModel(unsigned int id) {
	if (!models[id]->getLoadedState()) {
		load(models[id]->getName(), id);
	}
	return models[id];
}

void ModelLoader::parseObj(std::shared_ptr<ModelBase>& model, const string& name, unsigned int id) {
	model->setName(name);
	model->setId(id);

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
				model->getObjectCount()++;
				model->addObject(std::shared_ptr<ObjectBase>(new Object, OpGLLib::default_delete<ObjectBase>()));
				model->getObject(model->getObjectCount() - 1)->setName(line.substr(i + 1));
				i = line.length();
				break;
			//Vertex
			case 'v':
				if (model->getObjectCount() == 0) {
					model->getObjectCount()++;
					model->addObject(std::shared_ptr<ObjectBase>(new Object, OpGLLib::default_delete<ObjectBase>()));
				}
				if (line[i + 1] == ' ') {
					float x, y, z, w = 1.0f;
					ss.str(line.substr(i + 1));
					ss >> x >> y >> z >> w;
					//model.objects[model.count - 1].count++;
					//model.objects[model.count - 1].vertices.push_back(glm::vec4(x, y, z, w));
					model->getObject(model->getObjectCount() - 1)->getVerticesCount()++;
					model->getObject(model->getObjectCount() - 1)->getVertices().push_back(glm::vec4(x, y, z, w));
				}
				else if (line[i + 1] == 't') {
					float x, y;
					ss.str(line.substr(i + 2));
					ss >> x >> y;
					//model.objects[model.count - 1].textureVertices.push_back(glm::vec2(x, y));
					model->getObject(model->getObjectCount() - 1)->getTextureVertices().push_back(glm::vec2(x, y));
				}
				else if (line[i + 1] == 'n') {
					float x, y, z;
					ss.str(line.substr(i + 2));
					ss >> x >> y >> z;
					//model.objects[model.count - 1].normals.push_back(glm::vec3(x, y, z));
					model->getObject(model->getObjectCount() - 1)->getNormals().push_back(glm::vec3(x, y, z));
				}
				i = line.length();
				break;
				//Edge smoothing
			case 's':
				if (model->getObjectCount() == 0) {
					model->getObjectCount()++;
					model->addObject(std::shared_ptr<ObjectBase>(new Object, OpGLLib::default_delete<ObjectBase>()));
				}
				x = 0;
				ss.str(line.substr(i + 1));
				ss >> x;
				//model.objects[model.count - 1].lineSmoothing = x;
				model->getObject(model->getObjectCount() - 1)->setLineSmoothing(x);
				i = line.length();
				break;
			case 'f':
				if (model->getObjectCount() == 0) {
					model->getObjectCount()++;
					model->addObject(std::shared_ptr<ObjectBase>(new Object, OpGLLib::default_delete<ObjectBase>()));
				}
				string str = line.substr(i + 1);
				regex pattern("\\d+\\s\\d+\\s\\d+");
				smatch match;
				if (regex_search(str, match, pattern)) {
					ss.str(match[0].str());
					ss >> x >> y >> z;
					//model.objects[model.count - 1].indicies.push_back(glm::uvec3(--x, --y, --z));
					model->getObject(model->getObjectCount() - 1)->getIndicies().push_back(glm::uvec3(--x, --y, --z));
				}
				else if (regex_search(str, match, pattern.assign("\\d+/\\d+\\s\\d+/\\d+\\s\\d+/\\d+"))) {
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
					//model.objects[model.count - 1].indicies.push_back(glm::uvec3(--x, --y, --z));
					//model.objects[model.count - 1].textureIndicies.push_back(glm::uvec3(--xT, --yT, --zT));
					model->getObject(model->getObjectCount() - 1)->getIndicies().push_back(glm::uvec3(--x, --y, --z));
					model->getObject(model->getObjectCount() - 1)->getTextureIndicies().push_back(glm::uvec3(--xT, --yT, --zT));
				}
				else if (regex_search(str, match, pattern.assign("\\d+//\\d+\\s\\d+//\\d+\\s\\d+//\\d+"))) {
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
					//model.objects[model.count - 1].indicies.push_back(glm::uvec3(--x, --y, --z));
					//model.objects[model.count - 1].normalIndicies.push_back(glm::uvec3(--xN, --yN, --zN));
					model->getObject(model->getObjectCount() - 1)->getIndicies().push_back(glm::uvec3(--x, --y, --z));
					model->getObject(model->getObjectCount() - 1)->getNormalIndicies().push_back(glm::uvec3(--xN, --yN, --zN));
				}
				else if (regex_search(str, match, pattern.assign("\\d+/\\d+/\\d+\\s\\d+/\\d+/\\d+\\s\\d+/\\d+/\\d+"))) {
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
					//model.objects[model.count - 1].indicies.push_back(glm::uvec3(--x, --y, --z));
					//model.objects[model.count - 1].textureIndicies.push_back(glm::uvec3(--xT, --yT, --zT));
					//model.objects[model.count - 1].normalIndicies.push_back(glm::uvec3(--xN, --yN, --zN));
					model->getObject(model->getObjectCount() - 1)->getIndicies().push_back(glm::uvec3(--x, --y, --z));
					model->getObject(model->getObjectCount() - 1)->getTextureIndicies().push_back(glm::uvec3(--xT, --yT, --zT));
					model->getObject(model->getObjectCount() - 1)->getNormalIndicies().push_back(glm::uvec3(--xN, --yN, --zN));
				}
				i = line.length();
			}
		}
	}

}
