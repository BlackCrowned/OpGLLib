/*
 * Exception.h
 *
 *  Created on: 30.07.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_EXCEPTION_H_
#define OPGLLIB_EXCEPTION_H_

#include <OpGLLib/internal.h>

#include <OpGLLib/OpGLLib.h>


namespace OpGLLib {

enum class ExceptionType {
	OPENFILE_EXCEPTION, GL_SHADERS_COMPILE_EXCEPTION, GL_SHADERS_LINK_EXCEPTION, GL_MODELLOADER_LOADMODEL_EXCEPTION
};


class Exception: public OpGLLibBase {
public:
	Exception(OpGLLibBase const* pointer);
	virtual ~Exception() = default;

	virtual ExceptionType what() = 0;
	virtual std::string toString() = 0;

	virtual bool handle() = 0;
};

class OpenFileException: public Exception {
public:
	OpenFileException(OpGLLibBase const* pointer, std::string const& file);
	virtual ~OpenFileException() = default;

	virtual ExceptionType what();
	virtual std::string toString();

	virtual bool handle();

private:
	std::string const& _file;
};

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
