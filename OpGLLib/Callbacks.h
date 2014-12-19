/*
 * Callbacks.h
 *
 *  Created on: 19.12.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_CALLBACKS_H_
#define OPGLLIB_CALLBACKS_H_

#include <OpGLLib/internal.h>

enum CallbackSettings {
	removeWhenFinished = 0x1
};

template<typename Event, typename Function, typename ...Args>
class Callbacks {
public:
	Callbacks();
	~Callbacks();

	void addCallback(Event event, Function const& func, Args const& ...args, int settings);
	void addCallback(Event event, Function&& func, Args&& ...args, int settings);
	void removeCallbacks(Event event);

	void dispatchEvent(Event event);

private:
	void removeCallback(int i);

	template<size_t ...I>
	inline void call_func(Function& func, std::tuple<Args...> args, std::index_sequence<I...>) {
		func(get<I>(args)...);
	};

	std::deque<std::tuple<Event, Function, int> > callbacks;
	std::deque<std::tuple<Args...> > arguments;
};

#endif /* OPGLLIB_CALLBACKS_H_ */
