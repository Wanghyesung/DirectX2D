#include "WSKill.h"
#include "WSKillStorage.h"
#include "WInput.h"
#include "WTransform.h"
#include "WSkillNumber1.h"
#include "WInterfaceUI.h"
#include "WSceneManger.h"
#include "WObject.h"
namespace W
{
	SKill::SKill() :
		m_bTargetOn(false),
		m_bClone(false),
		m_vDragStartPos(Vector2::One),
		m_vStartPos(Vector3::One),
		eSkillNuber(SKillStorage::eSkillNuber::None),
		m_pSKillClone(nullptr)
	{
		SetIconType(eIconType::SKill);
		SetParentUIType(eParentUI::SkillStorage);
	}
	SKill::~SKill()
	{

	}
	void SKill::Initialize()
	{

	}
	void SKill::Update()
	{
		IconUI::Update();
	}
	void SKill::LateUpdate()
	{
		IconUI::LateUpdate();
	}
	void SKill::Render()
	{
		IconUI::Render();
	}
	void SKill::MouseOn()
	{
		//스킬을 누르면 해당 스킬에 맞는 UI를 새로 생성
		IconUI::MouseOn();
		//if (m_bTargetOn)
		//{
		//	Transform* pTransform = GetComponent<Transform>();
		//	Vector2 vMousePos = Input::GetMousePos();
		//
		//	Vector2 vDiff = vMousePos - m_vDragStartPos;
		//	Vector3 vPosisition = pTransform->GetPosition() + vDiff;
		//
		//	pTransform->SetPosition(vPosisition);
		//
		//	//MoveToParent(vDiff);
		//
		//	m_vDragStartPos = Input::GetMousePos();
		//}
	}
	void SKill::MouseLbtnDown()
	{	
		IconUI::MouseLbtnDown();

		eParentUI eType = GetParentUIType();
		if (eType != eParentUI::SkillStorage)
			return;

		if (m_pSKillClone == nullptr && m_pOwnerClone == nullptr)
			create_clone();
	}
	void SKill::MouseLbtnUp()
	{
		IconUI::MouseLbtnUp();

		check_interface();
	}
	void SKill::MouseLbtnClicked()
	{

	}

	void SKill::create_clone()
	{
		UI* pParentUI = GetParentUI();
		switch (eSkillNuber)
		{
		case W::SKillStorage::eSkillNuber::First:
			m_pSKillClone = dynamic_cast<SkillNumber1*>(pParentUI)->CreateClone(this);//클론만들고 반환받기
			break;
		case W::SKillStorage::eSkillNuber::Second:
			break;
		case W::SKillStorage::eSkillNuber::Third:
			break;
		case W::SKillStorage::eSkillNuber::Four:
			break;
		case W::SKillStorage::eSkillNuber::Five:
			break;

		}
	}

	void SKill::check_interface()
	{
		Transform* pTransform = GetComponent<Transform>();
		Vector3 vPosition = pTransform->GetPosition();

		InterfaceUI* pInterface = SceneManger::GetUI<InterfaceUI>();

		Vector2 vUIStartPosition = pInterface->GetStartPosition();
		Vector2 vUIEndPosition = pInterface->GetEndPosition();
		Vector2 vUIDiffPosition = pInterface->GetDiffPosition();

		//인터페이스 범위 밖이면
		if (!((vPosition.x <= vUIEndPosition.x + vUIDiffPosition.x && vPosition.x >= vUIStartPosition.x - vUIDiffPosition.x) &&
			(vPosition.y >= vUIEndPosition.y + vUIDiffPosition.y && vPosition.y <= vUIStartPosition.y - vUIDiffPosition.y)))
		{

			if (GetParentUIType() == eParentUI::SkillStorage)
			{
				//클론 UI 삭제하고 원래 자리로
				object::Destroy(m_pSKillClone);
				m_pSKillClone = nullptr;
				Vector3 vStartPos = GetStartPosition();
				GetComponent<Transform>()->SetPosition((vStartPos));
			}
			else
			{
				vPosition = m_pSKillClone->GetComponent<Transform>()->GetPosition();
				pTransform->SetPosition(vPosition);

				pInterface->DeleteChildUI(this);
				pInterface->DeleteItem(this);

				m_pSKillClone->GetParentUI()->AddChildUI(this, false);
				SetParentUIType(eParentUI::SkillStorage);

				object::Destroy(m_pSKillClone);
				m_pSKillClone = nullptr;
			}
		}
			
		else
		{
			if (!changepos_interface())//실패하면
			{
				object::Destroy(m_pSKillClone);
				m_pSKillClone = nullptr;
				Vector3 vStartPos = GetStartPosition();
				GetComponent<Transform>()->SetPosition((vStartPos));
			}
		}
			

	}

	bool SKill::changepos_interface()
	{
		Transform* pSkillTransform = GetComponent<Transform>();
		Vector3 vSKillPosition = pSkillTransform->GetPosition();
		bool bSuccess = SceneManger::GetUI<InterfaceUI>()->ChangeItemPosition(this, Vector2(vSKillPosition.x, vSKillPosition.y));
		return bSuccess;
		//
		//
		//InterfaceUI* pInterface = SceneManger::GetUI<InterfaceUI>();
		//Vector2 vUIStartPosition = pInterface->GetStartPosition();
		//Vector2 vUIEndPosition = pInterface->GetEndPosition();
		//Vector2 vUIDiffPosition = pInterface->GetDiffPosition();
		//
		////내 skill 트렌스폼
		//
		//Vector2 vStartPosition = Vector2(vUIStartPosition.x, vUIStartPosition.y);
		//Vector2 vComaprePos = {};
		//
		////마우스 둔 우치에서 가장 가까운곳 찾기
		//Vector2 vMinValue = Vector2(2000.f, 2000.f);
		//float fMinLen = 2000.f;
		//UINT iMinX = 0;
		//UINT iMinY = 0;
		//
		//for (UINT y = 0; y < 2; ++y)
		//{
		//	vComaprePos.y = vStartPosition.y + y * vUIDiffPosition.y;
		//	for (UINT x = 0; x < 4; ++x)
		//	{
		//		vComaprePos.x = vStartPosition.x + x * vUIDiffPosition.x;
		//
		//		Vector2 vDiff = vSKillPosition - vComaprePos;
		//		float fLen = abs(vDiff.Length());
		//
		//		//아이템 둔곳에서 가장 가까운곳
		//		if (fLen <= fMinLen)
		//		{
		//			fMinLen = fLen;
		//			vMinValue = vComaprePos;
		//			iMinX = x;
		//			iMinY = y;
		//		}
		//	}
		//}
		//
		//IconUI* pFindItem = pInterface->FindItemOnPosition(iMinX, iMinY);
		//if (pFindItem != nullptr)
		//{
		//	if (pFindItem->GetIconType() == eIconType::Item)
		//	{
		//		return false;
		//	}
		//	else
		//	{
		//		SKill* pSKill = dynamic_cast<SKill*>(pFindItem);
		//		pSKill->DeleteParent();
		//		pSKill->m_pSKillClone->SetClone(false);
		//		pSKill->m_pSKillClone = nullptr;
		//	}
		//}
		//
		//pSkillTransform->SetPosition(vMinValue.x, vMinValue.y, vSKillPosition.z);
		//SetItemIndex(iMinX, iMinY);
		//this->DeleteParent();
		//pInterface->InsertItem(this, GetName());
		//return true;
	}

}