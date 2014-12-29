/*
 * Allocators.cpp
 *
 *  Created on: 07.12.2014
 *      Author: Michael
 */

#include <OpGLLib/Allocators.h>

using namespace std;

template<class T> FileAllocator<T>::FileAllocator() {

}

template<class T> FileAllocator<T>::~FileAllocator() {
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
