/*
 * Logging.cpp
 *
 *  Created on: 26.07.2015
 *      Author: mimoe
 */

#include <OpGLLib/Logging.h>

namespace OpGLLib {

Logging::LoggingLevel Logging::_loggingLevel = Logging::LoggingLevel::debug;

void Logging::log(std::string const& msg, LoggingLevel loggingLevel) {
	//Only log relevant data
	if (loggingLevel < _loggingLevel) {
		return;
	}
	switch (loggingLevel) {
	case LoggingLevel::debug:
	case LoggingLevel::notice:
	case LoggingLevel::warning:
		std::cout << msg << std::endl;
		break;
	case LoggingLevel::recoverableError:
	case LoggingLevel::unrecoverableError:
		std::cerr << msg << std::endl;
		break;
	default:
		std::cerr << "Logging::log(): Wrong LoggingLevel selected!" << std::endl;
	}
}

void Logging::setLoggingLevel(LoggingLevel loggingLevel) {
	_loggingLevel = loggingLevel;
}

}
