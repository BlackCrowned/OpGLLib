/*
 * Allocators.h
 *
 *  Created on: 07.12.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_ALLOCATORS_H_
#define OPGLLIB_ALLOCATORS_H_

#include <deque>
#include <iostream>
#include <fstream>

template<class T>
class Allocator {
public:
	Allocator() = default;
	Allocator(Allocator const& other) = default;
	Allocator(Allocator&& other) = default;
	~Allocator() {
	}

	template<class U> struct rebind {
		typedef Allocator<U> other;
	};

	T* allocate(int n = 1) {
		return reinterpret_cast<T*>(::operator new(sizeof(T) * n));
	}
	void deallocate(T* ptr, int n = 1) {
		::operator delete(reinterpret_cast<void*>(ptr));
	}

	template<class U, class ...Args>
	void construct(int n, U* ptr, Args&&... args) {
		for (auto i = 0; i < n; i++) {
			::new (reinterpret_cast<void*>(ptr + i)) U(std::forward<Args>(args)...);
		}
	}
	template<class U, class ...Args>
	void construct(U* ptr, Args&&... args) {
		::new (reinterpret_cast<void*>(ptr)) U(std::forward<Args>(args)...);
	}
	template<class U>
	void destroy(U* ptr, int n) {
		for (auto i = 0; i < n; i++) {
			(ptr + i)->~U();
		}
	}
	template<class U>
	void destroy(U* ptr) {
		ptr->~U();
	}
};

template<class T>
class MemManager {
public:
	MemManager() {
		std::cout << "MemManager constructed!" << std::endl;
	}
	MemManager(MemManager<T> const& other) = default;
	MemManager(MemManager<T> && other) = default;
	~MemManager() {
		std::cout << "Destructing MemManager..." << std::endl;
		destroyAll();
		deallocateAll();
		std::cout << "MemManager successfully destructed!" << std::endl;
	}

	template<class ...Args> T* construct(Args&&... args) {
		int i = nextFree();
		T* tmp = allocated[i];
		constructed.push_back(tmp);
		allocated.erase(allocated.begin() + i);
		allocator.construct(tmp, std::forward<Args>(args)...);
		return tmp;
	}
	template<class container, class ...Args> void constructN(size_t n, container& c, Args&&...args) {
		int i = /*nextFreeRange(n)*/ -1;
		if (i != -1) {
			for (size_t j = 0; j < n; j++) {
				//allocator.construct(n, allocated[i], std::forward<Args>(args)...);
				c.push_back(allocated[i]);
				constructed.push_back(allocated[i]);
				allocated.erase(allocated.begin() + i);
			}
		} else {
			for (size_t i = 0; i < n; i++) {
				c.push_back(construct(std::forward<Args>(args)...));
			}
		}
	}

	T *manage(T&& object) {
		std::cout << "Called: MemManager::manage(object)" << std::endl;
		constructed.push_back(&object);
		return &object;
	}
	T *manage(T* object) {
		std::cout << "Called: MemManager::manage(" << object << ")" << std::endl;
		constructed.push_back(object);
		return object;
	}

	void destroy(T&& object) {
		destroy(&object);
	}
	void destroy(T* object) {
		int i = constructedPos(object);
		if (i != -1) {
			allocator.destroy(object);
			markFree(constructed[i]);
			constructed.erase(constructed.begin() + i);
			deallocateMemory(0);
		}

	}

	T* release(T&& object) {
		return release(&object);
	}
	T* release(T* object) {
		int i = constructedPos(object);
		if (i != -1) {
			constructed.erase(constructed.begin() + i);
		}
		return object;
	}

	void destroyAll() {
		std::cout << "Called: MemManager::destroyAll()" << std::endl;
		for (auto i : constructed) {
			allocator.destroy(i);
			markFree(i);
		}
		constructed.clear();
	}
	void deallocateAll() {
		std::cout << "Called: MemManager::deallocateAll()" << std::endl;
		for (auto i : allocated) {
			allocator.deallocate(i, 1);
		}
	}

private:
	Allocator<T> allocator;
	std::deque<T*> allocated;
	std::deque<T*> constructed;
	size_t lastAutoResize = 1;

	void allocateMemory(size_t n) {
		std::cout << "Called: MemManager::allocateMemory(" << n << ")" << std::endl;
		while (allocated.size() < n) {
			lastAutoResize *= 2;
			std::cout << "Increased allocated memory by " << lastAutoResize << std::endl;
			for (size_t i = 0; i < lastAutoResize; i++) {
				markFree(allocator.allocate(1));
			}
		}
	}
	void deallocateMemory(size_t n) {
		while (allocated.size() > n + lastAutoResize + 1) {
			std::cout << "Decreased allocated memory by " << lastAutoResize << std::endl;
			int tmp = /*nextFreeRange(lastAutoDecrease)*/-1;
			if (tmp != -1) {
				std::cout << "Sorry but you just found a freeRange" << std::endl;
				//allocator.deallocate(allocated[tmp], lastAutoDecrease);
			} else {
				for (size_t i = 0; i < lastAutoResize; i++) {
					allocator.deallocate(allocated[nextFree()], 1);
					allocated.erase(allocated.begin());
				}
			}
		}
	}

	void markFree(T* p) {
		size_t i = 0;
		while (i < allocated.size() && allocated[i] < p) {
			i++;
		}
		if (i == allocated.size()) {
			allocated.push_back(p);
		} else {
			allocated.insert(allocated.begin() + i, p);
		}
	}

	int nextFreeRange(size_t n) {
		if (n < 1) {
			return -1;
		}
		if (allocated.size() < n) {
			allocateMemory(n - allocated.size());
		}
		size_t start = 0;
		size_t current = 1;
		for (size_t i = 0; i < allocated.size(); i++) {
			if ((current - start) + (allocated.size() - current) < n) {
				return -1;
			}
			if (allocated[start] + 1 == allocated[current]) {
				if (current - start == n) {
					return start;
				}
				current++;
			} else {
				start = current++;
			}
		}
		return -1;
	}

	int nextFree() {
		if (allocated.size() < 1) {
			allocateMemory(1);
		}
		return 0;
	}

	int constructedPos(T* p) {
		for (size_t i = 0; i < constructed.size(); i++) {
			if (constructed[i] == p) {
				return i;
			}
		}
		return -1;
	}

};

template<class T>
class FileAllocator: public MemManager<T> {
public:
	FileAllocator();
	~FileAllocator();

	template<class ...Args> T *openFile(Args&&... args) {
		return MemManager<T>::construct(std::forward<Args>(args)...);
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

template class FileAllocator<std::fstream> ;

#endif /* OPGLLIB_ALLOCATORS_H_ */
