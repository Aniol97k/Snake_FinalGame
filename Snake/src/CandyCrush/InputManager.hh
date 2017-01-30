
#pragma once
#include <queue>
#include <iostream>
#include <SDL/SDL.h>
#include <unordered_map>

#define IM InputManager::Instance()

struct MouseCoords { 
	Sint32 x{ 0 }, y{ 0 };
	MouseCoords() = default;
	MouseCoords(Sint32 x_, Sint32 y_) : x(x_), y(y_) {};
	friend MouseCoords operator-(const MouseCoords &lhs, const MouseCoords &rhs) { return std::move(MouseCoords(lhs.x - rhs.x, lhs.y - rhs.y)); };
	friend std::ostream &operator<<(std::ostream &os, const MouseCoords &rhs) { return os << '(' << rhs.x << ", " << rhs.y << ')'; };
};

enum MouseButton {
	MOUSE_BUTTON_LEFT = SDL_BUTTON_LEFT,
	MOUSE_BUTTON_MIDDLE,
	MOUSE_BUTTON_RIGHT
};

enum KeyButton : int { 
	KEY_BUTTON_DOWN = SDLK_DOWN,
	KEY_BUTTON_UP = SDLK_UP,
	KEY_BUTTON_LEFT = SDLK_LEFT,
	KEY_BUTTON_RIGHT = SDLK_RIGHT,
	KEY_BUTTON_ESCAPE = SDLK_ESCAPE,
	KEY_BUTTON_BACKSPACE = SDLK_BACKSPACE,
	KEY_BUTTON_ENTER = SDLK_RETURN,
	KEY_BUTTON_TAB = SDLK_TAB,
	KEY_BUTTON_LCTRL = SDLK_LCTRL,
	KEY_BUTTON_RCTRL = SDLK_RCTRL,
	KEY_BUTTON_LALT = SDLK_LALT,
	KEY_BUTTON_RALT = SDLK_RALT,
	KEY_BUTTON_LSHIFT = SDLK_LSHIFT,
	KEY_BUTTON_RSHIFT = SDLK_RSHIFT,
};


class InputManager {
public:
	
	inline static InputManager &Instance() {
		static InputManager inputManager;
		return inputManager;
	}
	
	void Update(void) {
		ProcessStates(); 
		SDL_Event evnt; 
		while (SDL_PollEvent(&evnt)) { 
			switch (evnt.type) { 
				case SDL_QUIT:				m_exit = true; break; 
				case SDL_MOUSEMOTION:		m_mouseCoords.x = evnt.motion.x; m_mouseCoords.y = evnt.motion.y; break; 
				case SDL_MOUSEWHEEL:		m_mouseWheel = evnt.wheel.y; 
				case SDL_MOUSEBUTTONDOWN:	m_inputValues.push(&(m_inputMap[evnt.button.button] = InputValue::DOWN)); break;
				case SDL_MOUSEBUTTONUP:		m_inputValues.push(&(m_inputMap[evnt.button.button] = InputValue::UP)); break; 
				case SDL_KEYDOWN:			m_inputValues.push(&(m_inputMap[evnt.key.keysym.sym] = (evnt.key.repeat) ? InputValue::HOLD : InputValue::DOWN)); break; 
				case SDL_KEYUP:				m_inputValues.push(&(m_inputMap[evnt.key.keysym.sym] = InputValue::UP)); break; 
			}
		}
	}
	
	inline bool HasQuit(void) const { 
		return m_exit; 
	};
	
	inline const MouseCoords &GetMouseCoords(void) const {
		return m_mouseCoords;
	};
	
	inline Sint32 GetMouseWheel(void) const {
		return m_mouseWheel; 
	};
	
	
	template<MouseButton btn> bool IsMouseDown(void) {
		return CheckInput<btn, InputValue::DOWN>();
	}
	
	template<MouseButton btn> bool IsMouseHold(void) {
		return CheckInput<btn, InputValue::HOLD>();
	}
	
	template<MouseButton btn> bool IsMouseUp(void) {
		return CheckInput<btn, InputValue::UP>();
	}
	
	template<Sint32 key> bool IsKeyDown(void) {
		return CheckInput<key, InputValue::DOWN>();
	}
	
	template<Sint32 key> bool IsKeyHold(void) {
		return CheckInput<key, InputValue::HOLD>();
	}
	
	template<Sint32 key> bool IsKeyUp(void) {
		return CheckInput<key, InputValue::UP>();
	}
private:
	
	enum class InputValue {
		UP = SDL_RELEASED,
		DOWN,
		HOLD,
		EMPTY
	};
	
	InputManager() = default;
	
	InputManager(const InputManager &rhs) = delete;
	
	InputManager &operator=(const InputManager &rhs) = delete;
	
	void ProcessStates(void) {
		while (!m_inputValues.empty()) { 
			auto value = m_inputValues.front(); 
			switch (*value) { 
				case InputValue::DOWN:	*value = InputValue::HOLD; value = nullptr; break; 
				case InputValue::UP:	*value = InputValue::EMPTY; value = nullptr; 
			} 
			m_inputValues.pop(); 
		}
	}
	
	template<Sint32 id, InputValue value> bool CheckInput(void) {
		auto it = m_inputMap.find(id); 
		return (it != m_inputMap.end()) ? it->second == value : false; 
	}
private:
	std::unordered_map<Sint32, InputValue> m_inputMap;		
	std::queue<InputValue*> m_inputValues;					
	MouseCoords m_mouseCoords;								
	Sint32 m_mouseWheel{ 0 };								
	bool m_exit = false;									
};