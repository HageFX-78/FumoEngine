#pragma once

//Player/User defined tags
namespace FumoEngine
{
	/// <summary>
	/// Tags that can assigned to game objects, it is part of the game engine.<br>
	/// Tags can be added to have more variety.<br>
	/// Each gameobject can only have one tag for now, tags are currently used for collision
	/// detection, multiple tags can be added to be collidable. During collision, gameobjects with said tags would only
	/// trigger a collision. All gameobjects have [default] type added as collidable by default.
	/// </summary>
	enum UserTag {
		Default,
		Player,
		Enemy,
		Bullet
	};
}
