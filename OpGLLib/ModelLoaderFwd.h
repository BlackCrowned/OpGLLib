/*
 * ModelLoaderFwd.h
 *
 *  Created on: 05.08.2015
 *      Author: mimoe
 */

namespace OpGLLib {
namespace gl {

enum class MeshType;

class Mesh;
template<MeshType T> class MeshImpl;
class NullMesh;

class ModelLoaderBase;
class ModelLoader;
class NullModelLoader;

}
}
