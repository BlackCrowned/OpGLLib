/*
 * CircularBuffer.h
 *
 *  Created on: 27.07.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_CIRCULARBUFFER_H_
#define OPGLLIB_CIRCULARBUFFER_H_

#include <OpGLLib/internal.h>

#include <memory>
#include <stdexcept>
#include <limits>

namespace OpGLLib {

template<class T, class allocator = std::allocator<T>>
class CircularBuffer {
public:
	typedef T value_type;
	typedef allocator allocator_type;

	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	typedef T& reference;
	typedef T const& const_reference;

	typedef T* pointer;
	typedef const pointer const_pointer;

	CircularBuffer();
	CircularBuffer(size_type size, bool auto_resize = false);
	CircularBuffer(CircularBuffer<T, allocator> const& other);
	~CircularBuffer();

	CircularBuffer<T, allocator>& operator=(CircularBuffer<T, allocator> const& other);
	CircularBuffer<T, allocator>& operator=(CircularBuffer<T, allocator> && other);
	//TODO: INITLIST

	void assign(size_type count, const_reference value);
	//TODO: ITERATOR
	//TODO: INITLIST

	void auto_resize(bool auto_resize) noexcept;

	//Element access

	reference at(size_type i);
	const_reference at(size_type i) const;

	reference operator[](size_type i);
	const_reference operator[](size_type i) const;

	reference front();
	const_reference front() const;

	reference back();
	const_reference back() const;

	//Capacity

	bool empty() const noexcept;

	size_type size() const noexcept;

	size_type max_size() const noexcept;

	void resize(size_type count);
	void resize(size_type count, const_reference value);

	size_type capacity() const noexcept;

	void reserve(size_type new_cap);

	//Modifiers

	void clear();

	void push_front(value_type value);
	template<class ...ArgsT> void emplace_front(ArgsT&&... args);
	void pop_front();

	void push_back(value_type value);
	template<class ...ArgsT> void emplace_back(ArgsT&&... args);
	void pop_back();

	void swap(CircularBuffer<T, allocator>& other);

private:
	void _outOfRangeCheck(size_type pos) const;
	void _lengthErrorCheck(size_type new_cap) const;

	void _increaseHead(difference_type n = 1);
	void _decreaseHead(difference_type n = 1);
	void _increaseTail(difference_type n = 1);
	void _decreaseTail(difference_type n = 1);

	void _boundsCheck(difference_type n);

	template<class ...ArgsT> void _resize(size_type count, ArgsT&&... args);

	size_type _capacity;
	allocator_type _allocator;

	pointer _array;

	difference_type _head;
	difference_type _tail;

	size_type _size;

	bool _auto_resize;
};

}

#include <OpGLLib/CircularBuffer.inl>

#endif /* OPGLLIB_CIRCULARBUFFER_H_ */
