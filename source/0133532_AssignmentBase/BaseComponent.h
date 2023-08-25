#pragma once

namespace FumoEngine
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent(GameObject* go);
		virtual ~BaseComponent() = 0; // pure virtual
		virtual void awake();
		virtual void start();
		virtual void update(float deltaTime);
		virtual void render();
		void destroy();
		bool shouldDestroy();

		bool allowMultiple = true;//Default true to allow components to be added more than once in a single GameObject
	protected:
		GameObject* gameObject;
		bool flaggedForDeletion = false;

	};
}


