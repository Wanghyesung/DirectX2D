#pragma once
#include "WUI.h"

namespace W
{
	class Inventory;

	class InterfaceUI : public UI
	{
	public:
		InterfaceUI();
		virtual ~InterfaceUI();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();//UI���� ���콺 �ö���� �� 
		virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
		virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
		virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

		void ActiveInventory();
	private:
		Inventory* m_pInventory;
	};

}

