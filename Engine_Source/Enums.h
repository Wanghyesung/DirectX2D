#pragma once


namespace W::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		Particle,
		MeshRenderer,
		Script,
		Camera,
		End,
	};

	enum class eLayerType
	{
		Default,
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

}
