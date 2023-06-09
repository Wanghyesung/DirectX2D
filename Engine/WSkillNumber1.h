#pragma once
#include "WUI.h"

namespace W
{
	class SkillNumber1 : public UI
	{
	public:
		SkillNumber1();
		virtual ~SkillNumber1();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();
		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();

		void SetActive(bool _bOn) { m_bActive = _bOn; }
		bool IsActive() { return m_bActive; }

		class SKill* CreateClone(class SKill* _pSkill);
	private:
		bool m_bActive;

		Vector3 m_vDarkSkillPosition;
		Vector3 m_vLuckSkillPosition;
	};
}


