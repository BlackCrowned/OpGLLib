/*
 * Callbacks.h
 *
 *  Created on: 19.12.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_CALLBACKS_H_
#define OPGLLIB_CALLBACKS_H_

#include <OpGLLib/internal.h>

#include <OpGLLib/OpGLLib.h>

#include <tuple>
#include <memory>
#include <unordered_map>
#include <deque>
#include <stack>


namespace OpGLLib{

class CallbackBase;

struct CallbackOptions {

};

template<class Event>
class CallbackHandler {
public:
	typedef std::deque<std::shared_ptr<CallbackBase>> eventContainer;
	CallbackHandler() = default;
	~CallbackHandler() = default;

	void addCallback(Event event, std::shared_ptr<CallbackBase> callback);
	void removeCallback(Event event, std::shared_ptr<CallbackBase> callback);
	void removeCallbacks(Event event);
	void removeCallbacks(std::shared_ptr<CallbackBase> callback);

	void dispatchEvent(Event event);

private:
	std::unordered_map<Event, eventContainer> _container;
};

class CallbackBase {
public:
	CallbackBase() = default;
	virtual ~CallbackBase() = default;

	virtual void call() const = 0;
};

template<class T, class ...Args>
class Callback : public CallbackBase{
public:
	Callback(T&& callable, Args&&... arguments);
	virtual ~Callback() = default;

	virtual void call() const;
private:
	template<size_t ...I> constexpr void _callImpl(std::index_sequence<I...> seq);

	T _callable;
	std::tuple<Args...> _arguments;
};
}

#include <OpGLLib/Callbacks.inl>

#endif /* OPGLLIB_CALLBACKS_H_ */
