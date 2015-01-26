/*
 * ImageLoader.h
 *
 *  Created on: 16.01.2015
 *      Author: Michael
 */

#ifndef OPGLLIB_IMAGELOADER_H_
#define OPGLLIB_IMAGELOADER_H_

#include <OpGLLib/internal.h>
#include <OpGLLib/FileLoader.h>

namespace ImageLoader {

struct Dimensions {
	size_t width, height;
};

template<class T> using tvec4 = glm::detail::tvec4<T, glm::precision::highp>;

class Image {
public:
	typedef void dataType;
	typedef tvec4<dataType> vectorType;
	Image(Dimensions dimensions, std::shared_ptr<void> data, Dimensions offset = {0, 1});
	Image(Image const& other) = default;
	Image(Image && other) = default;
	~Image() = default;

	Image& operator =(Image other);

	std::shared_ptr<void> getData();
private:
	Dimensions dimensions;
	std::shared_ptr<void> data;
	Dimensions offset;
};

template<class T>
class Image1D {
public:
	typedef T dataType;
	typedef tvec4<dataType> vectorType;

	Image1D(size_t width);
	template<class U> Image1D(size_t width, std::shared_ptr<U> data, Dimensions offset = {0, 1});
	Image1D(Image1D<T> const& other) = default;
	Image1D(Image1D<T> && other) = default;
	~Image1D() = default;

	Image1D<T>& operator =(Image1D<T> other);
	tvec4<T>& operator [](size_t x);
	tvec4<T>& operator ()(size_t x = 0);

	std::shared_ptr<vectorType> getData();

private:
	Dimensions dimensions;
	std::shared_ptr<vectorType> data;
	Dimensions offset;
};

template<class T>
class Image2D {
public:
	typedef T dataType;
	typedef tvec4<dataType> vectorType;

	Image2D(size_t width, size_t height);
	template<class U> Image2D(size_t width, size_t height, std::shared_ptr<U> data, Dimensions offset = {0, 1});
	Image2D(Image2D<T> const& other) = default;
	Image2D(Image2D<T> && other) = default;
	~Image2D() = default;

	Image2D<T>& operator =(Image2D<T> other);
	Image1D<T> operator [](size_t x);
	tvec4<T>& operator ()(size_t x = 0, size_t y = 0);

	std::shared_ptr<vectorType> getData();

private:
	Dimensions dimensions;
	std::shared_ptr<vectorType> data;
	Dimensions offset;
};

enum Compression {
	BI_RGB = 0, BI_RLE8 = 1, BI_RLE4 = 2, BI_BITFIELDS = 3
};

struct ColorTableEntry {
	ColorTableEntry(char* offset) {
		color.b = *reinterpret_cast<OpGLLib::Types::BYTE*>(offset);
		color.g = *reinterpret_cast<OpGLLib::Types::BYTE*>(offset + 1);
		color.r = *reinterpret_cast<OpGLLib::Types::BYTE*>(offset + 2);
		color.a = *reinterpret_cast<OpGLLib::Types::BYTE*>(offset + 3);
	}
	tvec4<OpGLLib::Types::BYTE> color;
};

struct ColorTable {
	ColorTable() {
		ptr = nullptr;
		_size = 0;
	}
	ColorTable(char* ptr, size_t size) {
		ColorTable::ptr = ptr;
		ColorTable::_size = size;
	}
	~ColorTable() {

	}
	void operator ()(char* ptr, size_t size) {
		ColorTable::ptr = ptr;
		ColorTable::_size = size;
	}
	ColorTableEntry operator [](int i) {
		char* offset = ptr + (i * 4);
		return ColorTableEntry(offset);
	}
	size_t size() {
		return _size;
	}
private:
	char* ptr;
	size_t _size;
};

struct Bitmask {
	OpGLLib::Types::DWORD<> red, green, blue;
};

class Bitmap {
public:
	Bitmap(std::shared_ptr<char> address);
	Bitmap(Bitmap const& other) = delete;
	Bitmap(Bitmap&& other) = default;
	~Bitmap();

	Image2D<OpGLLib::Types::BYTE> getImage();

	OpGLLib::Types::WORD<> signature;
	OpGLLib::Types::DWORD<> fileSize;
	OpGLLib::Types::DWORD<> headerSize;
	OpGLLib::Types::DWORD<> offset;
	OpGLLib::Types::LONG<> width;
	OpGLLib::Types::LONG<> height;
	OpGLLib::Types::WORD<> planes;
	OpGLLib::Types::WORD<> bitCount;
	OpGLLib::Types::DWORD<> compression;
	OpGLLib::Types::DWORD<> sizeImage;
	OpGLLib::Types::DWORD<> clrUsed;
	OpGLLib::Types::DWORD<> clrImportant;
	Bitmask bitmask;
	ColorTable colorTable;
private:
	std::shared_ptr<char> address;
	char* ptr;
	std::shared_ptr<tvec4<OpGLLib::Types::BYTE> > imageData;
};

Bitmap loadBMP(std::string file);
}

template class ImageLoader::Image1D<float>;
template class ImageLoader::Image2D<float>;

#include <OpGLLib/ImageLoader.inl>

#endif /* OPGLLIB_IMAGELOADER_H_ */
