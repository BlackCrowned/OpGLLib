namespace OpGLLib {

template<class Callable, class ...Args> void AnimationObject::addCallback(AnimationCallbackEvents event, Callable const& callable, Args&& ...args) {
	callbackHandler.addCallback(event, make_callback(callable, args...), ((event == onUpdate) || (event == onRestart) || (event == onReverse)) ? false : true);
}

}