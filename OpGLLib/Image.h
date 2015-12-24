/*
 * Image.h
 *
 *  Created on: 16.01.2015
 *      Author: Michael
 */

#ifndef OPGLLIB_IMAGE_H_
#define OPGLLIB_IMAGE_H_

#include <OpGLLib/internal.h>

#include <OpGLLib/FileLoader.h>

#include <lodePNG/lodepng.h>

namespace OpGLLib {

struct Dimensions {
	size_t width, height;
};

template<class T>
class Image {
public:
	typedef T dataType;

	Image() = default;
	Image(Dimensions dimensions, std::vector<dataType> const& data);
	Image(Dimensions dimensions, std::vector<dataType>&& data);
	Image(Image<dataType> const& other) = default;
	Image(Image<dataType>&& other) = default;

	Image<T>& operator=(Image<T> other);

	std::vector<dataType>& get();
	Dimensions getDimensions();

	void reset(Dimensions dimensions, std::vector<dataType>& data);

	~Image() = default;
private:
	Dimensions _dimensions;
	std::vector<dataType> _data;
};

}



#include <OpGLLib/Image.inl>

#endif /* OPGLLIB_IMAGE_H_ */
