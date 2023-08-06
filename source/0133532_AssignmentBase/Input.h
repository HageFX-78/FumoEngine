#pragma once

#include "AppWindow.h"
#include <glfw/glfw3.h>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>

struct InputVector2
{
	double x;
	double y;
};
class Input
{
public:
	static void processInput(AppWindow* window);

	static bool getAnyKey(int &firstKey);
	static bool getAnyKeyDown(int& firstKey);

	static void getAnyKeyAndProcess();

	static bool getKey(int key);
	static bool getKeyDown(int key);
	static bool getKeyUp(int key);
	static bool getMouseButton(int mb);
	static bool getMouseButtonDown(int mb);
	static bool getMouseButtonUp(int mb);

	static const InputVector2 getMousePosition();

	static std::string getKeyNameFiltered(int key);
private:
	static std::unordered_map<int, bool> key_states;
	static std::unordered_map<int, bool> previous_key_states;

	static std::unordered_map<int, bool> mouse_states;
	static std::unordered_map<int, bool> previous_mouse_states;

	static InputVector2 mousePos;
};

