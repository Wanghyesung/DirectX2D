#include "WSKill.h"
#include "WInput.h"
#include "WTransform.h"
namespace W
{
	SKill::SKill():
		m_bTargetOn(false),
		m_vDragStartPos(Vector3::One)
	{

	}
	SKill::~SKill()
	{

	}
	void SKill::Initialize()
	{

	}
	void SKill::Update()
	{
		UI::Update();
	}
	void SKill::LateUpdate()
	{
		UI::LateUpdate();
	}
	void SKill::Render()
	{
		UI::Render();
	}
	void SKill::MouseOn()
	{
		if (m_bTargetOn)
		{
			Transform* pTransform = GetComponent<Transform>();
			Vector2 vMousePos = Input::GetMousePos();

			Vector2 vDiff = vMousePos - m_vDragStartPos;
			Vector3 vPosisition = pTransform->GetPosition() + vDiff;

			pTransform->SetPosition(vPosisition);

			//MoveToParent(vDiff);

			m_vDragStartPos = Input::GetMousePos();
		}
	}
	void SKill::MouseLbtnDown()
	{
		m_bTargetOn = true;

		m_vDragStartPos = Input::GetMousePos();
	}
	void SKill::MouseLbtnUp()
	{
		m_bTargetOn = false;

		//m_vDragStartPos = Input::GetMousePos();
	}
	void SKill::MouseLbtnClicked()
	{

	}
}