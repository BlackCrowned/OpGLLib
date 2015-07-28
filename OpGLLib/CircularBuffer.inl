/*
 * CircularBuffer.inl
 *
 *  Created on: 27.07.2015
 *      Author: mimoe
 */

namespace OpGLLib {

template<class T, class allocator>
CircularBuffer<T, allocator>::CircularBuffer() :
		_capacity(0), _allocator(), _array(nullptr), _head(-1), _tail(0), _size(0), _auto_resize(false) {

}

template<class T, class allocator>
CircularBuffer<T, allocator>::CircularBuffer(size_type size, bool auto_resize) :
		_capacity(size), _allocator(), _array(_allocator.allocate(size)), _head(0), _tail(0), _size(0), _auto_resize(auto_resize) {

}

template<class T, class allocator>
CircularBuffer<T, allocator>::CircularBuffer(CircularBuffer<T, allocator> const& other) :
		_capacity(other._capacity), _allocator(other._allocator), _array(_allocator.allocate(_capacity)), _head(0), _tail(0), _size(0),
				_auto_resize(other._auto_resize) {

	//Copy construct each element
	for (size_type i = 0; i < other.size(); i++) {
		emplace_back(other[i]);
	}
}

template<class T, class allocator>
CircularBuffer<T, allocator>::~CircularBuffer() {
	//Clear buffer
	clear();

	//Deallocate remaining storage
	_allocator.deallocate(_array, capacity());
}

template<class T, class allocator>
CircularBuffer<T, allocator>& CircularBuffer<T, allocator>::operator=(CircularBuffer<T, allocator> const& other) {
	//Destroy and deallocate current content
	clear();
	_allocator.deallocate(_array, capacity());

	//Reset members
	_head = 0;
	_tail = 0;
	_size = 0;

	//Copy state
	_capacity = other._capacity;
	_auto_resize = other._auto_resize;
	_array = _allocator.allocate(capacity());

	//Copy content
	for (size_type i = 0; i < other.size(); i++) {
		emplace_back(other[i]);
	}
}

template<class T, class allocator>
CircularBuffer<T, allocator>& CircularBuffer<T, allocator>::operator =(CircularBuffer<T, allocator> && other) {
	//Simply swap content
	swap(other);
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::assign(size_type count, const_reference value) {
	//Destroy current content
	clear();

	for (size_type i = 0; i < count; i++) {
		emplace_back(value);
	}
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::auto_resize(bool auto_resize) noexcept{
	_auto_resize = auto_resize;
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::at(size_type pos) -> reference {
	//Check bounds
	_outOfRangeCheck(pos);
	return _array[(_head + pos) % capacity()];
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::at(size_type pos) const -> const_reference {
	//Check bounds
	_outOfRangeCheck(pos);
	return _array[(_head + pos) % capacity()];
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::operator [](size_type pos) -> reference {
	return _array[(_head + pos) % capacity()];
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::operator [](size_type pos) const -> const_reference {
	return _array[(_head + pos) % capacity()];
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::front() -> reference {
	return _array[_head];
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::front() const -> const_reference {
	return _array[_head];
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::back() -> reference {
	return _array[(_tail - 1) % capacity()];
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::back() const -> const_reference {
	return _array[(_tail - 1) % capacity()];
}

template<class T, class allocator>
bool CircularBuffer<T, allocator>::empty() const noexcept {
	return size() == 0 ? true : false;
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::size() const noexcept -> size_type {
	return _size;
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::max_size() const noexcept -> size_type {
	return std::numeric_limits<difference_type>::max();
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::resize(size_type count) {
	_resize(count);
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::resize(size_type count, const_reference value) {
	_resize(count, value);
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::capacity() const noexcept -> size_type {
	return _capacity;
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::reserve(size_type new_cap) {
	if (new_cap > capacity()) {
		//Check wether max_size is reached
		_lengthErrorCheck(new_cap);

		//Construct new CircularBuffer with requested_size
		CircularBuffer<T, allocator> new_cb(new_cap);

		//Copy/Move current content to new CircularBuffer
		for (size_type i = 0; i < size(); i++) {
			new_cb.emplace_back(std::move(operator[](i)));
		}

		//Swap current and new CircularBuffer
		swap(new_cb);
	}
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::clear() {
	//Destruct all objects
	while (!empty()) {
		pop_front();
	}
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::push_front(value_type value) {
	_boundsCheck(1);
	_decreaseHead();
	_array[_head] = value;
}

template<class T, class allocator> template<class ...ArgsT>
void CircularBuffer<T, allocator>::emplace_front(ArgsT&&... args) {
	_boundsCheck(1);
	_decreaseHead();
	_allocator.construct(_array + _head, std::forward<ArgsT>(args)...);
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::pop_front() {
	_allocator.destroy(_array + _head);
	_increaseHead();
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::push_back(value_type value) {
	_boundsCheck(1);
	_array[_tail] = value;
	_increaseTail();
}

template<class T, class allocator> template<class ...ArgsT>
void CircularBuffer<T, allocator>::emplace_back(ArgsT&&... args) {
	_boundsCheck(1);
	_allocator.construct(_array + _tail, std::forward<ArgsT>(args)...);
	_increaseTail();
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::pop_back() {
	_decreaseTail();
	_allocator.destroy(_array + _tail);
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::swap(CircularBuffer<T, allocator>& other) {
	std::swap(_capacity, other._capacity);
	std::swap(_allocator, other._allocator);
	std::swap(_array, other._array);
	std::swap(_head, other._head);
	std::swap(_tail, other._tail);
	std::swap(_size, other._size);
	std::swap(_auto_resize, other._auto_resize);
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::_outOfRangeCheck(size_type pos) const {
	if (pos >= size()) {
		throw std::out_of_range(
				std::string("CircularBuffer::_outOfRangeCheck(size_type pos): pos[") + std::to_string(pos)
						+ std::string("] >= this->size()[") + std::to_string(size()) + std::string("]"));
	}
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::_lengthErrorCheck(size_type new_cap) const {
	if (new_cap > capacity()) {
		throw std::length_error(
				std::string("CircularBuffer::_lengthErrorCheck(size_type new_cap): new_cap[") + std::to_string(new_cap)
						+ std::string("] > this->max_size()[") + std::to_string(max_size()) + std::string("]"));
	}
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::_increaseHead(difference_type n) {
	_head = (_head + n) % capacity();
	_size -= n;
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::_decreaseHead(difference_type n) {
	_head = (_head - n) % capacity();
	_size += n;
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::_increaseTail(difference_type n) {
	_tail = (_tail + n) % capacity();
	_size += n;
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::_decreaseTail(difference_type n) {
	_tail = (_tail - n) % capacity();
	_size -= n;
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::_boundsCheck(difference_type n) {
	//Only check bounds if _auto_resize is enabled
	if (!_auto_resize) {
		return;
	}

	//Check wether resizing is required
	if (size() + n > capacity()) {
		//Try to resize CircularBuffer
		if (capacity() * 2 < max_size()) {
			reserve(capacity() * 2);
		} else {
			reserve(capacity() + (max_size() - capacity()));
		}

		//Check wether additional resizing is required
		return _boundsCheck(n);
	}
}

template<class T, class allocator> template<class ...ArgsT>
void CircularBuffer<T, allocator>::_resize(size_type count, ArgsT&& ... args) {
	if (count < size()) {
		//Destroy objects exceeding the new limit
		while (count < size()) {
			pop_back();
		}
	} else if (count > size()) {
		//Append missing Elements
		while (count > size()) {
			emplace_back(std::forward<ArgsT>(args)...);
		}
	}
}

}

