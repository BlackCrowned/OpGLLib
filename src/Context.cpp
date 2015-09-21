/*
 * Context.cpp
 *
 *  Created on: 25.04.2015
 *      Author: Michael
 */

#include <OpGLLib/Context.h>

namespace OpGLLib {
namespace gl {

glbinding::ContextHandle Context::currentContext;

void Context::setContext(glbinding::ContextHandle context) {
	glbinding::Binding::useContext(context);
	currentContext = context;
}

glbinding::ContextHandle Context::getCurrentContext() {
	return currentContext;
}

}
}

