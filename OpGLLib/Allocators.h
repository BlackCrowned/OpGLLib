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
	}
	MemManager(MemManager<T> const& other) = default;
	MemManager(MemManager<T> && other) = default;
	~MemManager() {
		destroyAll();
		deallocateAll();
	}

	template<class ...Args> T* construct(Args&&... args) {
		requestAllocation(1);
		int block = nextAvailableBlock();
		if (block == -1) {
			std::cerr << "Error: No blocks to construct in available" << std::endl;
			return nullptr;
		}
		int i = blockTable[block].nextAvailable();
		if (i == -1) {
			std::cerr << "Error: Block was indeed full" << std::endl;
			return nullptr;
		}
		totalFree--;
		totalUsed++;
		allocator.construct(blockTable[block].construct(i), std::forward<Args>(args)...);
		return blockTable[block][i];
	}
	template<class container, class ...Args> void constructN(size_t n, container& c, Args&&...args) {
		requestAllocation(n);
		for (size_t i = 0; i < n; i++) {
			c.push_back(construct(std::forward<Args>(args)...));
		}
	}

	T *manage(T&& object) {
		manage(&object);
		return &object;
	}
	T *manage(T* object) {
		Block managedBlock(1, object, false, true);
		totalUsed++;
		blockTable.push_back(std::move(managedBlock));
		return object;
	}

	void destroy(T&& object) {
		destroy(&object);
	}
	void destroy(T* object) {
		for (size_t i = 0; i < blockTable.size(); i++) {
			if (!blockTable[i].empty) {
				if (object >= blockTable[i].first && object <= blockTable[i][blockTable[i].size]) {
					for (size_t j = 0; j < blockTable[i].size; j++) {
						if (blockTable[i][j] == object) {
							totalFree++;
							totalUsed--;
							allocator.destroy(blockTable[i].destroy(j));
							requestDeallocation();
							return;
						}
					}
				}
			}
		}
		std::cerr << "Coudn't find object@" << object << "!" << std::endl;
	}

	T* release(T&& object) {
		return release(&object);
	}
	T* release(T* object) {
		for (size_t i = 0; i < blockTable.size(); i++) {
			if (!blockTable[i].empty && blockTable[i].size == 1) {
				for (size_t j = 0; j < blockTable[i].size; j++) {
					if (blockTable[i][j] == object) {
						blockTable.erase(blockTable.begin() + i);
						return object;
					}
				}
			}
		}
		return nullptr;
	}

	void destroyAll() {
		for (size_t i = 0; i < blockTable.size(); i++) {
			if (!blockTable[i].empty) {
				for (size_t j = 0; j < blockTable[i].size; j++) {
					totalFree++;
					totalUsed--;
					allocator.destroy(blockTable[i].destroy(j));
				}
				requestDeallocation();
			}
		}
		return;
	}
	void deallocateAll() {
		for (size_t i = 0; i < blockTable.size(); i++) {
			totalFree--;
			allocator.deallocate(blockTable[i].first, blockTable[i].size);
		}
	}

private:
	struct Block {
		Block(size_t _size, T* _first, bool _empty = true, bool _full = false) {
			size = _size;
			empty = _empty;
			full = _full;
			first = _first;
			available = new bool[size];
			for (size_t i = 0; i < size; i++) {
				available[i] = true;
			}
			amountAvailable = size;
		}
		Block(Block const& other) {
			size = other.size;
			empty = other.empty;
			full = other.full;
			first = other.first;
			available = new bool[size];
			for (size_t i = 0; i < size; i++) {
				available[i] = other.available[i];
			}
			firstAvailable = other.firstAvailable;
			amountAvailable = other.amountAvailable;
		}
		Block(Block&& other) {
			size = other.size;
			empty = other.empty;
			full = other.full;
			first = other.first;
			available = other.available;
			other.available = nullptr;
			firstAvailable = other.firstAvailable;
			amountAvailable = other.amountAvailable;
		}
		~Block() {
			delete[] available;
		}

		Block& operator =(Block const& other) {
			this->size = other.size;
			this->empty = other.empty;
			this->full = other.full;
			this->first = other.first;
			this->available = new bool[this->size];
			for (size_t i = 0; i < this->size; i++) {
				this->available[i] = other.available[i];
			}
			this->firstAvailable = other.firstAvailable;
			this->amountAvailable = other.amountAvailable;
			return *this;
		}

		size_t size;
		bool empty;
		bool full;
		T* first;
		bool *available;
		int firstAvailable = 0;
		size_t amountAvailable;

		int nextAvailable() {
			if (full) {
				return -1;
			}
			if (available[firstAvailable]) {
				return firstAvailable;
			}
			for (size_t i = firstAvailable; i < size; i++) {
				if (available[i]) {
					firstAvailable = i;
					return i;
				}
			}
			//Try again starting from 0
			for (size_t i = 0; i < size; i++) {
				if (available[i]) {
					firstAvailable = i;
					return i;
				}
			}
			full = true;
			return -1;
		}
		T* operator [](int i) {
			return first + i;
		}
		T* construct(int i) {
			if (amountAvailable == 1) {
				full = true;
			} else {
				full = false;
			}
			empty = false;
			amountAvailable--;
			available[i] = false;
			return first + i;
		}
		T* destroy(int i) {
			if (amountAvailable == size - 1) {
				empty = true;
			} else {
				empty = false;
			}
			full = false;
			amountAvailable++;
			available[i] = true;
			return first + i;
		}
	};
	std::deque<Block> blockTable;
	size_t totalFree = 0;
	size_t totalUsed = 0;
	int firstAvailableBlock = 0;
	size_t medianBlockSize = 0;
	Allocator<T> allocator;

	void requestAllocation(size_t amount) {
		if (amount <= totalFree) {
			return;
		}
		size_t amountToAllocate = amount - totalFree;
		T* first = allocator.allocate(amountToAllocate);
		Block newBlock(amountToAllocate, first);
		blockTable.push_back(std::move(newBlock));
		totalFree += amountToAllocate;
		medianBlockSize = (medianBlockSize * blockTable.size() + amountToAllocate) / (blockTable.size() + 1);
		return;
	}
	void requestDeallocation() {
		if (totalFree > 2 * medianBlockSize) {
			int i = nextEmptyBlock();
			if (i != -1) {
				totalFree -= blockTable[i].size;
				allocator.deallocate(blockTable[i].first);
				blockTable.erase(blockTable.begin() + i);
			}
		}
	}

	int nextEmptyBlock() {
		for (size_t i = 0; i < blockTable.size(); i++) {
			if (blockTable[i].empty) {
				return i;
			}
		}
		return -1;
	}

	int nextAvailableBlock() {
		if (!blockTable[firstAvailableBlock].full) {
			return firstAvailableBlock;
		}
		for (size_t i = firstAvailableBlock; i < blockTable.size(); i++) {
			if (!blockTable[i].full) {
				firstAvailableBlock = i;
				return i;
			}
		}
		//Try again starting from 0
		for (size_t i = 0; i < blockTable.size(); i++) {
			if (!blockTable[i].full) {
				firstAvailableBlock = i;
				return i;
			}
		}
		return -1;
	}
};

#endif /* OPGLLIB_ALLOCATORS_H_ */
