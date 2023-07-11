#pragma once


namespace W::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		Collider2D,
		Rigidbody,
		Particle,
		MeshRenderer,
		Script,
		Camera,
		End,
	};

	enum class eLayerType
	{
		Default,
		Grid,
		Camera,
		Background,
		Ground,
		Player,
		NPC,
		Ladder,
		Object,
		Monster,
		UI,
		End,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		End,
	};

	enum class eCameraType
	{
		Object,
		UI,
		None,
	};

	enum class eParentUI
	{
		Interface,
		Inventory,
		SkillStorage,
		EquipState,
		None,
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End,
	};
	
}
