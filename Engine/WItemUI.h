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

		void SetParentUIType(eParentUI _eType) { m_eParentType = _eType; }
		eParentUI GetParentUIType() { return m_eParentType; }

		void SetItemIndex(int _iX, int _iY) { m_iItemIndexX = _iX; m_iItemIndexY = _iY; }
		int GetItemindexX() { return m_iItemIndexX; }
		int GetItemIndexY() { return m_iItemIndexY; }

		void SetInterIndex(int _iX, int _iY) { m_iInterIndexX = _iX; m_iInterIndexY = _iY; }

		int GetInterindexX() { return m_iInterIndexX; }
		int GetInterIndexY() { return m_iInterIndexY; }
		
		Vector3 GetStartPosition() { return m_vStartPos; }

	private:
		void changepos_interface();
		void changepos_inventory();

	private:
		bool m_bTargetOn;
		
		eParentUI m_eParentType;

		Vector2 m_vDragStartPos;
		Vector2 m_vDragEndPos;
		Vector3 m_vStartPos;

		int m_iItemIndexX;
		int m_iItemIndexY;

		int m_iInterIndexX;
		int m_iInterIndexY;
	};
}


