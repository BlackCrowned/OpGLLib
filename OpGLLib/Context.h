/*
 * Context.h
 *
 *  Created on: 25.04.2015
 *      Author: Michael
 */

#ifndef OPGLLIB_CONTEXT_H_
#define OPGLLIB_CONTEXT_H_

#define INCLUDE_GLBINDING
#include <OpGLLib/internal.h>

namespace OpGLLib {
namespace gl {
class Context {
public:
	static void setContext(glbinding::ContextHandle context);
	static glbinding::ContextHandle getCurrentContext();
private:
	static glbinding::ContextHandle currentContext;
};
}
}

#endif /* OPGLLIB_CONTEXT_H_ */
