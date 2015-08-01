/*
 * OpGLLib.h
 *
 *  Created on: 12.11.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_OPGLLIB_H_
#define OPGLLIB_OPGLLIB_H_

#include <OpGLLib/internal.h>

#include <OpGLLib/Logging.h>

namespace OpGLLib {

class OpGLLibBase {
public:
	OpGLLibBase();
	OpGLLibBase(OpGLLibBase const* pointer);
	OpGLLibBase(OpGLLibBase const& other) = default;
	OpGLLibBase(OpGLLibBase&& other) = default;

	void init();

	void reset(OpGLLibBase const* pointer);

	void setLogger(Logging&& logger);
	std::shared_ptr<Logging> getLogger() const;

	void swap(OpGLLibBase& other);

private:
	std::shared_ptr<Logging> _logger;
};

}

#endif /* OPGLLIB_OPGLLIB_H_ */
