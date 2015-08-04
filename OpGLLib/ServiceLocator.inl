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
	_loggingService.reset(new T(std::forward<T>(inputManagerService)), OpGLLib::default_delete<InputManagerBase>());
}

}
