/*
 * ServiceLocator.h
 *
 *  Created on: 01.08.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_SERVICELOCATOR_H_
#define OPGLLIB_SERVICELOCATOR_H_

#include <OpGLLib/internal.h>

#include <OpGLLib/Logging.h>
#include <OpGLLib/InputManagerFwd.h>
#include <OpGLLib/gl/ModelLoaderFwd.h>
#include <OpGLLib/DefaultDelete.h>

#include <OpGLLib/OpGLLibFwd.h>

namespace OpGLLib {

class ServiceLocator {
public:
	ServiceLocator();
	ServiceLocator(OpGLLibBase const* pointer);

	ServiceLocator(ServiceLocator const& other) = default;
	ServiceLocator(ServiceLocator&& other) = default;

	~ServiceLocator() = default;

	void init(OpGLLibBase const* pointer);

	void setLoggingService(std::shared_ptr<LoggingBase>&& loggingService);
	template<class T> void setLoggingService(T&& loggingService);
	std::shared_ptr<LoggingBase> getLoggingService();

	void setInputManagerService(std::shared_ptr<InputManagerBase>&& inputManagerService);
	template<class T> void setInputManagerService(T&& inputManagerService);
	std::shared_ptr<InputManagerBase> getInputManagerService();

	void setModelLoaderService(std::shared_ptr<gl::ModelLoaderBase>&& modelLoaderService);
	template <class T> void setModelLoaderService(T&& modelLoaderService);
	std::shared_ptr<gl::ModelLoaderBase> getModelLoaderService();

private:
	std::shared_ptr<LoggingBase> _loggingService;
	std::shared_ptr<InputManagerBase> _inputManagerService;
	std::shared_ptr<gl::ModelLoaderBase> _modelLoaderService;
};

}

#include <OpGLLib/ServiceLocator.inl>

#endif /* OPGLLIB_SERVICELOCATOR_H_ */
