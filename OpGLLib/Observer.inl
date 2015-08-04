/*
 * Observer.inl
 *
 *  Created on: 26.07.2015
 *      Author: mimoe
 */

namespace OpGLLib {
namespace Observer {

template<class ...ArgsT> void Subject<ArgsT...>::addObserver(std::shared_ptr<Observer<ArgsT...>> observer) {
	//Check if observer is already registered
	for (auto it = _observers.begin(); it != _observers.end(); it++) {
		if (observer == *it) {
			return;
		}
	}

	//Register observer
	_observers.push_back(observer);
}

template<class ...ArgsT> void Subject<ArgsT...>::removeObserver(std::shared_ptr<Observer<ArgsT...>> observer) {
	//Find observer
	for (auto it = _observers.begin(); it != _observers.end(); it++) {
		if (observer == *it) {
			//Unregister observer and return
			_observers.erase(it);
			return;
		}
	}
}

template<class ...ArgsT> void Subject<ArgsT...>::notify(ArgsT ... args) {
	//Notify all registered observers
	for (auto it = _observers.begin(); it != _observers.end(); it++) {
		(*it)->onNotify(args...);
	}
}

}
}

