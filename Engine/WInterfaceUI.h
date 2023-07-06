#pragma once
#include "WUI.h"
#include "WItemUI.h"

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

		virtual void MouseOn();//UI���� ���콺 �ö���� �� 
		virtual void MouseLbtnDown();//UI�ȿ��� ������ ��
		virtual void MouseLbtnUp();//UI�ȿ��� ���� ��
		virtual void MouseLbtnClicked();//UI�ȿ��� ������ ���� ��

		void DeleteItem(ItemUI* _pItem) { m_mapItems.erase(_pItem->GetName()); }
		//void AddItem(ItemUI* _pItem, std::wstring _strName);
		ItemUI* FindItem(std::wstring _strName);

		void CheckItemPosition(ItemUI* _pItem);
		bool SetItemPosition(ItemUI* _pItem);

		bool ChangeItemPosition(ItemUI* _pItem, Vector2 _vSetPosition);
		ItemUI* FindItemOnPosition(UINT _iX, UINT _iY);
		ItemUI* GetItemSamePos(ItemUI* _pItem);

		Vector2 GetStartPosition() { return m_vUIStartPosition; }
		Vector2 GetEndPosition() { return m_vUIEndPosition; }
		Vector2 GetDiffPosition() { return m_vUIDiffPosition; }

	private:
		//2.28 -3.21
		Vector2 m_vUIStartPosition;
		
		//3.3 -3.55
		Vector2 m_vUIEndPosition;
		
		// 0.255 //0.34
		Vector2 m_vUIDiffPosition;

		std::map<std::wstring, ItemUI*> m_mapItems;
	};

}

