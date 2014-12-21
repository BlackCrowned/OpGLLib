/*
 * Callbacks.cpp
 *
 *  Created on: 19.12.2014
 *      Author: Michael
 */

#include <OpGLLib/Callbacks.h>

using namespace std;

template<typename Event>
Callbacks<Event>::Callbacks() {

}

template <typename Event>
Callbacks<Event>::~Callbacks() {

}

template <typename Event>
void Callbacks<Event>::removeCallbacks(Event event) {
	for (unsigned int i = 0; i < callbacks.size(); i++) {
		if (callbacks.at(i)->event() == event) {
			removeCallback(i--);
		}
	}
}

template <typename Event>
void Callbacks<Event>::dispatchEvent(Event event) {
void Callbacks<Event>::removeCallbacks() {
	callbacks.clear();
}

	for (unsigned int i = 0; i < callbacks.size(); i++) {
		if (callbacks.at(i)->event() == event) {
			callbacks.at(i)->call();
			if (callbacks.at(i)->settings() & removeWhenFinished) {
				removeCallback(i--);
			}

		}
	}
}

template<typename Event>
void Callbacks<Event>::removeCallback(int i) {
	callbacks.erase(callbacks.begin() + i);
}

template<typename Event>
int Callbacks<Event>::size() {
	return callbacks.size();
}
