/*
 * CircularBuffer.h
 *
 *  Created on: 27.07.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_CIRCULARBUFFER_H_
#define OPGLLIB_CIRCULARBUFFER_H_

#include <OpGLLib/internal.h>

#include <OpGLLib/Modulo.h>

#include <memory>
#include <stdexcept>
#include <limits>
#include <type_traits>
#include <string>

namespace OpGLLib {

template<class T>
class CircularBufferIterator {
public:
	//Iterator requirements
	typedef T value_type;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	typedef T* pointer;
	typedef T& reference;

	typedef const pointer const_pointer;
	typedef value_type const& const_reference;

	typedef std::input_iterator_tag iterator_category;

	CircularBufferIterator(pointer array, difference_type head, difference_type tail, size_type capacity, difference_type pos);
	CircularBufferIterator(CircularBufferIterator<T> const& other) = default;

	~CircularBufferIterator() = default;

	CircularBufferIterator<T>& operator=(CircularBufferIterator<T> const& other) = default;

	reference operator *();
	const_reference operator *() const;

	CircularBufferIterator<T>& operator ++() noexcept;
	CircularBufferIterator<T> operator ++(int) noexcept;

	void swap(CircularBufferIterator<T>& other) noexcept;

	//InputIterator requirements

	bool operator ==(CircularBufferIterator<T> const& other) const noexcept;
	bool operator !=(CircularBufferIterator<T> const& other) const noexcept;

	pointer operator ->();
	const_pointer operator ->() const;

private:
	pointer _array;
	difference_type _head;
	difference_type _tail;

	size_type _capacity;

	difference_type _pos;
};

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

	typedef CircularBufferIterator<T> iterator;
	typedef const iterator const_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef const std::reverse_iterator<iterator> const_reverse_iterator;

	CircularBuffer() = delete;
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

	//Iterators

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator crbegin() const;

	reverse_iterator rend();
	const_reverse_iterator rend() const;
	const_reverse_iterator crend() const;

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

	template<class Q = T>
	typename std::enable_if<std::is_nothrow_move_constructible<Q>::value, void>::type shrink_to_fit();

	template<class Q = T>
	typename std::enable_if<!std::is_nothrow_move_constructible<Q>::value, void>::type shrink_to_fit();

	//Modifiers

	void clear();

	void push_front(value_type const& value);
	void push_front(value_type&& value);
	template<class ...ArgsT> void emplace_front(ArgsT&&... args);
	void pop_front();

	void push_back(value_type const& value);
	void push_back(value_type&& value);
	template<class ...ArgsT> void emplace_back(ArgsT&&... args);
	void pop_back();

	void swap(CircularBuffer<T, allocator>& other);

	//Allocator

	allocator_type get_allocator() const noexcept;

private:
	void _outOfRangeCheck(size_type pos) const;
	void _lengthErrorCheck(size_type new_cap) const;

	void _increaseHead(difference_type n = 1);
	void _decreaseHead(difference_type n = 1);
	void _increaseTail(difference_type n = 1);
	void _decreaseTail(difference_type n = 1);

	bool _boundsCheck(difference_type n);

	template<class ...ArgsT> void _resize(size_type count, ArgsT&&... args);

	void _reallocate(size_type new_cap);

	template<class Q = T>
	typename std::enable_if<std::is_nothrow_move_constructible<Q>::value, void>::type _reallocate(size_type new_cap);

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
