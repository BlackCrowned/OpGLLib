/*
 * Log.h
 *
 *  Created on: 26.07.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_LOGGING_H_
#define OPGLLIB_LOGGING_H_

#include <OpGLLib/internal.h>

#include <OpGLLib/Observer.h>

#include <string>
#include <iostream>

namespace OpGLLib {


enum LoggingLevel {
	debug = 0, notice, warning, recoverableError, unrecoverableError, fatalError
};

class Logging: public Observer::Observer<std::string const&, int> {
public:
	Logging();
	Logging(LoggingLevel loggingLevel);
	~Logging() = default;

	void log(std::string const& msg, LoggingLevel loggingLevel);

	void setLoggingLevel(LoggingLevel loggingLevel);

protected:
	virtual void onNotify(std::string const& msg, int loggingLevel);

private:
	LoggingLevel _loggingLevel;
};

namespace detail {
static Logging _logger(LoggingLevel::debug);
}

}

#endif /* OPGLLIB_LOGGING_H_ */
