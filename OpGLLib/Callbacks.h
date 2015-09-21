/*
 * Callbacks.h
 *
 *  Created on: 19.12.2014
 *      Author: Michael
 */

#ifndef OPGLLIB_CALLBACKS_H_
#define OPGLLIB_CALLBACKS_H_

#include <chrono>
#include <functional>
#include <iostream>
#include <deque>
#include <queue>
#include <map>

namespace OpGLLib{
enum CallbackSettings {
	removeWhenFinished = 0x1
};

template<typename Event>
class Callbacks {
public:
	Callbacks();
	~Callbacks();

//	template<typename R, typename ...Args>
//	void addCallback(Event event, std::function<R(Args...)> function, Args&& ...args, int settings) {
//		std::cout << "Using rvalue reference" << std::endl;
//		this->callbacks.push_back(new Callback<std::function<R(Args...)>, Args...>(event, function, args..., settings));
//	}
//	;

	template<typename R = void, typename ...Args>
	void addCallback(Event event, std::function<R(Args...)> function, Args&& ...args, int settings) {
		this->callbacks.push_back(
				new Callback<std::function<R(Args...)>, Args...>(event, function, std::forward_as_tuple(args...), settings));
	}
	;
	template<typename Function, typename ...Args>
	void addCallback(Event event, Function function, Args&& ...args, int settings) {
		this->callbacks.push_back(
				new Callback<std::function<typename Function::result_type(Args...)>, Args...>(event, function,
						std::forward_as_tuple(args...), settings));
	}
	;
	template<typename R = void, typename Function, typename ...Args>
	void addCallback(Event event, Function function, Args&& ...args, int settings) {
		std::function<R(Args...)> func = function;
		this->callbacks.push_back(new Callback<std::function<R(Args...)>, Args...>(event, func, std::forward_as_tuple(args...), settings));
	}
	;

	void removeCallbacks(Event event);
	void removeCallbacks();

	void dispatchEvent(Event event, bool firstOnly = false);

	int size();

private:
	void removeCallback(int i);

	class virtualCallback {
	public:
		virtual ~virtualCallback() {
		}
		;
		virtual void call() = 0;
		virtual Event event() = 0;
		virtual int settings() = 0;
	};

	template<typename Function, typename ...Args>
	class Callback: public virtualCallback {
	public:
		Callback(Event event, Function const& func, std::tuple<Args&&...> const& argsT, int settings) :
				args(argsT) {
			this->_event = event;
			this->func = func;
			this->_settings = settings;
		}
		;

		~Callback() {
			//delete this;
		}

		void call() {
			call_func(std::index_sequence_for<Args...> { });
		}
		;

		Event event() {
			return _event;
		}
		;

		int settings() {
			return _settings;
		}
		;

		template<size_t ...I>
		void call_func(std::index_sequence<I...> seq) {
			func(std::get<I>(args)...);
		}

	private:

		Event _event;
		Function func;
		std::tuple<Args&&...> args;
		int _settings;
	};

	std::deque<virtualCallback *> callbacks;
};

template class Callbacks<int> ;
}



#endif /* OPGLLIB_CALLBACKS_H_ */
