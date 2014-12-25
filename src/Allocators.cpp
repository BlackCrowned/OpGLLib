/*
 * Allocators.cpp
 *
 *  Created on: 07.12.2014
 *      Author: Michael
 */

#include <OpGLLib/Allocators.h>

using namespace std;

template<class T> Allocator<T>::Allocator() {

}

template<class T> Allocator<T>::~Allocator() {
	deleteObjects();
}

template<class T> T *Allocator<T>::constructObject(T&& object) {
	objects.push_back(&object);
	return &object;
}

template<class T> T* Allocator<T>::constructObject(T* object) {
	objects.push_back(object);
	return object;
}

template<class T> void Allocator<T>::deleteObject(T&& object) {
	deleteObject(&object);
}

template<class T> void Allocator<T>::deleteObject(T *object) {
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i] == object) {
			delete objects[i];
			objects.erase(objects.begin() + i--);
		}
	}
}

template<class T> void Allocator<T>::deleteObjects() {
	for (auto i : objects) {
		delete i;
	}
	objects.clear();
}

template<class T> FileAllocator<T>::FileAllocator() :
		Allocator<T>::Allocator() {

}

template<class T> FileAllocator<T>::~FileAllocator() {
	closeFiles();
}

//template<class T> template<class ...Args> T *FileAllocator<T>::openFile(Args&&... args) {
//	return constructObject(args...);
//}

//template<class T> template<class ...Args> T *FileAllocator<T>::openFile(T& file, Args&&... args) {
//	file.open(args...);
//	return &file;
//}

template<class T> void FileAllocator<T>::closeFile(T&& file) {
	if (file.is_open()) {
		file.close();
	}
}

template<class T> void FileAllocator<T>::closeFile(T *file) {
	if (file->is_open()) {
		file->close();
	}
}

template<class T> void FileAllocator<T>::closeFiles() {
	for (auto i : Allocator<T>::objects) {
		if (i->is_open()) {
			i->close();
		}
	}
}
