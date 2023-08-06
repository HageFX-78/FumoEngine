#pragma once
#include "BaseScene.h"

#include <glad/glad.h>
#include <iostream>

#include "GameObjectCollection.h"
#include "SceneStateMachine.h"
#include "TransformComponent.h"
#include "RendererComponent.h"

#include "angle_util/matrix.h"
#include "angle_util/vector.h"

#include "Input.h"
#include "Time.h"

// -  -- -              -----------------      Classes



class TestAlexScene : public BaseScene {
public:
	std::string getName() const override {
		return "TestAlexScene";
	}

protected:

	void initialize() override {

		go1 = new GameObject("GameObject 1");
		go2 = new GameObject("GameObject 2");
	}
	void on_activate()
	{

		/*std::cout << "Object1 Name: " << go2->getName() << std::endl;
		std::cout << "Object1 X: " << go2->transform->getXPosition() << std::endl;*/
	}

	void on_deactivate()
	{

	}

	void on_update(float deltaTime)
	{
		tempTime += deltaTime;


		if (tempTime > 7 && !once)
		{

			//go2 = GameObjectCollection::find("GameObject 1");
			//go2 = new GameObject("GameObject 2");
			//go3 = GameObjectCollection::find("GameObject 2");
			once = true;
		}
	}
private:
	GameObject* go1;
	GameObject* go2;
	GameObject* go3;
	GameObject* go4;
	bool once = false;
	float tempTime = 0;

};

//Input testing from A1
class A1Scene : public BaseScene {
public:
	std::string getName() const override {
		return "A1Scene";
	}

	int anyKey = -1;
	int anyKeyDown = -1;
protected:
	void initialize() override {

	}

	void on_update(float deltaTime) override {

		// ### Get any Key inputs ### // Uncomment for extra functions, commented because it fills the terminal

			/*
			*
			if (Input::getAnyKeyDown(anyKeyDown))
			{
				std::cout << "The Key '" << Input::getKeyNameFiltered(anyKeyDown) << "' have been pressed " << std::endl;
			}

			if (Input::getAnyKey(anyKey))
			{
				std::cout << "The key '"<< Input::getKeyNameFiltered(anyKey) <<"' is still being pressed" << std::endl;
			}

			// Input and (process) all Keys not just the first one like getAnyKey() , but not viable for use

			Input::getAnyKeyAndProcess();

			*/

			//*/


#pragma region KeyInputs
		if (Input::getKeyDown(GLFW_KEY_A))
		{
			Time::setTargetFrameRate(20);
			std::cout << "User just pressed A key, setting frame limit to 20 FPS" << std::endl;
		}
		if (Input::getKey(GLFW_KEY_A))
		{
			std::cout << "User is holding down A key" << std::endl;
		}
		if (Input::getKeyUp(GLFW_KEY_A))
		{
			std::cout << "User just released A key" << std::endl;
		}

		if (Input::getKeyDown(GLFW_KEY_S))
		{
			Time::setTargetFrameRate(60);
			std::cout << "User just pressed S key, setting frame limit to 60 FPS" << std::endl;
		}

		if (Input::getKeyUp(GLFW_KEY_D))
		{
			Time::setTargetFrameRate(0);
			std::cout << "User just released D key, uncapping frame limit" << std::endl;
		}
#pragma endregion
		// ### Mouse Inputs ###
#pragma region mouseInputs
		if (Input::getMouseButtonDown(GLFW_MOUSE_BUTTON_1))
		{
			std::cout << "User just pressed left mouse button, cursor located at " << Input::getMousePosition().x << ", " << Input::getMousePosition().y << std::endl;
		}

		if (Input::getMouseButton(GLFW_MOUSE_BUTTON_1))
		{
			std::cout << "User is holding left mouse button, cursor located at " << Input::getMousePosition().x << ", " << Input::getMousePosition().y << std::endl;
		}

		if (Input::getMouseButtonUp(GLFW_MOUSE_BUTTON_1))
		{
			std::cout << "User just released left mouse button, cursor located at " << Input::getMousePosition().x << ", " << Input::getMousePosition().y << std::endl;
		}

		if (Input::getMouseButtonDown(GLFW_MOUSE_BUTTON_2))
		{
			std::cout << "User just pressed right mouse button, cursor located at " << Input::getMousePosition().x << ", " << Input::getMousePosition().y << std::endl;
		}

		if (Input::getMouseButton(GLFW_MOUSE_BUTTON_2))
		{
			std::cout << "User is holding down right mouse button, cursor located at " << Input::getMousePosition().x << ", " << Input::getMousePosition().y << std::endl;
		}

		if (Input::getMouseButtonUp(GLFW_MOUSE_BUTTON_2))
		{
			std::cout << "User just released right mouse button, cursor located at " << Input::getMousePosition().x << ", " << Input::getMousePosition().y << std::endl;
		}
#pragma endregion

	}

	void on_activate() override {
		glClearColor(0, 0.25, 0, 1);
	}
};
