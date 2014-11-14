#include <OpGLLib/OpGLLib.h>

using namespace gl;

OpGLLib::OpGLLib() {
	glbinding::Binding::initialize();
}

void OpGLLib::enableCulling(GLenum CullFace, GLenum FrontFace) {
	glEnable(GL_CULL_FACE);
	glCullFace(CullFace);
	glFrontFace(FrontFace);
}

void OpGLLib::disableCulling() {
	glDisable(GL_CULL_FACE);
}
