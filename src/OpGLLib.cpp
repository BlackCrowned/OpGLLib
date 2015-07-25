#include <OpGLLib/OpGLLib.h>

using namespace std;
using namespace gl;

namespace OpGLLib {

OpGLLib::OpGLLib() {
#ifndef RElEASE
	_debug.enableLogging();
#endif
}

OpGLLib::OpGLLib(glbinding::ContextHandle context) {
	_setContext(context);
#ifndef RElEASE
	_debug.enableLogging();
#endif
}

void OpGLLib::_setContext(glbinding::ContextHandle context) {
	glbinding::Binding::useContext(context);
}

}
