#ifdef INCLUDE_GLBINDING
#include <glbinding/gl/gl.h>
#include <glbinding/ContextHandle.h>
#include <glbinding/Binding.h>
#undef INCLUDE_GLBINDING
#endif

#ifdef INCLUDE_GLM
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#undef INCLUDE_GLM
#endif
