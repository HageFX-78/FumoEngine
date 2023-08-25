#include "GameObject.h"
#include "GameObjectCollection.h"
#include "TransformComponent.h"
#include "RendererComponent.h"

#include <iostream>

GameObject::GameObject(std::string nName, UserTag goTag) : name(nName), tag(goTag) {
	transform = addComponent<TransformComponent>();

	GameObjectCollection::add(this);
}
GameObject::~GameObject()
{
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

UserTag GameObject::getTag() const
{
	return tag;
}

void GameObject::setTag(UserTag value)
{
	tag = value;
}

void GameObject::destroy()
{
	flaggedForDeletion = true;
}

bool GameObject::shouldDestroy()
{
	return flaggedForDeletion;
}

void GameObject::setIsActive(bool value)
{
	isActive = value;
}

bool GameObject::getIsActive()
{
	return isActive;
}
