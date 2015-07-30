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

/* Define macros for easy logging */
//Undefines
#undef LOGN
#undef LOGN_MESSAGE
#undef LOGN_DEBUG
#undef LOGN_DEBUG_F
#undef LOG
#undef LOG_MESSAGE
#undef LOG_DEBUG
#undef LOG_DEBUG_F
//Defines
#define LOGN_MESSAGE(msg, loggingLevel) notify(msg, loggingLevel)
#define LOGN(msg, loggingLevel) LOGN_MESSAGE(std::string(__PRETTY_FUNCTION__) + std::string(": ") + msg, loggingLevel)
#define LOGN_DEBUG(msg) LOGN(msg, ::OpGLLib::LoggingLevel::debug)
#define LOGN_DEBUG_F LOGN_MESSAGE(std::string(__PRETTY_FUNCTION__), ::OpGLLib::LoggingLevel::debug)
#define LOG_MESSAGE(msg, loggingLevel) ::OpGLLib::detail::_logger.log(msg, loggingLevel)
#define LOG(msg, loggingLevel) LOG_MESSAGE(std::string(__PRETTY_FUNCTION__) + std::string(": ") + msg, loggingLevel)
#define LOG_DEBUG(msg) LOG(msg, ::OpGLLib::LoggingLevel::debug)
#define LOG_DEBUG_F LOG_MESSAGE(std::string(__PRETTY_FUNCTION__), ::OpGLLib::LoggingLevel::debug)

namespace OpGLLib {

enum class LoggingLevel {
	debug = 0, notice, warning, recoverableError, unrecoverableError, fatalError
};

namespace Observer {

typedef Observer<std::string const&, LoggingLevel> LoggingObserver;
typedef Subject<std::string const&, LoggingLevel> LoggingSubject;

}

class Logging: public Observer::LoggingObserver {
public:
	Logging();
	Logging(LoggingLevel loggingLevel);
	~Logging() = default;

	void log(std::string const& msg, LoggingLevel loggingLevel);

	void setLoggingLevel(LoggingLevel loggingLevel);

protected:
	virtual void onNotify(std::string const& msg, LoggingLevel loggingLevel);

private:
	LoggingLevel _loggingLevel;
};

namespace detail {
static Logging _logger(LoggingLevel::debug);
}

}

#endif /* OPGLLIB_LOGGING_H_ */
