#pragma once
#include "WUI.h"

//hlsl 헤더파일 (글로벌)
// 공통적으로 사용하는 샘플러, 상수버퍼를 #include 헤러파일로 추가가능
// 그리드를 가장 안쪽으로해서 가장 마지막에 그리게
// 흰색부분 discard
//

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

		void SetParentUIType(eParentUI _eType) { m_ePrevParentType = m_eParentType; m_eParentType = _eType; }
		eParentUI GetParentUIType() { return m_eParentType; }

		void SetItemIndex(int _iX, int _iY) { m_iItemIndexX = _iX; m_iItemIndexY = _iY; }
		int GetItemindexX() { return m_iItemIndexX; }
		int GetItemIndexY() { return m_iItemIndexY; }
		
		Vector3 GetStartPosition() { return m_vStartPos; }

		void DeleteParent();
	private:
		void changepos_interface();
		void changepos_inventory();

		bool check_postion();
		bool check_inventory();
		bool check_interface();
	private:
		bool m_bTargetOn;
		
		eParentUI m_eParentType;
		eParentUI m_ePrevParentType;

		Vector2 m_vDragStartPos;
		Vector2 m_vDragEndPos;
		Vector3 m_vStartPos;

		int m_iItemIndexX;
		int m_iItemIndexY;
	};
}


