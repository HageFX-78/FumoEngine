#include "Application.h"
#include "SceneStateMachine.h"

#include "ShowCaseScene.h"
#include "SplashScene.h"

namespace FumoEngine
{
	/// <summary>
	/// A singleton so that it can be accessed globally to retrieve non-static values
	/// </summary>
	Application* Application::instance;


	int Application::initialize(int width, int height, const char* title)
	{
		instance = this;
		window = new AppWindow();

		Time::setTargetFrameRate(60);// Set initial framerate

		int result = window->create(width, height, title);
		if (result)
		{
			window->setWindowEventCallback([this](WindowEvents eventType, void* payload)
				{
					onReceiveWindowEvent(eventType, payload);
				});
		}
		isRunning = true;
		isPaused = false;

		// Scene Creation ------------------------------------------

		SceneStateMachine::addScene<Showcase::SplashScene>();
		SceneStateMachine::addScene<Showcase::ShowCaseScene>();
		SceneStateMachine::loadScene("SplashScene");

		// ---------------------------------------------------------


		return result;
	}

	void Application::run()
	{
		while (isRunning)
		{
			// Timing --------------------------------------------------------------	
			Time::process();//Process time, delta time and frame limiting
			// ---------------------------------------------------------------------


			// Input Processing ----------------------------------------------------
			Input::processInput(window);

			// Global Key Inputs
			if (Input::getKey(GLFW_KEY_ESCAPE))
			{
				isRunning = false;
			}
			if (Input::getKeyDown(GLFW_KEY_TAB))
			{
				isPaused = !isPaused;
			}
			// ---------------------------------------------------------------------

			// Updates -------------------------------------------------------------
			std::string titleText = SceneStateMachine::getCurrentSceneName() + "      [ " + Time::getCurrentFPS().c_str() + " ]" +
				"     State : [ " + (isPaused ? "Paused" : "Running") + " ]";
			glfwSetWindowTitle(window->getWindowPtr(), titleText.c_str());

			if (!isPaused)
				SceneStateMachine::update(Time::getDeltaTime());
			// ---------------------------------------------------------------------

			// Rendering --------------------------------------------------------s---
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			SceneStateMachine::render();

			window->swap_and_poll();
		}
	}
	void Application::shutdown()
	{
		// Scene Deletion ------------------------------------------
		SceneStateMachine::dispose();
		// ---------------------------------------------------------

		delete window;
	}


	void Application::onReceiveWindowEvent(WindowEvents eventType, void* payload)
	{
		if (eventType == close)
		{
			std::cout << "[?] Window Close Event" << std::endl;
			isRunning = false;
		}
		else if (eventType == resize)
		{
			std::cout << "[?] Window Resize Event" << std::endl;

			WindowEventData* eventData = static_cast<WindowEventData*>(payload);
			ViewportSizeData* vpd = static_cast<ViewportSizeData*>(eventData->getPayload());


			glViewport(0, 0, vpd->width, vpd->height);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			glOrtho(-vpd->width / 2, vpd->width / 2, -vpd->height / 2, vpd->height / 2, -1, 1);//Center render in the view

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}
	}

	Vector2 Application::getWindowSize()
	{
		return window->getWindowSize();
	}
}



