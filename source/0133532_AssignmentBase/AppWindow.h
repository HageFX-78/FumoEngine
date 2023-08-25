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



