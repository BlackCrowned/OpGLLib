/*
 * ImageLoader.h
 *
 *  Created on: 16.01.2015
 *      Author: Michael
 */

#ifndef OPGLLIB_IMAGELOADER_H_
#define OPGLLIB_IMAGELOADER_H_

#define INCLUDE_GLM
#include <OpGLLib/internal.h>

#include <OpGLLib/FileLoader.h>

#include <lodePNG/lodepng.h>

namespace OpGLLib {
namespace ImageLoader {

struct Dimensions {
	size_t width, height;
};

template<class T> using tvec4 = glm::detail::tvec4<T, glm::precision::highp>;

template<class T>
class Image {
public:
	typedef T dataType;

	Image() = default;
	Image(Dimensions dimensions, std::vector<dataType> const& data);
	Image(Dimensions dimensions, std::vector<dataType>&& data);
	Image(Image<dataType> const& other) = default;
	Image(Image<dataType>&& other) = default;
	template<class U> Image(Image<U> const& other);
	template<class U> Image(Image<U>&& other);

	template<class U> Image<T>& operator=(Image<U> other);

	std::vector<dataType>& get();
	Dimensions getDimensions();

	void reset(Dimensions dimensions, std::vector<dataType>& data);

	~Image() = default;
private:
	Dimensions _dimensions;
	std::vector<dataType> _data;
};

//template<class T>
//class Image {
//public:
//	typedef T dataType;
//	typedef tvec4<dataType> vectorType;
//	Image(Dimensions dimensions, std::shared_ptr<vectorType> data, Dimensions offset = {0, 1});
//	Image(Image const& other) = default;
//	Image(Image && other) = default;
//	template<class U> Image(Image<U> const& i);
//	template<class U> Image(Image<U>&& i);
//	~Image() = default;
//
//	template<class U> Image<T>& operator =(Image<U> other);
//
//	Dimensions getDimensions();
//	std::shared_ptr<vectorType> getData();
//protected:
//	Dimensions dimensions;
//	std::shared_ptr<vectorType> data;
//	Dimensions offset;
//};
//
//template<class T>
//class Image1D : public Image<T>{
//public:
//	Image1D(size_t width);
//	template<class U> Image1D(size_t width, std::shared_ptr<U> data, Dimensions offset = {0, 1});
//	Image1D(Image1D<T> const& other);
//	Image1D(Image1D<T> && other);
//	~Image1D() = default;
//
//	template<class U> Image1D<T>& operator =(Image1D<U> other);
//	tvec4<T>& operator [](size_t x);
//	tvec4<T>& operator ()(size_t x = 0);
//};
//
//template<class T>
//class Image2D : public Image<T>{
//public:
//	Image2D(size_t width, size_t height);
//	template<class U> Image2D(size_t width, size_t height, std::shared_ptr<U> data, Dimensions offset = {0, 1});
//	Image2D(Image2D<T> const& other);
//	Image2D(Image2D<T> && other);
//	~Image2D() = default;
//
//	template<class U> Image2D<T>& operator =(Image2D<U> other);
//	Image1D<T> operator [](size_t x);
//	tvec4<T>& operator ()(size_t x = 0, size_t y = 0);
//};

enum Compression {
	BI_RGB = 0, BI_RLE8 = 1, BI_RLE4 = 2, BI_BITFIELDS = 3
};

struct ColorTableEntry {
	ColorTableEntry(char* offset) {
		color.b = *reinterpret_cast<Types::BYTE*>(offset);
		color.g = *reinterpret_cast<Types::BYTE*>(offset + 1);
		color.r = *reinterpret_cast<Types::BYTE*>(offset + 2);
		color.a = *reinterpret_cast<Types::BYTE*>(offset + 3);
	}
	tvec4<Types::BYTE> color;
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
	Types::DWORD<> red, green, blue;
};

class Bitmap {
public:
	typedef unsigned char dataType;

	Bitmap();
	Bitmap(char* ptr);
	Bitmap(std::string filename);
	Bitmap(Bitmap const& other) = delete;
	Bitmap(Bitmap&& other) = default;
	~Bitmap();
	bool loadBitmap(char* data);
	bool loadBitmap(std::string filename);

	Image<dataType> getImage();
	Dimensions getDimensions();
	size_t getWidth();
	size_t getHeight();
	size_t getBitCount();
private:
	Types::WORD<> signature;
	Types::DWORD<> fileSize;
	Types::DWORD<> headerSize;
	Types::DWORD<> offset;
	Types::LONG<> width;
	Types::LONG<> height;
	Types::WORD<> planes;
	Types::WORD<> bitCount;
	Types::DWORD<> compression;
	Types::DWORD<> sizeImage;
	Types::DWORD<> clrUsed;
	Types::DWORD<> clrImportant;
	Bitmask bitmask;
	ColorTable colorTable;
	std::vector<dataType> imageData;
};

Image<unsigned char> loadBMP(std::string filename);

Image<unsigned char> loadPNG(std::string filename);
}

}



#include <OpGLLib/ImageLoader.inl>

#endif /* OPGLLIB_IMAGELOADER_H_ */
