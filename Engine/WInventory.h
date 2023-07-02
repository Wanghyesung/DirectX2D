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

	private:
		void SetItemPos(ItemUI* _pItem);

	private:
		bool m_bRenderOn;
		std::map<std::wstring , ItemUI*> m_mapItems;


		friend class InterfaceUI;
	};

}

