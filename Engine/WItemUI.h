#pragma once
#include "WUI.h"

namespace W
{
	class ItemUI : public UI
	{
	public:
		ItemUI();
		virtual ~ItemUI();
		
		virtual void Initialize() override;
		virtual void Update()override;
		virtual void LateUpdate()override;
		virtual void Render()override;

		virtual void MouseOn()override;
		virtual void MouseLbtnDown()override;
		virtual void MouseLbtnUp()override;
		virtual void MouseLbtnClicked()override;

		void SetItemIndexX(UINT _iX, UINT _iY) { m_iItemIndexX = _iX; m_iItemIndexY = _iY; }

		UINT GetItemindexX() { return m_iItemIndexX; }
		UINT GetItemIndexY() { return m_iItemIndexY; }

	private:
		bool m_bTargetOn;

		Vector2 m_vDragStartPos;
		Vector2 m_vDragEndPos;

		UINT m_iItemIndexX;
		UINT m_iItemIndexY;
	};
}


