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

//Image<unsigned char> loadBMP(std::string filename);

Image<unsigned char> loadPNG(std::string filename);

}



#include <OpGLLib/ImageLoader.inl>

#endif /* OPGLLIB_IMAGELOADER_H_ */
