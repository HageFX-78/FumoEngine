#include "GameObject.h"
#include "GameObjectCollection.h"
#include "TransformComponent.h"
#include "RendererComponent.h"

#include <iostream>

GameObject::GameObject(std::string nName) : name(nName){
	transform = addComponent<TransformComponent>();
	renderer = addComponent<RendererComponent>();

	GameObjectCollection::add(this);
	std::cout << "<*> Game Object " << name << " is Instantiated" << std::endl;
}
GameObject::~GameObject()
{
	std::cout << "<!> Game Object " << name << " is Deleted" << std::endl;
	if (!components.empty())
	{
		for (auto component : components)
		{
			delete component;
		}
		components.clear();
	}
	
}
void GameObject::runComponentAwake()
{
	if (componentsJustAdded.size() == 0)
		return;

	for (auto newComponent : componentsJustAdded)
	{
		newComponent->awake();
	}
}

void GameObject::runComponentStart()
{
	if (componentsJustAdded.size() == 0)
		return;

	for (auto newComponent : componentsJustAdded)
	{
		newComponent->start();
	}
	componentsJustAdded.clear();
}

void GameObject::runComponentUpdate(float deltaTime)
{
	components.erase(std::remove_if(components.begin(), components.end(),
		[](BaseComponent* comp) {
			if (comp->shouldDestroy()) {
				delete comp;
				return true;
			}
			return false;
		}),
		components.end());// Erase 2nd parameter rrat

	for (auto component : components) {
		component->update(deltaTime);
	}
}

void GameObject::runComponentRender()
{
	for (auto component : components)
	{
		component->render();
	}
}

std::string GameObject::getName() const
{
	return name;
}
void GameObject::setName(std::string newName)
{
	name = newName;
}

void GameObject::destroy()
{
	flaggedForDeletion = true;
}

bool GameObject::shouldDestroy()
{
	return flaggedForDeletion;
}