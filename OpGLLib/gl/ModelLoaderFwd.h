/*
 * ModelLoaderFwd.h
 *
 *  Created on: 05.08.2015
 *      Author: mimoe
 */

namespace OpGLLib {
namespace gl {

enum class MeshType;
enum class MaterialType;

class Mesh;
template<MeshType T> class MeshImpl;
class NullMesh;

class Material;
template<MaterialType T> class MaterialImpl;

class Model;

class ModelLoaderBase;
class ModelLoader;
class NullModelLoader;

}
}
