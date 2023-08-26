#pragma once

#include <unordered_set>
#include <glad/glad.h>
#include "angle_util/vector.h"
#include "angle_util/matrix.h"

#include "BaseComponent.h"
#include "TransformComponent.h"

namespace FumoEngine
{
	/// <summary>
	/// Simple circular trigger collider that fires OnCollisionEnter(), OnCollisionStay(), OnCollisionExit() which can be overriden and defined
	/// with custom user logic for each individual game object. By default it doesn't do anything.
	/// <br><br>
	/// - You need to inherit this class and override the 3 aforementioned functions to provide custom logic.<br>
	/// - You can add collidable tags to determine what can and cannot collide with this game object with `addCollidableTag(UserTag)`.
	/// </summary>
	class CircleCollider : public BaseComponent
	{
	public:
		CircleCollider(GameObject* go, float rad = 5.0f, bool isVisible = false);
		~CircleCollider();

		/// <summary>
		/// This is where collisions are checked and fired on the overridable functions: OnTriggerOn(), OnTriggerStay(), OnTriggerExit()
		/// </summary>
		/// <param name="deltaTime"></param>
		void update(float deltaTime) override;
		void render() override;

		void setRadius(float rad);
		float getRadius() const;

		/// <summary>
		/// Gets center point of collider origin.
		/// </summary>
		/// <returns></returns>
		Vector2 getCenter() const;

		void addCollidableTag(UserTag typeName);
		void removeCollidableTag(UserTag typeName);
		std::unordered_set<UserTag> getCollidableTags();

		void setIsColliding(bool value);
		bool getIsColliding() const;

		/// <summary>
		/// Function that checks if a specific coordinate collides with this collider.
		/// </summary>
		/// <param name="point"></param>
		/// <returns></returns>
		bool containsPoint(const Vector2& point) const;
		/// <summary>
		/// Functions that checks if two colliders overlap.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool checkCircleCollision(const CircleCollider& other);

		/// <summary>
		/// Overridable function similar to Unity OnTriggerEnter(), inherit this function from this class to call custom logic in the scene.
		/// </summary>
		/// <param name="other">Collided object</param>
		virtual void OnCollisionEnter(GameObject& other);
		/// <summary>
		/// Overridable function similar to Unity OnTriggerStay(), inherit this function from this class to call custom logic in the scene.
		/// </summary>
		/// <param name="other">Collided object</param>
		virtual void OnCollisionExit(GameObject& other);
		/// <summary>
		/// Overridable function similar to Unity OnTriggerExit(), inherit this function from this class to call custom logic in the scene.
		/// </summary>
		/// <param name="other">Collided object</param>
		virtual void OnCollisionStay(GameObject& other);

		/// <summary>
		/// Global display colliders if true, will show every gameObject collider in the scene regardless of local showCollider setting.
		/// </summary>
		static bool globalShowCollider;

	protected:
		/// <summary>
		/// List of UserTags to determine which gameObjects are collidable, Default is added by default.
		/// </summary>
		std::unordered_set<UserTag> collidables = { Default };

		/// <summary>
		/// Cache to store collided gameObjects to determine whether this object has just collided, is still colliding or has stopped colliding.
		/// </summary>
		std::unordered_set<GameObject*> collidedCache;

		TransformComponent* localTransform;
		float radius;

		bool isColliding = false;
		/// <summary>
		/// Display colliders if true
		/// </summary>
		bool showCollider = false;

	};
}


