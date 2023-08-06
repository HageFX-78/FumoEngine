#include "Time.h"

float Time::gameTime = 0.0f;
float Time::prevTime = 0.0f;
float Time::deltaTime = 0.0f;
float Time::frameTime = 0.0f;

void Time::process()
{
	gameTime = glfwGetTime();
	deltaTime = gameTime - prevTime;

	//Frame limiting
	while (deltaTime < frameTime) {
		gameTime = glfwGetTime();
		deltaTime = gameTime - prevTime;
	}

	prevTime = gameTime; // cache the current time for next update.
}

void Time::setTargetFrameRate(unsigned int targetFrameRate)
{
	frameTime = targetFrameRate == 0 ? 0.0f : 1.0f / targetFrameRate;
}

float Time::getProcessedTime()
{
	return gameTime;
}

float Time::getDeltaTime()
{
	return deltaTime;
}

std::string Time::getCurrentFPS()
{
	return "FPS: " + std::to_string(1.0f / getDeltaTime());
}