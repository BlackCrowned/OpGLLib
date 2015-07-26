/*
 * Observer.h
 *
 *  Created on: 26.07.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_OBSERVER_H_
#define OPGLLIB_OBSERVER_H_

#include <OpGLLib/internal.h>

#include <deque>
#include <memory>

namespace OpGLLib {
namespace Observer {

template<class ...ArgsT> class Subject;

template<class ...ArgsT> class Observer {

friend class Subject<ArgsT...>;
public:
	Observer() = default;
	virtual ~Observer() = default;

protected:
	virtual void onNotify(ArgsT... args) = 0;
};

template<class ...ArgsT> class Subject {
public:
	Subject() = default;
	~Subject() = default;

	void addObserver(std::shared_ptr<Observer<ArgsT...>> observer);
	void removeObserver(std::shared_ptr<Observer<ArgsT...>> observer);

protected:
	void notify(ArgsT... args);
private:
	std::deque<std::shared_ptr<Observer<ArgsT...>>> _observers;
};

}
}

#include <OpGLLib/Observer.inl>

#endif /* OPGLLIB_OBSERVER_H_ */
