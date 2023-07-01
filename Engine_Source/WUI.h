#pragma once
#include "WGameObject.h"
#include "WResources.h"
namespace W
{

	class UI : public GameObject
	{
	public:
		UI();
		virtual ~UI();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();//UI���� ���콺 �ö���� �� 
		virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
		virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
		virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

		UI* GetParentUI() { return m_pParentUI; }
		void AddChildUI(UI* _pUI);

		bool IsLBntDown() { return m_bLbntDown; }
		bool IsMosueOn() { return m_bMouseOn; }

	private:
		//�ڽ� UI ������Ʈ
		void ChildUpdate();
		void ChildRender();
		void ChildLateupdate();

		void MouseOnCheck();

		void MoveToParent();

		const std::vector<UI*> GetChildUI() { return m_vecChildUI; }
	private:
		//�� �ڽ� UI
		std::vector<UI*> m_vecChildUI;
		//�� �θ� UI
		UI* m_pParentUI;
		Vector3 m_vParntUIPos;
		bool m_bMouseOn;
		bool m_bLbntDown;

		friend class UIManger;
	};

}

