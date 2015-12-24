/*
 * Callbacks.h
 *
 *  Created on: 19.12.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_CALLBACK_H_
#define OPGLLIB_CALLBACK_H_

#include <OpGLLib/internal.h>

#include <OpGLLib/OpGLLib.h>

#include <tuple>
#include <memory>
#include <unordered_map>
#include <deque>


namespace OpGLLib {

class CallbackBase;

template<class Event>
class CallbackHandler {
public:
	typedef std::deque<std::shared_ptr<CallbackBase>> eventContainer;

	CallbackHandler() = default;
	~CallbackHandler() = default;

	void addCallback(Event event, std::shared_ptr<CallbackBase> callback, bool callOnce = false);
	void removeCallback(Event event, std::shared_ptr<CallbackBase> callback);
	void removeCallbacks(Event event);
	void removeCallbacks(std::shared_ptr<CallbackBase> callback);

	void dispatchEvent(Event event);

private:
	static void _addCallbackImpl(std::unordered_map<Event, eventContainer>& container, Event& event, std::shared_ptr<CallbackBase>& callback);
	static void _removeCallbackImpl(std::unordered_map<Event, eventContainer>& container, Event& event, std::shared_ptr<CallbackBase>& callback);
	static void _removeCallbacksImpl(std::unordered_map<Event, eventContainer>& container, Event& event);
	static void _removeCallbacksImpl(std::unordered_map<Event, eventContainer>& container, std::shared_ptr<CallbackBase>& callback);
	static void _dispatchEventImpl(std::unordered_map<Event, eventContainer>& container, Event& event);

	std::unordered_map<Event, eventContainer> _container;
	std::unordered_map<Event, eventContainer> _containerOneCall;
};

class CallbackBase {
public:
	CallbackBase() = default;
	virtual ~CallbackBase() = default;

	virtual void call() const = 0;
};

template<class T, class ...Args>
class Callback : public CallbackBase {
public:
	Callback(T&& callable, Args&&... arguments);
	virtual ~Callback() = default;

	virtual void call() const;
private:
	template<size_t ...I> void _callImpl(std::index_sequence<I...> seq) const;

	T _callable;
	std::tuple<Args...> _arguments;
};

template<class T, class ...Args> std::shared_ptr<CallbackBase> make_callback(T&& callable, Args&&... args);
}

#include <OpGLLib/Callback.inl>

#endif /* OPGLLIB_CALLBACK_H_ */
