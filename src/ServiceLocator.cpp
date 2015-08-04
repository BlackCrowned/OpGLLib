/*
 * ServiceLocator.cpp
 *
 *  Created on: 01.08.2015
 *      Author: mimoe
 */

#include <OpGLLib/ServiceLocator.h>

namespace OpGLLib {

ServiceLocator::ServiceLocator() : _loggingService(new NullLogging(), OpGLLib::default_delete<LoggingBase>()){

}

void ServiceLocator::setLoggingService(std::shared_ptr<LoggingBase>&& loggingService) {
	//Check if loggingService holds a pointer
	if (loggingService.use_count()) {
		_loggingService = std::forward<std::shared_ptr<LoggingBase>>(loggingService);
	}
	//If it does not, register a null service instead
	else {
		_loggingService.reset(new NullLogging(), OpGLLib::default_delete<LoggingBase>());
	}
}

std::shared_ptr<LoggingBase> ServiceLocator::getLoggingService() {
	return _loggingService;
}

}
