#include "WIconUI.h"
#include "WSceneManger.h"
#include "WInterfaceUI.h"
#include "WSKillStorage.h"
#include "WInventory.h"
#include "WInput.h"
#include "WTransform.h"

namespace W
{
	IconUI::IconUI():
		m_bTargetOn(false),
		m_vDragStartPos(Vector2::One),
		m_vDragEndPos(Vector2::One),
		m_iItemIndexX(-1),
		m_iItemIndexY(-1),
		m_iPrevIndexX(-1),
		m_iPrevIndexY(-1),
		m_eType(eIconType::None),
		m_eParentType(eParentUI::None),
		m_ePrevParentType(eParentUI::None)
	{
	}
	IconUI::~IconUI()
	{
	}
	void IconUI::Initialize()
	{
	}
	void IconUI::Update()
	{
		UI::Update();
	}
	void IconUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void IconUI::Render()
	{
		UI::Render();
	}
	void IconUI::MouseOn()
	{
		if (m_bTargetOn)
		{
			Transform* pTransform = GetComponent<Transform>();
			Vector2 vMousePos = Input::GetMousePos();

			Vector2 vDiff = vMousePos - m_vDragStartPos;
			Vector3 vPosisition = pTransform->GetPosition() + vDiff;

			pTransform->SetPosition(vPosisition);

			MoveToParent(vDiff);

			m_vDragStartPos = Input::GetMousePos();
		}
	}
	void IconUI::MouseLbtnDown()
	{
		m_bTargetOn = true;

		m_vDragStartPos = Input::GetMousePos();

		Transform* pTransform = GetComponent<Transform>();

		Vector3 vPosition = pTransform->GetPosition();
		vPosition.z -= 0.1f;
		pTransform->SetPosition(vPosition);

		m_vStartPos = pTransform->GetPosition();
	}
	void IconUI::MouseLbtnUp()
	{
		m_bTargetOn = false;

		m_vDragEndPos = Input::GetMousePos();
		Transform* pTransform = GetComponent<Transform>();
		Vector3 vPosition = pTransform->GetPosition();

		vPosition.z = m_vStartPos.z;
		pTransform->SetPosition(vPosition);
	}
	void IconUI::MouseLbtnClicked()
	{

	}
	void IconUI::DeleteParent()
	{
		switch (m_eParentType)
		{
		case W::enums::eParentUI::Interface:
		{
			UI* pParentUI = GetParentUI();
			InterfaceUI* pInter = dynamic_cast<InterfaceUI*>(pParentUI);
			pInter->DeleteItem(this);
			pInter->DeleteChildUI(this);
		}
		break;
		case W::enums::eParentUI::Inventory:
		{
			UI* pParentUI = GetParentUI();
			Inventory* pInven = dynamic_cast<Inventory*>(pParentUI);
			pInven->DeleteItem(this);
			pInven->DeleteChildUI(this);
		}
		break;
		case W::enums::eParentUI::SkillStorage:
		{
			UI* pParentUI = GetParentUI();
			pParentUI->DeleteChildUI(this);
		}
		break;
		default:
			break;
		}
	}
}