/*
 * OpGLLib.h
 *
 *  Created on: 12.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_OPGLLIB_H_
#define OPGLLIB_OPGLLIB_H_

#include <OpGLLib/internal.h>

#include <OpGLLib/ServiceLocator.h>
#include <OpGLLib/DefaultDelete.h>
#include <OpGLLib/ObserverFwd.h>

namespace OpGLLib {

class OpGLLibBase: public Observer::LoggingSubject, public Observer::ExceptionHandlerSubject {
public:
	//Prevent shadowing of Subjects
	using Observer::LoggingSubject::addObserver;
	using Observer::LoggingSubject::notify;
	using Observer::ExceptionHandlerSubject::addObserver;
	using Observer::ExceptionHandlerSubject::notify;

	OpGLLibBase();
	OpGLLibBase(OpGLLibBase const* pointer);
	OpGLLibBase(OpGLLibBase const& other) = default;
	OpGLLibBase(OpGLLibBase&& other) = default;
	~OpGLLibBase() = default;

	void reset();
	void reset(OpGLLibBase const* pointer);

	void setServiceLocator(ServiceLocator&& serviceLocator);
	ServiceLocator& getServiceLocator() const;

	void swap(OpGLLibBase& other);

private:
	std::shared_ptr<ServiceLocator> _serviceLocator;
};

}

#endif /* OPGLLIB_OPGLLIB_H_ */
