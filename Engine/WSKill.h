#pragma once
#include "WUI.h"
#include "WSKillStorage.h"

namespace W
{
	class SKill : public UI
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
		bool IsClone() { return m_bClone; }

	private:
		void create_clone();

		//��ų�� interace�� Ȯ��
		void check_interface();
		bool changepos_interface();

	private:
		bool m_bTargetOn;
		bool m_bClone;//Ŭ���̸� �����Ӿ���

		SKill* m_pSKillClone;
		Vector2 m_vDragStartPos;
		Vector3 m_vStartPos;
		SKillStorage::eSkillNuber eSkillNuber;

	};
}


