/*
 * CircularBuffer.inl
 *
 *  Created on: 27.07.2015
 *      Author: mimoe
 */

namespace OpGLLib {

template<class T>
CircularBufferIterator<T>::CircularBufferIterator(pointer array, difference_type head, difference_type tail, size_type capacity,
		difference_type pos) :
		_array(array), _head(head), _tail(tail), _capacity(capacity), _pos(pos) {
}

template<class T>
auto CircularBufferIterator<T>::operator *() -> reference {
	return _array[(_head + _pos) % _capacity];
}

template<class T>
auto CircularBufferIterator<T>::operator *() const -> const_reference {
	return _array[(_head + _pos) % _capacity];
}

template<class T>
CircularBufferIterator<T>& CircularBufferIterator<T>::operator ++() noexcept {
	_pos += 1;
	return *this;
}

template<class T>
CircularBufferIterator<T> CircularBufferIterator<T>::operator ++(int) noexcept {
	CircularBufferIterator<T> tmp = *this;
	++*this;
	return tmp;
}

template<class T>
void CircularBufferIterator<T>::swap(CircularBufferIterator<T>& other) noexcept {
	std::swap(_array, other._array);
	std::swap(_head, other._head);
	std::swap(_tail, other._tail);
	std::swap(_capacity, other._capacity);
	std::swap(_pos, other._pos);
}

template<class T>
bool CircularBufferIterator<T>::operator ==(CircularBufferIterator<T> const& other) const noexcept {
	if (_array == other._array && _head == other._head && _tail == other._tail && _capacity == other._capacity && _pos == other._pos) {
		return true;
	}
	return false;
}

template<class T>
bool CircularBufferIterator<T>::operator !=(CircularBufferIterator<T> const& other) const noexcept {
	return !operator==(other);
}

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
void CircularBuffer<T, allocator>::auto_resize(bool auto_resize) noexcept {
	_auto_resize = auto_resize;
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::begin() -> iterator {
	return iterator(_array, _head, _tail, capacity(), 0);
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::begin() const -> const_iterator {
	return const_iterator(_array, _head, _tail, capacity(), 0);
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::cbegin() const -> const_iterator {
	return const_iterator(_array, _head, _tail, capacity(), 0);
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::end() -> iterator {
	return iterator(_array, _head, _tail, capacity(), size());
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::end() const -> const_iterator {
	return const_iterator(_array, _head, _tail, capacity(), size());
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::cend() const -> const_iterator {
	return const_iterator(_array, _head, _tail, capacity(), size());
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::rbegin() -> reverse_iterator {
	return reverse_iterator(_array, _head, _tail, capacity(), 0);
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::rbegin() const -> const_reverse_iterator {
	return const_reverse_iterator(_array, _head, _tail, capacity(), 0);
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::crbegin() const -> const_reverse_iterator {
	return const_reverse_iterator(_array, _head, _tail, capacity(), 0);
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::rend() -> reverse_iterator {
	return reverse_iterator(_array, _head, _tail, capacity(), size());
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::rend() const -> const_reverse_iterator {
	return const_reverse_iterator(_array, _head, _tail, capacity(), size());
}

template<class T, class allocator>
auto CircularBuffer<T, allocator>::crend() const -> const_reverse_iterator {
	return const_reverse_iterator(_array, _head, _tail, capacity(), size());
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
		CircularBuffer<T, allocator> new_cb(new_cap, _auto_resize);

		//Copy/Move current content to new CircularBuffer
		for (auto it = begin(); it != end(); it++) {
			new_cb.emplace_back(std::move(*it));
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
void CircularBuffer<T, allocator>::push_front(value_type const& value) {
	emplace_front(value);
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::push_front(value_type&& value) {
	emplace_front(std::move(value));
}

template<class T, class allocator> template<class ...ArgsT>
void CircularBuffer<T, allocator>::emplace_front(ArgsT&&... args) {
	if (!_boundsCheck(1)) {
		//Destroy element to regain space
		pop_back();
	}
	_decreaseHead();
	_allocator.construct(_array + _head, std::forward<ArgsT>(args)...);
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::pop_front() {
	_allocator.destroy(_array + _head);
	_increaseHead();
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::push_back(value_type const& value) {
	emplace_back(value);
}

template<class T, class allocator>
void CircularBuffer<T, allocator>::push_back(value_type&& value) {
	emplace_back(std::move(value));
}

template<class T, class allocator> template<class ...ArgsT>
void CircularBuffer<T, allocator>::emplace_back(ArgsT&&... args) {
	if (!_boundsCheck(1)) {
		//Destroy Element to regain space
		pop_front();
	}
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
auto CircularBuffer<T, allocator>::get_allocator() const noexcept -> allocator_type{
	return _allocator;
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
	if (new_cap > max_size()) {
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
bool CircularBuffer<T, allocator>::_boundsCheck(difference_type n) {
	//Check wether resizing is required
	if (size() + n > capacity()) {
		//Only resize if _auto_resize is set
		if (_auto_resize) {
			//Try to resize CircularBuffer
			if (capacity() * 2 < max_size()) {
				reserve(capacity() * 2);
			} else {
				reserve(capacity() + (max_size() - capacity()));
			}

			//Check wether additional resizing is required
			return _boundsCheck(n);
		}
		//Otherwhise bound check failed!
		else {
			return false;
		}
	}
	return true;
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

