#pragma once

namespace FumoEngine
{
	class GameObject;
	/// <summary>
	/// Base class for all components, modular classes meant to be added to game objects to give them functionality.
	/// </summary>
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

		/// <summary>
		/// Determines if a component can be added multiple times to a game Object.
		/// </summary>
		bool allowMultiple = true;//Default true to allow components to be added more than once in a single GameObject
	protected:
		GameObject* gameObject;
		bool flaggedForDeletion = false;

	};
}


