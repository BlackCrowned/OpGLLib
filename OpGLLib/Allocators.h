/*
 * Allocators.h
 *
 *  Created on: 07.12.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_ALLOCATORS_H_
#define OPGLLIB_ALLOCATORS_H_

#include <OpGLLib/internal.h>

template<class T>
class Allocator {
public:
	Allocator();
	Allocator(Allocator<T> const& other) = default;
	Allocator(Allocator<T> && other) = default;
	~Allocator();

	template<class ...Args> T *constructObject(Args&&... args) {
		objects.push_back(new T(std::forward<Args>(args)...));
		return objects.back();
	}
	T *constructObject(T&& object);
	T *constructObject(T* object);
	void deleteObject(T&& object);
	void deleteObject(T* object);
	void deleteObjects();

protected:
	std::vector<T *> objects;
};

template<class T>
class FileAllocator: public Allocator<T> {
public:
	FileAllocator();
	~FileAllocator();

	template<class ...Args> T *openFile(Args&&... args) {
		return Allocator<T>::constructObject(std::forward<Args>(args)...);
	}
	template<class ...Args> T *openFile(T* file, Args&&... args) {
		closeFile(file);
		file->open(std::forward<Args>(args)...);
		return file;
	}
	void closeFile(T* file);
	void closeFile(T&& file);
	void closeFiles();
};

template class Allocator<std::fstream> ;
template class FileAllocator<std::fstream> ;

#endif /* OPGLLIB_ALLOCATORS_H_ */
