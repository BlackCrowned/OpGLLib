/*
 * Callbacks.cpp
 *
 *  Created on: 19.12.2014
 *      Author: Michael
 */

#include <OpGLLib/Callbacks.h>

using namespace std;

template<typename Event, typename Function, typename ...Args>
Callbacks<Event, Function, Args...>::Callbacks() {

}

template <typename Event, typename Function, typename ...Args>
Callbacks<Event, Function, Args...>::~Callbacks() {

}

template <typename Event, typename Function, typename ...Args>
void Callbacks<Event, Function, Args...>::addCallback(Event event, Function const& func, Args const& ...args, int settings) {
	callbacks.emplace_back(make_tuple(event, func, settings));
	arguments.emplace_back(make_tuple(args...));
}

template <typename Event, typename Function, typename ...Args>
void Callbacks<Event, Function, Args...>::addCallback(Event event, Function&& func, Args&& ...args, int settings) {
	callbacks.emplace_back(make_tuple(event, std::move(func), settings));
	arguments.emplace_back(make_tuple(std::move(args...)));
}

template <typename Event, typename Function, typename ...Args>
void Callbacks<Event, Function, Args...>::removeCallbacks(Event event) {
	for (auto i = 0; i < callbacks.size(); i++) {
		if (get<0>(callbacks.at(i)) == event) {
			removeCallback(i--);
		}
	}
}

template <typename Event, typename Function, typename ...Args>
void Callbacks<Event, Function, Args...>::dispatchEvent(Event event) {
	for (auto i = 0; i < callbacks.size(); i++) {
		if (get<0>(callbacks.at(i)) == event) {
			Function func = get<1>(callbacks.at(i));
			int settings = get<2>(callbacks.at(i));
			call_func(func, index_sequence_for<Args...> {}, arguments.at(i));
			if (settings & removeWhenFinished) {
				removeCallback(i--);
			}

		}
	}
}

template<typename Event, typename Function, typename ...Args>
void Callbacks<Event, Function, Args...>::removeCallback(int i) {
	callbacks.erase(i);
	arguments.erase(i);
}
