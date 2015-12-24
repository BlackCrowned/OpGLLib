namespace OpGLLib {

template<class Event> void CallbackHandler<Event>::addCallback(Event event, std::shared_ptr<CallbackBase> callback, bool callOnce) {
	if (!callOnce) {
		_addCallbackImpl(_container, event, callback);
	}
	else {
		_addCallbackImpl(_containerOneCall, event, callback);
	}
}

template <class Event> void CallbackHandler<Event>::removeCallback(Event event, std::shared_ptr<CallbackBase> callback) {
	_removeCallbackImpl(_container, event, callback);
	_removeCallbackImpl(_containerOneCall, event, callback);
}

template<class Event> void CallbackHandler<Event>::removeCallbacks(Event event) {
	_removeCallbacksImpl(_container, event);
	_removeCallbacksImpl(_containerOneCall, event);
}

template<class Event> void CallbackHandler<Event>::removeCallbacks(std::shared_ptr<CallbackBase> callback) {
	_removeCallbacksImpl(_container, callback);
	_removeCallbacksImpl(_containerOneCall, callback);
}

template<class Event> void CallbackHandler<Event>::dispatchEvent(Event event) {
	_dispatchEventImpl(_container, event);
	_dispatchEventImpl(_containerOneCall, event);
}

template<class Event> void CallbackHandler<Event>::_addCallbackImpl(std::unordered_map<Event, eventContainer>& container, Event& event, std::shared_ptr<CallbackBase>& callback) {
	container[event].push_back(std::move(callback));
}

template<class Event> void CallbackHandler<Event>::_removeCallbackImpl(std::unordered_map<Event, eventContainer>& container, Event& event, std::shared_ptr<CallbackBase>& callback) {
	//Prevent unnecessary instantiation of event-container
	if (container.count(event) == 0) {
		return;
	}
	//Delete all instances
	for (auto i = std::count(container[event].begin(), container[event].end(), callback); i > 0; i--) {
		//Find and delete callback
		auto it = std::find(container[event].begin(), container[event].end(), callback);
		container[event].erase(it);
	}
}

template<class Event> void CallbackHandler<Event>::_removeCallbacksImpl(std::unordered_map<Event, eventContainer>& container, Event& event) {
	//Prevent unnecessary instantiation of event-container
	if (container.count(event) == 0) {
		return;
	}

	//Erase event
	container.erase(event);
}

template<class Event> void CallbackHandler<Event>::_removeCallbacksImpl(std::unordered_map<Event, eventContainer>& container, std::shared_ptr<CallbackBase>& callback) {
	//Check all event-containers
	for (auto i : container) {
		//Remove all instances
		_removeCallbackImpl(container, i->first, callback);
	}
}

template<class Event> void CallbackHandler<Event>::_dispatchEventImpl(std::unordered_map<Event, eventContainer>& container, Event& event) {
	//Prevent unnecessary instantiation of event-container
	if (container.count(event) == 0) {
		return;
	}
	//Call all callbacks listening to this event
	for (auto it = container[event].begin(); it != container[event].end(); it++) {
		(*it)->call();
	}
}

template <class T, class ...Args> Callback<T, Args...>::Callback(T&& callable, Args&&... arguments) :
	_callable(std::forward<T>(callable)), _arguments(std::tuple<Args...>(std::forward<Args>(arguments)...)) {}

template<class T, class ...Args> void Callback<T, Args...>::call() const {
	_callImpl(std::index_sequence_for<Args...>{} );
}

template<class T, class ...Args> template<size_t ...I> void Callback<T, Args...>::_callImpl(std::index_sequence<I...> seq) const{
	_callable(std::forward<typename std::tuple_element<I, decltype(_arguments)>::type>(std::get<I>(_arguments))...);
};

template<class T, class ...Args> std::shared_ptr<CallbackBase> make_callback(T&& callable, Args&&... args){
	return std::shared_ptr<CallbackBase>(new Callback<T, Args...>(std::forward<T>(callable), std::forward<Args>(args)...));
}

}