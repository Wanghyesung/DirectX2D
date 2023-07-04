#pragma once

#include "WUI.h"
#include "WItemUI.h"
namespace W
{
	class Inventory : public UI
	{
	public:
		Inventory();
		virtual ~Inventory();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

		ItemUI* FindItem(std::wstring _strName);
		void AddItem(ItemUI* _pItem, std::wstring _strName);
		void DeleteItem(ItemUI* _pItem) { m_mapItems.erase(_pItem->GetName()); }

		bool SetItemPosition(ItemUI* _pItem);
		bool ChangeItemPosition(ItemUI* _pItem , Vector2 _vSetPosition);
		ItemUI* FindItemOnPosition(UINT _iX, UINT _iY);

	private:
		bool m_bRenderOn;
		std::map<std::wstring, ItemUI*> m_mapItems;

		bool m_bTargetOn;

		Vector2 m_vDragStartPos;

		Vector2 m_vUIStartPosition;
		Vector2 m_vUIEndPosition;
		Vector2 m_vUIDiffPosition;

		friend class InterfaceUI;
	};

}

