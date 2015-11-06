/*
 * Uniform.cpp
 *
 *  Created on: 06.11.2015
 *      Author: mimoe
 */

#include <OpGLLib/gl/Uniform.h>

namespace OpGLLib {
namespace gl {

Uniform::Uniform(int location) :
		_location(location) {

}

int Uniform::id() {
	return _location;
}

}
}
