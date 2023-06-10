#pragma once
#include "WEntity.h"

namespace W
{
	using namespace W::enums;

	class Component
	{
	public:
		Component();
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LadteUpdate();
		virtual void Render();

	private:
		const eComponentType m_eType;

	};
}


