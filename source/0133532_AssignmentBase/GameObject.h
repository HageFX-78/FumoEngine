#pragma once

#include <vector>
#include <string>
#include <type_traits>
#include <typeindex>
#include <unordered_set>
#include <iostream>

#include "BaseComponent.h"
#include "UserTags.h"

namespace FumoEngine
{
	class TransformComponent;
	class RendererComponent;
	/// <summary>
	/// Actors/Objects that can have logic and behaviour to interact with one another in a game scene.
	/// </summary>
	class GameObject
	{
	public:
		GameObject(std::string nName = "New_GameObject", UserTag goTag = Default);
		~GameObject();

		/// <summary>
		/// Add component(s) that have a base of BaseComponent<br>
		/// Components by default can be added to the same game object multiple times by default but can be disabled 
		/// by calling allowMultiple = false in the constructor or header file. It is a value inherited from BaseComponent<br><br>
		/// Works for component that inherited from components already inheriting BaseComponent.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <typeparam name=""></typeparam>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="...args">User may add 0 to multiple arguments as parameters to the constructor</param>
		/// <returns></returns>
		template <
			typename T,
			typename = typename std::enable_if<std::is_base_of<BaseComponent, T>::value>::type,
			typename... Args
		>
		T* addComponent(Args&&... args) {

			auto availableInstance = getComponent<T>();//Check if the component exists or not

			if (availableInstance != nullptr)
			{
				if (!availableInstance->allowMultiple)//A bool inherited from baseComponent, just need to set to false in desired component if needed, else default to true
				{
					std::cout << "<!> The " << typeid(T).name() << " cannot be added multiple times " << std::endl;
					return nullptr;
				}
			}

			T* newComponent = new T(this, std::forward<Args>(args)...);

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

		UserTag getTag() const;
		void setTag(UserTag value);

		void destroy();
		bool shouldDestroy();

		void setIsActive(bool value);
		bool getIsActive();

		TransformComponent* transform = nullptr;

	protected:
		std::string name;
		/// <summary>
		/// Tags to identify the type of actor a gameobject is, tags can be added in UserTags.h<br>
		/// Each gameObject can only be tagged with one type of tag.
		/// </summary>
		UserTag tag;

	private:
		std::vector<BaseComponent*> components;
		std::vector<BaseComponent*> componentsJustAdded;
		bool flaggedForDeletion = false;

		/// <summary>
		/// Active state of a gameObject, if disabled, object would not run Update and Render, useful for object pooling.
		/// </summary>
		bool isActive = true;

	};
}

