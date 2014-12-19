/*
 * Timer.h
 *
 *  Created on: 17.12.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_TIMER_H_
#define OPGLLIB_TIMER_H_

#include <OpGLLib/internal.h>

class Timer {
public:
	Timer();
	~Timer();

	void setDelay(std::chrono::milliseconds delay);

private:
};



#endif /* OPGLLIB_TIMER_H_ */
