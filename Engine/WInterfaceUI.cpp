#include "WInterfaceUI.h"
#include "WResources.h"
#include "WChannleBntUI.h"
#include "WTransform.h"

namespace W
{
	InterfaceUI::InterfaceUI()
	{
		std::shared_ptr<Texture> pInterfaceTex =
			Resources::Load<Texture>(L"InterfaceTex", L"..\\Resources\\Texture\\UI\\Interface\\back_0.png");

		std::shared_ptr<Material> pInterfaceMater = std::make_shared<Material>();
		pInterfaceMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pInterfaceMater->SetTexture(pInterfaceTex);
		Resources::Insert(L"InterfaceMater", pInterfaceMater);
	}
	InterfaceUI::~InterfaceUI()
	{
		//AddChildUI()
	}
	void InterfaceUI::Initialize()
	{
		//ÀÚ½ÄUI
		ChannleBntUI* pChannleUI = new ChannleBntUI();
		//Vector3 vPos = this->GetComponent<Transform>()->GetPosition();
		//pChannleUI->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -0.1f) + vPos);
		pChannleUI->GetComponent<Transform>()->SetPosition(0.f,0.f,-0.22f);
		pChannleUI->GetComponent<Transform>()->SetScale(1.5f * 0.5f, 0.7f * 0.5f, 0.f);
		AddChildUI(pChannleUI);
	}
	void InterfaceUI::Update()
	{
		UI::Update();
	}
	void InterfaceUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void InterfaceUI::Render()
	{
		UI::Render();
	}
	void InterfaceUI::MouseOn()
	{

	}
	void InterfaceUI::MouseLbtnDown()
	{

	}
	void InterfaceUI::MouseLbtnUp()
	{

	}
	void InterfaceUI::MouseLbtnClicked()
	{

	}

}