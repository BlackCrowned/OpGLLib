#include <OpGLLib/OpGLLib.h>

namespace OpGLLib {

OpGLLibBase::OpGLLibBase() :
		_logger(new Logging(LoggingLevel::debug)) {

}

OpGLLibBase::OpGLLibBase(OpGLLibBase const* pointer) :
		_logger(pointer->_logger) {

}

void OpGLLibBase::init() {

}

void OpGLLibBase::setLogger(Logging&& logger) {
	_logger.reset(new Logging(std::forward<Logging>(logger)));
}

std::shared_ptr<Logging> OpGLLibBase::getLogger(){
	return _logger;
}

}
