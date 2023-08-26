#pragma once
#include <glfw/glfw3.h>
#include <iostream>
#include <string>

namespace FumoEngine
{
	/// <summary>
	/// The class that governs time of the overall engine, if timeScale is set to 0, everything outside of application will cease to run.
	/// </summary>
	class Time
	{
	public:
		static void process();
		static void setTargetFrameRate(unsigned int targetFrameRate);
		static float getDeltaTime();
		static float getProcessedTime();
		static std::string getCurrentFPS();

		static float getTimeScale();
		static void setTimeScale(float value);
	private:
		static float gameTime;
		static float prevTime;
		static float deltaTime;
		static float frameTime;
		/// <summary>
		/// An additional value to slow down/speed up time, doing timeScale = 0 will freeze the game but all inputs within the scene would not be processed.<br>
		/// Application defined Inputs are still processed.
		/// </summary>
		static float timeScale;
	};
}


