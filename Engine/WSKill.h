#pragma once
#include "WSKillStorage.h"
#include "WIconUI.h"

namespace W
{
	class SKill : public IconUI
	{
	public:
		SKill();
		virtual ~SKill();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();
		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();

		void SetSkillNuber(SKillStorage::eSkillNuber _eNuber) { eSkillNuber = _eNuber; }

		void SetClone(bool _bOn) { m_bClone = _bOn; }
		void SetOwner(SKill* _pSKill) { m_pOwnerClone = _pSKill; }
		bool IsClone() { return m_bClone; }

		SKill* GetClone() { return m_pOwnerClone; }
		void SetNullClone() { m_pSKillClone = nullptr; }

	private:
		void create_clone();

		//스킬은 interace만 확인
		void check_interface();
		bool changepos_interface();

	private:
		bool m_bTargetOn;
		bool m_bClone;//클론이면 움직임없이

		//내 클론 UI, 부모
		SKill* m_pSKillClone;
		SKill* m_pOwnerClone;
		Vector2 m_vDragStartPos;
		Vector3 m_vStartPos;
		SKillStorage::eSkillNuber eSkillNuber;

	};
}


