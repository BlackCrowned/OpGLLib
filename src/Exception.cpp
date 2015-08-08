/*
 * Exception.cpp
 *
 *  Created on: 30.07.2015
 *      Author: mimoe
 */

#include <OpGLLib/Exception.h>

#include <OpGLLib/ServiceLocator.h>

namespace OpGLLib {

Exception::Exception(OpGLLibBase const* pointer) :
		OpGLLibBase(pointer) {

}

OpenFileException::OpenFileException(OpGLLibBase const* pointer, std::string const& file) :
		Exception(pointer), _file(file) {

}

ExceptionType OpenFileException::what() {
	return ExceptionType::OPENFILE_EXCEPTION;
}

std::string OpenFileException::toString() {
	return "Unable to open file: " + _file;
}

bool OpenFileException::handle() {
	getServiceLocator().getLoggingService()->log(toString(), LoggingLevel::unrecoverableError);

	//Assume unrecoverable
	return false;
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
