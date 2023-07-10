#pragma once
#include "WIconUI.h"
namespace W
{
	class Equip : public IconUI
	{
	public:
		enum class EquipType
		{
			//목걸이 모자 신발 바지 장비
			Pandant,
			Hat,
			Top,
			Bottom,
			Shoes,
			Weapon,
			None,
		};

		Equip();
		virtual ~Equip();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();
		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();

		void SetEquipType(EquipType _eType) { m_eType = _eType; }
		EquipType GetEquipType() { return m_eType; }


	private:
		bool changepos_equipstate();
		bool changepos_inventory();

	private:
		EquipType m_eType;

	};
}


