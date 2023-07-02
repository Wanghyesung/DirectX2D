#include "WItemUI.h"
#include "WInput.h"
#include "WTransform.h"
namespace W
{
	ItemUI::ItemUI():
		m_bTargetOn(false),
		m_vDragStartPos(Vector2::One),
		m_vDragEndPos(Vector2::One),
		m_iItemIndexX(0),
		m_iItemIndexY(0)
	{
	}
	ItemUI::~ItemUI()
	{
	}
	void ItemUI::Initialize()
	{

	}
	void ItemUI::Update()
	{
		UI::Update();
	}
	void ItemUI::LateUpdate()
	{	
		if (m_bTargetOn)
		{
			Transform* pTransform = GetComponent<Transform>();
			Vector2 vMousePos = Input::GetMousePos();

			Vector2 vDiff = vMousePos - m_vDragStartPos;
			Vector3 vPosisition = pTransform->GetPosition() + vDiff;

			pTransform->SetPosition(vPosisition);

			m_vDragStartPos = Input::GetMousePos();
		}

		UI::LateUpdate();
	}
	void ItemUI::Render()
	{
		UI::Render();
	}
	void ItemUI::MouseOn()
	{

	}
	void ItemUI::MouseLbtnDown()
	{
		m_bTargetOn = true;

		m_vDragStartPos = Input::GetMousePos();
	}
	void ItemUI::MouseLbtnUp()
	{
		m_bTargetOn = false;

		m_vDragEndPos = Input::GetMousePos();
	}
	void ItemUI::MouseLbtnClicked()
	{

	}
}