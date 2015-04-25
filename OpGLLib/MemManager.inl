/*!
 * @class MemManager
 * @brief Automatically manages allocation and deallocation
 * @tparam T Type of object
 */

namespace OpGLLib {
/*!
 * @brief Default constructor
 */
template<class T>
MemManager<T>::MemManager() {

}
/*!
 * @fn MemManager<T>::MemManager(MemManager const& other)
 * @brief Copy constructor
 */
/*!
 * @fn MemManager<T>::MemManager(MemManager&& other)
 * @brief Move constructor
 */

/*!
 * @brief Destructor
 * @details Destructs all objects and Deallocates allocated storage.
 */
template<class T>
MemManager<T>::~MemManager() {
	destroyAll();
	deallocateAll();
}

/*!
 * @brief Copy and Swap assignment operator
 */
template<class T>
MemManager<T>& MemManager<T>::operator=(MemManager<T> other) {
	std::swap(blockTable, other.blockTable);
	std::swap(totalUsed, other.totalUsed);
	std::swap(totalFree, other.totalFree);
	std::swap(firstAvailableBlock, other.firstAvailableBlock);
	std::swap(medianAllocationSize, other.medianAllocationSize);
	return *this;
}

/*!
 * @brief Constructs object
 * @details Only allocates additional storage if not enough storage allocated
 * @param args Arguments to pass to object constructor
 * @return Pointer to constructed object
 */
template<class T>
template<class ...Args>
T* MemManager<T>::construct(Args&& ...args) {
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

/*!
 * @brief Constructs n objects
 * @details Only allocates additional storage if not enough storage allocated
 * @tparam container Any container that supports `.push_back()`
 * @param n Amount of objects to construct
 * @param c Container to store pointer to constructed objects
 * @param args Arguments to pass to object constructor (no copy made)
 */
template<class T>
template<class container, class ...Args>
void MemManager<T>::constructN(size_t n, container& c, Args&& ...args) {
	requestAllocation(n);
	for (size_t i = 0; i < n; i++) {
		c.push_back(construct(std::forward<Args>(args)...));
	}
}

/*!
 * @brief Allows MemManager to manage storage for an object
 * @details Address of `object` won't change
 * @param object %Object to manage
 * @param n Amount of objects to manage
 * @return Pointer to managed object
 */
template<class T>
T* MemManager<T>::manage(T&& object, size_t n) {
	manage(&object, n);
	return &object;
}

/*!
 * @brief Allows MemManager to manage storage for an object
 * @details Address of `object` won't change
 * @param object Pointer to object to manage
 * @param n Amount of objects to manage
 * @return Pointer to managed object
 */
template<class T>
T* MemManager<T>::manage(T* object, size_t n) {
	Block managedBlock(n, object, true);
	totalUsed += n;
	blockTable.push_back(std::move(managedBlock));
	return object;
}

/*!
 * @brief Destructs a previously constructed object
 * @param object %Object to destruct
 * @throw Throws "Coudn't find object!" on error
 */
template<class T>
void MemManager<T>::destroy(T&& object) {
	destroy(&object);
}

/*!
 * @brief Destructs a previously constructed object
 * @param object Pointer to object to destruct
 * @throw Throws "Coudn't find object!" on error
 */
template<class T>
void MemManager<T>::destroy(T* object) {
	for (size_t i = 0; i < blockTable.size(); i++) {
		if (!blockTable[i].empty) {
			if (object >= blockTable[i].first && object < blockTable[i][blockTable[i].size]) {
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
	throw "Coudn't find object!";
}

/*!
 * @brief Releases objects from MemManager
 * @details - Can be used to reclaim storage control for objects
 * - Can be used to claim storage control for objects as long as n equals the size of the allocated storage block
 * - Can be used to claim storage control for objects by moving/copying objects out of allocated storage blocks
 * @param object First object to release
 * @param n Amount of objects to release
 * @return Pointer to released objects
 */
template<class T>
T* MemManager<T>::release(T&& object, size_t n) {
	return release(&object, n);
}

/*!
 * @brief Releases objects from MemManager
 * @details - Can be used to reclaim storage control for objects
 * - Can be used to claim storage control for objects as long as n equals the size of the allocated storage block
 * - Can be used to claim storage control for objects by moving/copying objects out of allocated storage blocks
 * @param object Pointer to first object to release
 * @param n Amount of objects to release
 * @return Pointer to released objects
 */
template<class T>
T* MemManager<T>::release(T* object, size_t n) {
	for (size_t i = 0; i < blockTable.size(); i++) {
		if (!blockTable[i].empty) {
			if (object >= blockTable[i].first && object < blockTable[i][blockTable[i].size]) {
				if (blockTable[i].size == n && blockTable[i][0] == object) {
					totalUsed -= n;
					blockTable.erase(blockTable.begin() + i);
					return object;
				} else {
					for (size_t j = 0; j < blockTable[i].size; j++) {
						if (blockTable[i][j] == object && j + n <= blockTable[i].size) {
							T* newFirst = allocator.allocate(n);
							for (size_t x = 0; x < n; x++) {
								T* tmp = newFirst + x;
								allocator.construct(tmp, std::move(*blockTable[i].destroy(j + x)));
								totalUsed--;
								totalFree++;
							}
							requestDeallocation();
							return newFirst;
						}
					}
				}

			}
		}
	}
	return nullptr;
}

/*!
 * @brief Reserves storage
 * @param amount Amount to reserve
 */
template<class T>
void MemManager<T>::reserve(size_t amount) {
	requestAllocation(amount);
}

/*!
 * @brief Destructs all objects
 */
template<class T>
void MemManager<T>::destroyAll() {
	for (size_t i = 0; i < blockTable.size(); i++) {
		if (!blockTable[i].empty) {
			for (size_t j = 0; j < blockTable[i].size; j++) {
				totalFree++;
				totalUsed--;
				allocator.destroy(blockTable[i].destroy(j));
			}
		}
	}
	return;
}

/*!
 * @brief Deallocates <b>ALL</b> storage
 * @details <b>Won't</b> call destructors
 */
template<class T>
void MemManager<T>::deallocateAll() {
	for (size_t i = 0; i < blockTable.size(); i++) {
		totalFree--;
		allocator.deallocate(blockTable[i].first, blockTable[i].size);
	}
	blockTable.clear();
	totalUsed = 0;
}

template<class T>
struct MemManager<T>::Block {
	Block(size_t _size, T* _first, bool _full = false);
	Block(Block const& other);
	Block(Block&& other);
	~Block();

	Block& operator =(Block&& other);

	int nextAvailable();
	T* operator [](size_t i);
	T* construct(size_t i);
	T* destroy(size_t i);

	size_t size;
	bool empty;
	bool full;
	T* first;
	bool* available;
	size_t firstAvailable = 0;
	size_t amountAvailable;
};

template<class T>
MemManager<T>::Block::Block(size_t _size, T* _first, bool _full) {
	size = _size;
	empty = !_full;
	full = _full;
	first = _first;
	available = new bool[size];
	for (size_t i = 0; i < size; i++) {
		available[i] = !_full;
	}
	amountAvailable = !_full ? size : 0;
}

template<class T>
MemManager<T>::Block::Block(Block const& other) {
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

template<class T>
MemManager<T>::Block::Block(Block&& other) {
	size = other.size;
	empty = other.empty;
	full = other.full;
	first = other.first;
	available = other.available;
	other.available = nullptr;
	firstAvailable = other.firstAvailable;
	amountAvailable = other.amountAvailable;
}

template<class T>
MemManager<T>::Block::~Block() {
	delete[] available;
}

template<class T>
auto MemManager<T>::Block::operator =(Block&& other) -> Block& {
	if (this != &other) {
		Block tmp(std::forward < Block > (other));
		std::swap(size, tmp.size);
		std::swap(empty, tmp.empty);
		std::swap(full, tmp.full);
		std::swap(first, tmp.first);
		std::swap(available, tmp.available);
		std::swap(firstAvailable, tmp.firstAvailable);
		std::swap(amountAvailable, tmp.amountAvailable);
	} else {
		std::cout << "this == &other" << std::endl;
	}
	return *this;
}

template<class T>
int MemManager<T>::Block::nextAvailable() {
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
	for (size_t i = 0; i < firstAvailable; i++) {
		if (available[i]) {
			firstAvailable = i;
			return i;
		}
	}
	full = true;
	return -1;
}

template<class T>
T* MemManager<T>::Block::operator [](size_t i) {
	return first + i;
}

template<class T>
T* MemManager<T>::Block::construct(size_t i) {
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

template<class T>
T* MemManager<T>::Block::destroy(size_t i) {
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

template<class T>
void MemManager<T>::requestAllocation(size_t amount) {
	if (amount <= totalFree) {
		return;
	}
	size_t amountToAllocate = amount - totalFree;
	T* first = allocator.allocate(amountToAllocate);
	Block newBlock(amountToAllocate, first);
	blockTable.push_back(std::move(newBlock));
	totalFree += amountToAllocate;
	medianAllocationSize = (medianAllocationSize * blockTable.size() + amount) / (blockTable.size() + 1);
	return;
}

template<class T>
void MemManager<T>::requestDeallocation() {
	if (totalFree > 2 * medianAllocationSize) {
		int i = nextEmptyBlock();
		if (i != -1) {
			totalFree -= blockTable[i].size;
			allocator.deallocate(blockTable[i].first, blockTable[i].size);
			blockTable.erase(blockTable.begin() + i);
		}
	}
}

template<class T>
int MemManager<T>::nextEmptyBlock() {
	for (size_t i = 0; i < blockTable.size(); i++) {
		if (blockTable[i].empty) {
			return i;
		}
	}
	return -1;
}

template<class T>
int MemManager<T>::nextAvailableBlock() {
	if (firstAvailableBlock < blockTable.size() && !blockTable[firstAvailableBlock].full) {
		return firstAvailableBlock;
	}
	for (size_t i = firstAvailableBlock; i < blockTable.size(); i++) {
		if (!blockTable[i].full) {
			firstAvailableBlock = i;
			return i;
		}
	}
	//Try again starting from 0
	for (size_t i = 0; i < firstAvailableBlock; i++) {
		if (!blockTable[i].full) {
			firstAvailableBlock = i;
			return i;
		}
	}
	return -1;
}
}

