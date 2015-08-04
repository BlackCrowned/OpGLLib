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

}
