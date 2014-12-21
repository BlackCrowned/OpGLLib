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

template<typename Event>
class Callbacks {
public:
	Callbacks();
	~Callbacks();

	template<typename Function, typename ...Args>
	void addCallback(Event event, Function const& func, Args const& ...args, int settings) {
		this->callbacks.push_back(new Callback<Function, Args...>(event, func, args..., settings));
	};

	void removeCallbacks(Event event);
	void removeCallbacks();

	void dispatchEvent(Event event);

	int size();

private:
	void removeCallback(int i);

	class virtualCallback {
	public:
		virtual ~virtualCallback() {};
		virtual void call() = 0;
		virtual Event event() = 0;
		virtual int settings() = 0;
	};

	template <typename Function, typename ...Args>
	class Callback : public virtualCallback{
	public:
		Callback(Event event, Function const& func, Args const&... args, int settings) {
			this->_event = event;
			this->func = &func;
			this->args = std::make_tuple(args...);
			this->_settings = settings;
		};

		~Callback() {
			delete this;
		}

		void call() {
			call_func(std::index_sequence_for<Args...> {});
		};

		Event event() {
			return _event;
		};

		int settings() {
			return _settings;
		};

		template<size_t ...I>
		void call_func(std::index_sequence<I...> seq) {
			(*func)(std::get<I>(args)...);
		}

	private:

		Event _event;
		Function* func;
		std::tuple<Args...> args;
		int _settings;
	};


	std::deque<virtualCallback *> callbacks;
};

template class Callbacks<int>;

#endif /* OPGLLIB_CALLBACKS_H_ */
