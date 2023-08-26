#pragma once
#include <string>
#include <functional>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <string>

#include "angle_util/vector.h"
#include "WindowEventData.h"

namespace FumoEngine
{
	/// <summary>
	/// Window event enums to determine which event to act upon used in  WindowEventCallback
	/// </summary>
	enum WindowEvents {
		resize,
		close
	};

	struct GLFWwindow;
	typedef std::function<void(WindowEvents, void*)> WindowEventCallbackFn;
	struct WindowData {
		int width;
		int height;
		std::string title;
		WindowEventCallbackFn callback;
	};

	/// <summary>
	/// Application window that governs actions concerning the window itself.
	/// </summary>
	class AppWindow
	{
	public:
		~AppWindow(); // destructor
		int create(int width, int height, const char* title);
		void swap_and_poll();
		void setWindowEventCallback(const WindowEventCallbackFn& fn);

		::GLFWwindow* getWindowPtr();
		Vector2 getWindowSize();
	private:
		::GLFWwindow* window;
		WindowData data;
	};
}



