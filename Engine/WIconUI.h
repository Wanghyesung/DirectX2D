#pragma once
#include "WUI.h"
namespace W
{
	class IconUI : public UI
	{
	public:
		enum class eIconType
		{
			Item,
			SKill,
			Equip,
			None
		};

		IconUI();
		virtual ~IconUI();

		void SetIconType(eIconType _eType) { m_eType = _eType; }
		eIconType GetIconType() { return m_eType; }

	private:
		eIconType m_eType;
	};
}


