#include "Input.h"
#include <Windows.h>


namespace FumoEngine
{
	//Key and Mouse States
#pragma region KeyMouseStates
	std::unordered_map<int, bool> Input::key_states = {
			{ GLFW_KEY_W, false },
			{ GLFW_KEY_A, false },
			{ GLFW_KEY_S, false },
			{ GLFW_KEY_D, false },

			{ GLFW_KEY_Q, false },
			{ GLFW_KEY_E, false },
			{ GLFW_KEY_R, false },
			{ GLFW_KEY_T, false },
			{ GLFW_KEY_Y, false },
			{ GLFW_KEY_U, false },
			{ GLFW_KEY_I, false },
			{ GLFW_KEY_O, false },
			{ GLFW_KEY_P, false },

			{ GLFW_KEY_F, false },
			{ GLFW_KEY_G, false },
			{ GLFW_KEY_H, false },
			{ GLFW_KEY_J, false },
			{ GLFW_KEY_K, false },
			{ GLFW_KEY_L, false },

			{ GLFW_KEY_Z, false },
			{ GLFW_KEY_X, false },
			{ GLFW_KEY_C, false },
			{ GLFW_KEY_V, false },
			{ GLFW_KEY_B, false },
			{ GLFW_KEY_N, false },
			{ GLFW_KEY_M, false },

			{ GLFW_KEY_0, false },
			{ GLFW_KEY_1, false },
			{ GLFW_KEY_2, false },
			{ GLFW_KEY_3, false },
			{ GLFW_KEY_4, false },
			{ GLFW_KEY_5, false },
			{ GLFW_KEY_6, false },
			{ GLFW_KEY_7, false },
			{ GLFW_KEY_8, false },
			{ GLFW_KEY_9, false },

			{ GLFW_KEY_LEFT_ALT, false },
			{ GLFW_KEY_RIGHT_ALT, false },
			{ GLFW_KEY_LEFT_SHIFT, false },
			{ GLFW_KEY_RIGHT_SHIFT, false },
			{ GLFW_KEY_LEFT_CONTROL, false },
			{ GLFW_KEY_RIGHT_CONTROL, false },
			{ GLFW_KEY_UP, false },
			{ GLFW_KEY_DOWN, false },
			{ GLFW_KEY_LEFT, false },
			{ GLFW_KEY_RIGHT, false },
			{ GLFW_KEY_SPACE, false },
			{ GLFW_KEY_ESCAPE, false},
			{ GLFW_KEY_ENTER, false},
			{ GLFW_KEY_TAB, false}
	};
	std::unordered_map<int, bool> Input::previous_key_states = key_states;

	std::unordered_map<int, bool> Input::mouse_states = {
		{ GLFW_MOUSE_BUTTON_1, false },
		{ GLFW_MOUSE_BUTTON_2, false }
	};
	std::unordered_map<int, bool> Input::previous_mouse_states = mouse_states;
#pragma endregion


	InputVector2 Input::mousePos{ 0, 0 };
	InputVector2 Input::centeredMousePos{ 0, 0 };
	void Input::processInput(AppWindow* window)
	{
		::GLFWwindow* mWindow = window->getWindowPtr();//Get actual window ptr in input instead of application

		glfwGetCursorPos(mWindow, &mousePos.x, &mousePos.y);

		int screenWidth, screenHeight;
		glfwGetWindowSize(mWindow, &screenWidth, &screenHeight);

		float mousePosXCentered = static_cast<float>(mousePos.x) - (screenWidth * 0.5f);
		float mousePosYCentered = (screenHeight * 0.5f) - static_cast<float>(mousePos.y);

		centeredMousePos = InputVector2(mousePosXCentered, mousePosYCentered);//Where 0, 0 is center of the window

		//Keys
		for (auto& it : previous_key_states)
		{
			it.second = key_states[it.first];
		}
		for (auto& it : key_states)
		{
			it.second = glfwGetKey(mWindow, it.first);
		}

		//Mouse
		for (auto& it : previous_mouse_states)
		{
			it.second = mouse_states[it.first];
		}
		for (auto& it : mouse_states)
		{
			it.second = glfwGetMouseButton(mWindow, it.first);
		}
	}

	bool Input::getAnyKey(int& firstKey)
	{
		for (const auto& keyState : key_states)
		{
			if (keyState.second)
			{
				firstKey = keyState.first;
				return true;
			}
		}
		firstKey = -1;
		return false;
	}
	bool Input::getAnyKeyDown(int& firstKey)
	{
		for (const auto& p_keyState : previous_key_states)
		{
			if (!p_keyState.second && key_states[p_keyState.first])
			{
				firstKey = p_keyState.first;
				return true;
			}
		}
		return false;
	}

#pragma region Additional
	//  Addtional function made for experimentation, to compensate for the fact that getAnyKey only reads 1 key, the first key checked.
	void Input::getAnyKeyAndProcess()
	{
		std::queue<int> pressedKeys;
		for (const auto& keyState : key_states)
		{
			if (keyState.second)
			{
				pressedKeys.push(keyState.first);
			}
		}

		if (pressedKeys.empty())
			return;

		std::cout << "Pressed key(s): ";
		while (!pressedKeys.empty())
		{
			std::cout << getKeyNameFiltered(pressedKeys.front()) << " ";
			pressedKeys.pop();
		}
		std::cout << std::endl;
	}
#pragma endregion

	bool Input::getKey(int key)
	{
		auto it = key_states.find(key);
		return (it != key_states.end() && it->second);
	}
	bool Input::getKeyDown(int key)
	{
		auto it = key_states.find(key);
		auto itp = previous_key_states.find(key);
		return (it != key_states.end() && !itp->second && it->second);
	}

	bool Input::getKeyUp(int key)
	{
		auto it = key_states.find(key);
		auto itp = previous_key_states.find(key);
		return (it != key_states.end() && itp->second && !it->second);
	}

	bool Input::getMouseButton(int mb)
	{
		auto it = mouse_states.find(mb);
		return (it != mouse_states.end() && it->second);
	}
	bool Input::getMouseButtonDown(int mb)
	{
		auto it = mouse_states.find(mb);
		auto itp = previous_mouse_states.find(mb);
		return (it != mouse_states.end() && !itp->second && it->second);
	}
	bool Input::getMouseButtonUp(int mb)
	{
		auto it = mouse_states.find(mb);
		auto itp = previous_mouse_states.find(mb);
		return (it != mouse_states.end() && itp->second && !it->second);
	}

	const InputVector2 Input::getMousePosition()
	{
		return mousePos;
	}

	const InputVector2 Input::getMousePositionCentered()
	{
		return centeredMousePos;
	}

	std::string Input::getKeyNameFiltered(int key) {

		char const* str = glfwGetKeyName(key, 0);
		if (str) return std::string(str);//Return normally if given key can be printed


		switch (key) {//When it returns nullptr after the glfw function, idk why they half finished the function
		case GLFW_KEY_LEFT_CONTROL: return "Left Ctrl";
		case GLFW_KEY_RIGHT_CONTROL: return "Right Ctrl";

		case GLFW_KEY_LEFT_SHIFT: return "Left Shift";
		case GLFW_KEY_RIGHT_SHIFT: return "Right Shift";

		case GLFW_KEY_LEFT_ALT: return "Left Alt";
		case GLFW_KEY_RIGHT_ALT: return "Right Alt";

		case GLFW_KEY_ESCAPE: return "Escape";
		case GLFW_KEY_ENTER: return "Enter";
		case GLFW_KEY_SPACE: return "Space";

		case GLFW_KEY_UP: return "Arrow Up";
		case GLFW_KEY_DOWN: return "Arrow Down";
		case GLFW_KEY_LEFT: return "Arrow Left";
		case GLFW_KEY_RIGHT: return "Arrow Right";

		case GLFW_KEY_TAB: return "Tab";
		default: return "Unknown Key";
		}
	}
}
