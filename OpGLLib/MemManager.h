/*
 * MemManager.h
 *
 *  Created on: 07.12.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_MEMMANAGER_H_
#define OPGLLIB_MEMMANAGER_H_

#include <deque>
#include <iostream>

template<class T>
class MemManager {
public:
	MemManager();
	MemManager(MemManager<T> const& other) = default;
	MemManager(MemManager<T> && other) = default;
	~MemManager();

	MemManager& operator=(MemManager other);

	template<class ...Args> T* construct(Args&&... args);
	template<class container, class ...Args> void constructN(size_t n, container& c, Args&&...args);

	T *manage(T&& object, size_t n = 1);
	T *manage(T* object, size_t n = 1);

	void destroy(T&& object);
	void destroy(T* object);

	T* release(T&& object, size_t n = 1);
	T* release(T* object, size_t n = 1);

	void reserve(size_t amount);

	void destroyAll();
	void deallocateAll();

private:
	void requestAllocation(size_t amount);
	void requestDeallocation();

	int nextEmptyBlock();
	int nextAvailableBlock();

	struct Block;
	std::deque<Block> blockTable;
	size_t totalFree = 0;
	size_t totalUsed = 0;
	size_t firstAvailableBlock = 0;
	size_t medianAllocationSize = 0;
	std::allocator<T> allocator;
};

#include <OpGLLib/MemManager.inl>

#endif /* OPGLLIB_MEMMANAGER_H_ */
