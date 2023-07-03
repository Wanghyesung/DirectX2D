#pragma once
#include "WUI.h"

namespace W
{
	class Inventory;
	class ItemUI;

	class InterfaceUI : public UI
	{
	public:
		InterfaceUI();
		virtual ~InterfaceUI();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void MouseOn();//UI위에 마우스 올라왔을 떄 
		virtual void MouseLbtnDown();//UI안에서 눌렸을 떄
		virtual void MouseLbtnUp();//UI안에서 땠을 때
		virtual void MouseLbtnClicked();//UI안에서 누르고 떘을 떄

		void ActiveInventory();

		void AddItem(ItemUI* _pItem, std::wstring _strName);
		ItemUI* FindItem(std::wstring _strName);

	private:
		bool setitemposition(ItemUI* _pItem);

	private:
		Inventory* m_pInventory;

		//2.28 -3.21
		Vector2 m_vUIStartPosition;
		
		//3.3 -3.55
		Vector2 m_vUIEndPosition;
		
		// 0.255 //0.34
		Vector2 m_vUIDiffPosition;

		std::map<std::wstring, ItemUI*> m_mapItems;
	};

}

