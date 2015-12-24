namespace OpGLLib {

template<class Event> void CallbackHandler<Event>::addCallback(Event event, std::shared_ptr<CallbackBase> callback) {
	_container[event].push_back(std::move(callback));
}

template <class Event> void CallbackHandler<Event>::removeCallback(Event event, std::shared_ptr<CallbackBase> callback) {
	//Prevent unnecessary instantiation of event-container
	if (_container.count(event) == 0) {
		return;
	}
	//Delete all instances
	for (auto i = std::count(_container[event].begin(), _container[event].end(), callback); i > 0; i--) {
		//Find and delete callback
		auto it = std::find(_container[event].begin(), _container[event].end(), callback);
		_container[event].erase(it);
	}


}

template<class Event> void CallbackHandler<Event>::removeCallbacks(Event event) {
	//Prevent unnecessary instantiation of event-container
	if (_container.count(event) == 0) {
		return;
	}

	//Erase event
	_container.erase(event);
}

template<class Event> void CallbackHandler<Event>::removeCallbacks(std::shared_ptr<CallbackBase> callback) {
	//Check all event-containers
	for (auto i : _container) {
		//Remove all instances
		removeCallback(i->first, callback);
	}
}

template<class Event> void CallbackHandler<Event>::dispatchEvent(Event event) {
	//Prevent unnecessary instantiation of event-container
	if (_container.count() == 0) {
		return;
	}
	//Call all callbacks listening to this event
	for (auto it = _container[event].begin(); it != _container[event].end(); it++) {
		it->call();
	}
}

template <class T, class ...Args> Callback<T, Args...>::Callback(T&& callable, Args&&... arguments) :
	_callable(callable), _arguments(std::make_tuple(std::forward<Args...>(arguments...))) {}

template<class T, class ...Args> void Callback<T, Args...>::call() const {
	_callImpl(std::index_sequence_for<decltype(_arguments)>);
}

template<class T, class ...Args> template<size_t ...I> constexpr void Callback<T, Args...>::_callImpl(std::index_sequence<I...> seq) {
	_callable(std::forward<typename std::tuple_element<I, decltype(_arguments)>::type>(std::get<I>(_arguments))...);
};

}