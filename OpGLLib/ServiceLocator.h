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
#include <OpGLLib/DefaultDelete.h>

namespace OpGLLib {

class ServiceLocator {
public:
	ServiceLocator();

	ServiceLocator(ServiceLocator const& other) = default;
	ServiceLocator(ServiceLocator&& other) = default;

	~ServiceLocator() = default;

	void registerLoggingService(std::shared_ptr<LoggingBase>&& loggingService);
	template<class T> void registerLoggingService(T&& loggingService);

	std::shared_ptr<LoggingBase> getLoggingService();

private:
	std::shared_ptr<LoggingBase> _loggingService;
};

}

#include <OpGLLib/ServiceLocator.inl>

#endif /* OPGLLIB_SERVICELOCATOR_H_ */
