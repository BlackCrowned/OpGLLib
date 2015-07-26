/*
 * Log.h
 *
 *  Created on: 26.07.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_LOGGING_H_
#define OPGLLIB_LOGGING_H_

#include <OpGLLib/internal.h>

#include <string>
#include <iostream>

namespace OpGLLib {

class Logging {
public:
	Logging() = delete;
	~Logging() = delete;

	enum class LoggingLevel {
		debug = 0,
		notice,
		warning,
		recoverableError,
		unrecoverableError,
	};

	static void log(std::string const& msg, LoggingLevel loggingLevel);

	static void setLoggingLevel(LoggingLevel loggingLevel);

private:
	static LoggingLevel _loggingLevel;
};

}


#endif /* OPGLLIB_LOGGING_H_ */
