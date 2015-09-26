/*
 * ServiceLocator.cpp
 *
 *  Created on: 01.08.2015
 *      Author: mimoe
 */

#include <OpGLLib/ServiceLocator.h>
#include <OpGLLib/InputManager.h>
#include <OpGLLib/gl/ModelLoader.h>
#include <OpGLLib/ImageManager.h>

#include <OpGLLib/OpGLLib.h>

namespace OpGLLib {

ServiceLocator::ServiceLocator() :
		_loggingService(), _inputManagerService(), _modelLoaderService(), _imageManagerService() {

}

ServiceLocator::ServiceLocator(OpGLLibBase const* pointer) :
		_loggingService(new NullLogging(), OpGLLib::default_delete<LoggingBase>()),
				_inputManagerService(new NullInputManager(pointer), OpGLLib::default_delete<InputManagerBase>()),
				_modelLoaderService(new gl::NullModelLoader(pointer), OpGLLib::default_delete<gl::ModelLoaderBase>()),
				_imageManagerService(new NullImageManager(pointer), OpGLLib::default_delete<ImageManagerBase>()){

}

void ServiceLocator::init(OpGLLibBase const* pointer) {
	_loggingService.reset(new NullLogging(), OpGLLib::default_delete<LoggingBase>());
	_inputManagerService.reset(new NullInputManager(pointer), OpGLLib::default_delete<InputManagerBase>());
	_modelLoaderService.reset(new gl::NullModelLoader(pointer), OpGLLib::default_delete<gl::ModelLoaderBase>());
	_imageManagerService.reset(new NullImageManager(pointer), OpGLLib::default_delete<ImageManagerBase>());
}

void ServiceLocator::setLoggingService(std::shared_ptr<LoggingBase>&& loggingService) {
	//Check if loggingService holds a pointer
	if (loggingService.use_count()) {
		_loggingService = std::forward<std::shared_ptr<LoggingBase>>(loggingService);
	}
	//If it does not, register a null service instead
	else {
		_loggingService.reset(new NullLogging(), OpGLLib::default_delete<LoggingBase>());
	}
}

std::shared_ptr<LoggingBase> ServiceLocator::getLoggingService() {
	return _loggingService;
}

void ServiceLocator::setInputManagerService(std::shared_ptr<InputManagerBase>&& inputManagerService) {
	//Check if inputManagerService holds a pointer
	if (inputManagerService.use_count()) {
		_inputManagerService = std::forward<std::shared_ptr<InputManagerBase>>(inputManagerService);
	}
	//If it does not, register a null service instead
	else {
		_inputManagerService.reset(new NullInputManager(), OpGLLib::default_delete<InputManagerBase>());
	}
}

std::shared_ptr<InputManagerBase> ServiceLocator::getInputManagerService() {
	return _inputManagerService;
}

void ServiceLocator::setModelLoaderService(std::shared_ptr<gl::ModelLoaderBase>&& modelLoaderService) {
	//Check if modelLoaderService holds a pointer
	if (modelLoaderService.use_count()) {
		_modelLoaderService = std::forward<std::shared_ptr<gl::ModelLoaderBase>>(modelLoaderService);
	}
	//If it does not, register a null service instead
	else {
		_modelLoaderService.reset(new gl::NullModelLoader(), OpGLLib::default_delete<gl::ModelLoaderBase>());
	}
}

std::shared_ptr<gl::ModelLoaderBase> ServiceLocator::getModelLoaderService() {
	return _modelLoaderService;
}

void ServiceLocator::setImageManagerService(std::shared_ptr<ImageManagerBase>&& imageManagerService) {
	//Check if imageManagerService holds a pointer
	if (imageManagerService.use_count()) {
		_imageManagerService = std::forward<std::shared_ptr<ImageManagerBase>>(imageManagerService);
	}
	//If it does not, register a null service instead
	else {
		_imageManagerService.reset(new NullImageManager(), OpGLLib::default_delete<ImageManagerBase>());
	}
}

std::shared_ptr<ImageManagerBase> ServiceLocator::getImageManagerService() {
	return _imageManagerService;
}

}
