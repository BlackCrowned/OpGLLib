#include <OpGLLib/OpGLLib.h>

using namespace gl;

OpGLLib::OpGLLib(glbinding::ContextHandle context) {
	glbinding::Binding::useContext(context);
	//glbinding::Binding::initialize(false);
}

void OpGLLib::enableCulling(GLenum CullFace, GLenum FrontFace) {
	glEnable(GL_CULL_FACE);
	glCullFace(CullFace);
	glFrontFace(FrontFace);
}

void OpGLLib::disableCulling() {
	glDisable(GL_CULL_FACE);
}
