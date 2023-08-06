#pragma once
#include "AppWindow.h"
#include "Time.h"
#include "WindowEventData.h"
#include "Input.h"

#include <string>
#include <iostream>
#include <glfw/glfw3.h>
#include <glad/glad.h>


class Application
{
public:
	int initialize(int width, int height, const char* title);
	void run();
	void shutdown();
	void onReceiveWindowEvent(WindowEvents eventType, void* payload);
private:
	AppWindow* window;
	Time* time;
	Input* input;
	bool isRunning;
};

