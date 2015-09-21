/*
 * Types.cpp
 *
 *  Created on: 24.06.2015
 *      Author: mimoe
 */


#include <OpGLLib/Types.h>

namespace OpGLLib {

namespace Types {


std::string getTypeName(TypeInfo n) {
	return std::string(TypeNames[static_cast<int>(n)]);
}

}

}
