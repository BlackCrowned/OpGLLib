/*
 * InputManager.cpp
 *
 *  Created on: 04.08.2015
 *      Author: mimoe
 */

#include <OpGLLib/InputManager.h>

namespace OpGLLib {

InputManagerBase::InputManagerBase() :
		OpGLLibBase() {

}

InputManagerBase::InputManagerBase(OpGLLibBase const* pointer) :
		OpGLLibBase(pointer) {

}

InputManager::InputManager() :
		InputManagerBase() {

}

InputManager::InputManager(OpGLLibBase const* pointer) :
		InputManagerBase(pointer) {

}

void InputManager::setKey(KeyEvent keyEvent, Key key) {
	_keyMap[key] = keyEvent;
}

void InputManager::pressKey(Key key) {
	_keyMap[key] = KeyEvent::KEY_DOWN;
}

void InputManager::releaseKey(Key key) {
	_keyMap[key] = KeyEvent::KEY_UP;
}

KeyEvent InputManager::getKey(Key key) {
	return _keyMap[key];
}

void InputManager::onNotify(KeyEvent keyEvent, Key key) {
	setKey(keyEvent, key);
}

NullInputManager::NullInputManager() :
		InputManagerBase() {

}

NullInputManager::NullInputManager(OpGLLibBase const* pointer) :
		InputManagerBase(pointer) {

}

void NullInputManager::setKey(KeyEvent keyEvent, Key key) {
	//Do nothing
}

void NullInputManager::pressKey(Key key) {
	//Do nothing
}

void NullInputManager::releaseKey(Key key) {
	//Do nothing
}

KeyEvent NullInputManager::getKey(Key key) {
	//Return nothing
	return KeyEvent::KEY_UP;
}

void NullInputManager::onNotify(KeyEvent keyEvent, Key key) {
	//Do nothing
}

}
