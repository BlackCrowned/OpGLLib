#include <OpGLLib/OpGLLib.h>

namespace OpGLLib {

OpGLLibBase::OpGLLibBase() :
		_serviceLocator(new ServiceLocator(), OpGLLib::default_delete<ServiceLocator>()) {

}

OpGLLibBase::OpGLLibBase(OpGLLibBase const* pointer) :
		_serviceLocator(pointer->_serviceLocator) {

}

void OpGLLibBase::reset() {
	OpGLLibBase newBase;

	//Swap with newBase
	swap(newBase);
}

void OpGLLibBase::reset(OpGLLibBase const* pointer) {
	OpGLLibBase newBase(pointer);

	//Swap with newBase
	swap(newBase);
}

void OpGLLibBase::setServiceLocator(ServiceLocator&& serviceLocator) {
	_serviceLocator.reset(new ServiceLocator(std::forward<ServiceLocator>(serviceLocator)), OpGLLib::default_delete<ServiceLocator>());
}

ServiceLocator& OpGLLibBase::getServiceLocator() const {
	return *_serviceLocator;
}

void OpGLLibBase::swap(OpGLLibBase& other) {
	std::swap(_serviceLocator, other._serviceLocator);
}

}
