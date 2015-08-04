/*
 * InputManager.h
 *
 *  Created on: 04.08.2015
 *      Author: mimoe
 */

#ifndef OPGLLIB_INPUTMANAGER_H_
#define OPGLLIB_INPUTMANAGER_H_

#include <OpGLLib/internal.h>

#include <OpGLLib/OpGLLib.h>
#include <OpGLLib/ObserverFwd.h>

#include <map>

namespace OpGLLib {

enum class KeyEvent {
	KEY_UP = 0, KEY_DOWN
};

typedef int Key;

class InputManagerBase: public OpGLLibBase, public Observer::InputManagerObserver {
public:
	InputManagerBase();
	InputManagerBase(OpGLLibBase const* pointer);
	virtual ~InputManagerBase() = 0;

	virtual void setKey(KeyEvent keyEvent, Key key) = 0;
	virtual void pressKey(Key key) = 0;
	virtual void releaseKey(Key key) = 0;

	virtual KeyEvent getKey(Key key) = 0;

protected:
	virtual void onNotify(KeyEvent keyEvent, Key key) = 0;
private:
};

class InputManager: public InputManagerBase {
public:
	InputManager();
	InputManager(OpGLLibBase const* pointer);
	virtual ~InputManager() = default;

	virtual void setKey(KeyEvent keyEvent, Key key);
	virtual void pressKey(Key key);
	virtual void releaseKey(Key key);

	virtual KeyEvent getKey(Key key);

protected:
	virtual void onNotify(KeyEvent keyEvent, Key key);

private:
	std::map<Key, KeyEvent> _keyMap;
};

class NullInputManager: public InputManagerBase {
public:
	NullInputManager();
	NullInputManager(OpGLLibBase const* pointer);
	virtual ~NullInputManager() = default;

	virtual void setKey(KeyEvent keyEvent, Key key);
	virtual void pressKey(Key key);
	virtual void releaseKey(Key key);

	virtual KeyEvent getKey(Key key);

protected:
	virtual void onNotify(KeyEvent keyEvent, Key key);
};

}

#endif /* OPGLLIB_INPUTMANAGER_H_ */
