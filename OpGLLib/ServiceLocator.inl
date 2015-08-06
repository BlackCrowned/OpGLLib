/*
 * ServiceLocator.inl
 *
 *  Created on: 01.08.2015
 *      Author: mimoe
 */

namespace OpGLLib {

template<class T> void ServiceLocator::setLoggingService(T&& loggingService) {
	_loggingService.reset(new T(std::forward<T>(loggingService)), OpGLLib::default_delete<LoggingBase>());
}

template<class T> void ServiceLocator::setInputManagerService(T&& inputManagerService) {
	_inputManagerService.reset(new T(std::forward<T>(inputManagerService)), OpGLLib::default_delete<InputManagerBase>());
}

template<class T> void ServiceLocator::setModelLoaderService(T&& modelLoaderService) {
	_modelLoaderService.reset(new T(std::forward<T>(modelLoaderService)), OpGLLib::default_delete<gl::ModelLoaderBase>());
}

}
