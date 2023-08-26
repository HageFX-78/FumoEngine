#pragma once
#include "AppWindow.h"
#include "Time.h"
#include "Input.h"
#include "WindowEventData.h"
#include "angle_util/vector.h"

#include <string>
#include <iostream>
#include <glfw/glfw3.h>
#include <glad/glad.h>

namespace FumoEngine
{
	/// <summary>
	/// This class defines the core structure of the Fumo Engine's main application. 
	/// It initializes the engine, manages scenes, handles input, updates and renders scenes, and responds to window events. 
	/// It creates a loop for continuous execution, allowing scenes to evolve. 
	/// </summary>
	class Application
	{
	public:
		static Application* instance;
		int initialize(int width, int height, const char* title);
		void run();
		void shutdown();
		void onReceiveWindowEvent(WindowEvents eventType, void* payload);

		Vector2 getWindowSize();

	private:
		AppWindow* window;
		Time* time;
		Input* input;
		bool isRunning;
		bool isPaused;
	};
}


