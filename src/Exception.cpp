/*
 * Exception.cpp
 *
 *  Created on: 30.07.2015
 *      Author: mimoe
 */

#include <OpGLLib/Exception.h>

namespace OpGLLib {

Exception::Exception(OpGLLibBase* pointer) :
		OpGLLibBase(pointer) {
	//Use default logger
	addObserver(getLogger());
}

UnableToOpenFileException::UnableToOpenFileException(OpGLLibBase* pointer, std::string const& file) :
		Exception(pointer), _file(file) {

}

ExceptionType UnableToOpenFileException::what() {
	return ExceptionType::UNABLE_TO_OPEN_FILE;
}

std::string UnableToOpenFileException::toString() {
	return "Unable to open file: " + _file;
}

bool UnableToOpenFileException::handle() {
	notify(toString(), LoggingLevel::unrecoverableError);

	//Assume unrecoverable
	return false;
}

namespace gl {
namespace Shaders {

CompileException::CompileException(OpGLLibBase* pointer, std::string const& shader, std::shared_ptr<char> const& infoLog) :
		Exception(pointer), _shader(shader), _infoLog(infoLog) {

}

ExceptionType CompileException::what() {
	return ExceptionType::GL_SHADERS_COMPILE_EXCEPTION;
}

std::string CompileException::toString() {
	return "Failed to compile shader " + _shader;
}

bool CompileException::handle() {
	notify(toString(), LoggingLevel::unrecoverableError);
	notify(_infoLog.get(), LoggingLevel::debug);

	//This error is unrecoverable
	return false;
}

LinkException::LinkException(OpGLLibBase* pointer, std::shared_ptr<char> const& infoLog) :
		Exception(pointer), _infoLog(infoLog) {

}

ExceptionType LinkException::what() {
	return ExceptionType::GL_SHADERS_LINK_EXCEPTION;
}

std::string LinkException::toString() {
	return "Failed to link program";
}

bool LinkException::handle() {
	notify(toString(), LoggingLevel::unrecoverableError);
	notify(_infoLog.get(), LoggingLevel::debug);

	//This error is unrecoverable
	return false;
}

}
}

//void ExceptionHandler::handleException(Exception* exception) {
//	notify("Handling exception: " << exception->toString(), LoggingLevel::debug);
//	exception->handle();
//	delete exception;
//}
//
//void ExceptionHandler::onNotify(Exception* exception) {
//	handleException(exception);
//}

}
