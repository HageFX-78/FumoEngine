#pragma once
#include <glfw/glfw3.h>
#include <iostream>
#include <string>

class Time
{
public:
	static void process();
	static void setTargetFrameRate(unsigned int targetFrameRate);
	static float getDeltaTime();
	static float getProcessedTime();
	static std::string getCurrentFPS();
private:
	static float gameTime;
	static float prevTime;
	static float deltaTime;
	static float frameTime;
};

