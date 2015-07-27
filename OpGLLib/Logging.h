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

/* Define macros for easy logging */
#define LOGN(msg, loggingLevel) notify(std::string(__PRETTY_FUNCTION__) + std::string(": ") + msg, loggingLevel)
#define LOG(msg, loggingLevel) ::OpGLLib::detail::_logger.log(std::string(__PRETTY_FUNCTION__) + std::string(": ") + msg, loggingLevel)
#define LOG_MESSAGE(msg, loggingLevel) ::OpGLLib::detail::_logger.log(msg, loggingLevel)

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
