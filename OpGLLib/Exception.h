/*
 * Exception.h
 *
 *  Created on: 30.07.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_EXCEPTION_H_
#define OPGLLIB_EXCEPTION_H_

#include <OpGLLib/internal.h>

#include <OpGLLib/Observer.h>
#include <OpGLLib/Logging.h>
#include <OpGLLib/OpGLLib.h>

namespace OpGLLib {

enum class ExceptionType {
	UNABLE_TO_OPEN_FILE, GL_SHADERS_COMPILE_EXCEPTION, GL_SHADERS_LINK_EXCEPTION
};

class Exception: public OpGLLibBase, public Observer::LoggingSubject {
public:
	Exception(OpGLLibBase* pointer);
	virtual ~Exception() = default;

	virtual ExceptionType what() = 0;
	virtual std::string toString() = 0;

	virtual bool handle() = 0;
};

class UnableToOpenFileException: public Exception {
public:
	UnableToOpenFileException(OpGLLibBase* pointer, std::string const& file);
	virtual ~UnableToOpenFileException() = default;

	virtual ExceptionType what();
	virtual std::string toString();

	virtual bool handle();

private:
	std::string const& _file;
};

namespace gl {
namespace Shaders {

class CompileException: public Exception {
public:
	CompileException(OpGLLibBase* pointer, std::string const& shader, std::shared_ptr<char> const& infoLog);
	virtual ~CompileException() = default;

	virtual ExceptionType what();
	virtual std::string toString();

	virtual bool handle();

private:
	std::string const& _shader;
	std::shared_ptr<char> const& _infoLog;
};

class LinkException: public Exception {
public:
	LinkException(OpGLLibBase* pointer, std::shared_ptr<char> const& infoLog);
	virtual ~LinkException() = default;

	virtual ExceptionType what();
	virtual std::string toString();

	virtual bool handle();
private:
	std::shared_ptr<char> const& _infoLog;
};

}
}

namespace Observer {

typedef Observer<ExceptionType> ExceptionHandlerObserver;
typedef Subject<ExceptionType> ExceptionHandlerSubject;

}

//class ExceptionHandler: public Observer::ExceptionHandlerObserver, Observer::LoggingSubject {
//public:
//	ExceptionHandler() = default;
//	~ExceptionHandler() = default;
//
//	void handleException(Exception* exception);
//
//protected:
//	virtual void onNotify(Exception* exception);
//private:
//
//};

}

#endif /* OPGLLIB_EXCEPTION_H_ */