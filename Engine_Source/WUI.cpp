#include "WUI.h"
#include "WTransform.h"
#include "WInput.h"
#include "WCamera.h"
#include "WSceneManger.h"
#include "WApplication.h"

extern W::Application application;

namespace W
{
	UI::UI():
		m_bLbntDown(false),
		m_bMouseOn(false),
		m_pParentUI(nullptr),
		m_vecChildUI{},
		m_vParntUIPos{}
	{

	}
	UI::~UI()
	{
		for (UI* pChildUI : m_vecChildUI)
		{
			if (pChildUI != nullptr)
			{
				delete pChildUI;
				pChildUI = nullptr;
			}
		}
	}
	void UI::Initialize()
	{

	}
	void UI::Update()
	{
		GameObject::Update();

		ChildUpdate();
	}
	void UI::LateUpdate()
	{

		MoveToParent();

		//여기서 부모 UI랑 같이 움직이게
		GameObject::LateUpdate();
		//마우스 체크

		ChildLateupdate();

		MouseOnCheck();
	}
	void UI::Render()
	{
		GameObject::Render();

		ChildRender();
	}
	void UI::MouseOn()
	{

	}
	void UI::MouseLbtnDown()
	{

	}
	void UI::MouseLbtnUp()
	{

	}
	void UI::MouseLbtnClicked()
	{

	}
	void UI::AddChildUI(UI* _pUI)
	{
		m_vecChildUI.push_back(_pUI);
		_pUI->m_pParentUI = this;
	}
	void UI::ChildUpdate()
	{
		for (UI* pUI : m_vecChildUI)
		{
			pUI->Update();
		}
	}
	void UI::ChildRender()
	{
		for (UI* pUI : m_vecChildUI)
		{
			pUI->Render();
		}
	}
	void UI::ChildLateupdate()
	{
		for (UI* pUI : m_vecChildUI)
		{
			pUI->LateUpdate();
		}
	}
	void UI::MouseOnCheck()
	{
		RECT tRect = {};
		GetClientRect(application.GetHwnd(), &tRect);
		Transform* pTransform = GetComponent<Transform>();
		Vector3 vScale = pTransform->GetScale();
		Vector3 vPos = pTransform->GetPosition();

		Vector2 MousePos = Input::GetMousePos();
		math::Vector3 vMousePos(MousePos.x, MousePos.y, 0.f);

		math::Viewport view(0.f,0.f, tRect.right - tRect.left, tRect.bottom - tRect.top);
		vMousePos = view.Unproject(vMousePos, Camera::GetProjectionMatrix(), Camera::GetViewMatrix(), Matrix::Identity);
		
	
		if ((vPos.x - vScale.x/2.f) <= vMousePos.x && vMousePos.x <= (vPos.x + vScale.x/2.f) &&
			(vPos.y - vScale.y/2.f) <= vMousePos.y && vMousePos.y <= (vPos.y + vScale.y/2.f))
		{
			m_bMouseOn = true;
		}
		else
		{
			m_bMouseOn = false;
		}


	}
	void UI::MoveToParent()
	{
		if (m_pParentUI != nullptr)
		{
			Vector3 vFinalPos = {};

			Transform* pParentTransform = m_pParentUI->GetComponent<Transform>();
			Vector3 vParentPos = pParentTransform->GetPosition();
			if (vParentPos != m_vParntUIPos)
			{
				m_vParntUIPos = vParentPos;

				Transform* pTransform = GetComponent<Transform>();
				Vector3 vPos = pTransform->GetPosition();

				vFinalPos = vPos + vParentPos;
				//vPos.x += vParentPos.x;
				//vPos.y += vParentPos.y;
				pTransform->SetPosition(vFinalPos);
			}
		}
	}
}