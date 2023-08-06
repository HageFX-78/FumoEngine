#pragma once

#include <vector>
#include <string>
#include <type_traits>
#include <typeindex>
#include <unordered_set>
#include <iostream>

#include "BaseComponent.h"


class TransformComponent;
class RendererComponent;
class GameObject
{
public:
	GameObject(std::string nName = "New_GameObject");
	~GameObject();

	template <
		typename T,
		typename = typename std::enable_if<std::is_base_of<BaseComponent, T>::value>::type
	>

	T* addComponent() {

		auto availableInstance = getComponent<T>();//Check if the component exists or not

		if (availableInstance != nullptr)
		{
			if (!availableInstance->allowMultiple)//A bool inherited from baseComponent, just need to set to false in desired component if needed, else default to true
			{
				std::cout <<"<!> The " << typeid(T).name() << " cannot be added multiple times " << std::endl;
				return nullptr;
			}
		}

		T* newComponent = new T(this);
		componentsJustAdded.push_back(newComponent);
		components.push_back(newComponent);

		return newComponent;
	}

	template <
		typename T,
		typename = typename std::enable_if<std::is_base_of<BaseComponent, T>::value>::type
	>

	T* getComponent() {
		for (auto& c : components) {
			T* tryCast = dynamic_cast<T*>(c);
			if (tryCast != nullptr) {
				return tryCast;
			}
		}
		return nullptr;
	}

	void runComponentAwake();
	void runComponentStart();
	void runComponentUpdate(float deltaTime);
	void runComponentRender();

	std::string getName() const;
	void setName(std::string value);

	void destroy();
	bool shouldDestroy();

	TransformComponent* transform = nullptr;
	RendererComponent* renderer = nullptr;

protected:
	std::string name;
	

private:
	std::vector<BaseComponent*> components;
	std::vector<BaseComponent*> componentsJustAdded;
	bool flaggedForDeletion = false;

};