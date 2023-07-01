#include "WInterfaceUI.h"
#include "WTransform.h"
#include "WChannleBntUI.h"
#include "WSystemUI.h"
#include "WMenuUI.h"
#include "WStarUI.h"
#include "WShopUI.h"
#include "WGaugeUI.h"
#include "WLevelUI.h"
#include "WInvenUI.h"
#include "WEquipUI.h"
#include "WCharUI.h"
#include "WStatUI.h"
#include "WQuestUI.h"
#include "WSKillUI.h"
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
		pChannleUI->GetComponent<Transform>()->SetPosition(1.65f,-0.23f,-0.01f);
		pChannleUI->GetComponent<Transform>()->SetScale(1.5f * 0.5f, 0.7f * 0.5f, 0.f);
		AddChildUI(pChannleUI);

		ShopUI* pShopUI = new ShopUI();
		pShopUI->GetComponent<Transform>()->SetPosition(-0.9f, -0.23f, -0.01f);
		pShopUI->GetComponent<Transform>()->SetScale(1.1f * 0.5f, 0.7f * 0.5f, 0.f); //11 : 7
		AddChildUI(pShopUI);

		StarUI* pStarUI = new StarUI();
		pStarUI->GetComponent<Transform>()->SetPosition(-0.3f, -0.23f, -0.01f);
		pStarUI->GetComponent<Transform>()->SetScale(1.1f * 0.5f, 0.7f * 0.5f, 0.f); //11 : 7
		AddChildUI(pStarUI);

		MenuUI* pMenuUI = new MenuUI();
		pMenuUI->GetComponent<Transform>()->SetPosition(0.3f, -0.23f, -0.01f);
		pMenuUI->GetComponent<Transform>()->SetScale(1.1f * 0.5f, 0.7f * 0.5f, 0.f); //11 : 7
		AddChildUI(pMenuUI);

		SystemUI* pSystemUI = new SystemUI();
		pSystemUI->GetComponent<Transform>()->SetPosition(0.9f, -0.23f, -0.01f);
		pSystemUI->GetComponent<Transform>()->SetScale(1.1f * 0.5f, 0.7f * 0.5f, 0.f); //11 : 7
		AddChildUI(pSystemUI);

		//extra
		CharUI* pCharUI = new CharUI();
		pCharUI->GetComponent<Transform>()->SetPosition(-0.77f, 0.06f, -0.01f);
		pCharUI->GetComponent<Transform>()->SetScale(1.619f * 0.17f, 1.f * 0.17f, 0.f); //1.619 : 1
		AddChildUI(pCharUI);

		StatUI* pStatUI = new StatUI();
		pStatUI->GetComponent<Transform>()->SetPosition(-0.45f, 0.06f, -0.01f);
		pStatUI->GetComponent<Transform>()->SetScale(1.619f * 0.17f, 1.f * 0.17f, 0.f); //1.619 : 1
		AddChildUI(pStatUI);

		QuestUI* pQuestUI = new QuestUI();
		pQuestUI->GetComponent<Transform>()->SetPosition(-0.18f, 0.06f, -0.01f);
		pQuestUI->GetComponent<Transform>()->SetScale(1.619f * 0.17f, 1.f * 0.17f, 0.f); //1.619 : 1
		AddChildUI(pQuestUI);

		InvenUI* pInvenUI = new InvenUI();
		pInvenUI->GetComponent<Transform>()->SetPosition(0.14f, 0.06f, -0.01f);
		pInvenUI->GetComponent<Transform>()->SetScale(1.619f * 0.17f, 1.f * 0.17f, 0.f); //1.619 : 1
		AddChildUI(pInvenUI);

		EquipUI* pEquipUI = new EquipUI();
		pEquipUI->GetComponent<Transform>()->SetPosition(0.41f, 0.06f, -0.01f);
		pEquipUI->GetComponent<Transform>()->SetScale(1.619f * 0.17f, 1.f * 0.17f, 0.f); //1.619 : 1
		AddChildUI(pEquipUI);

		SKillUI* pSKillUI = new SKillUI();
		pSKillUI->GetComponent<Transform>()->SetPosition(0.73f, 0.06f, -0.01f);
		pSKillUI->GetComponent<Transform>()->SetScale(1.619f * 0.17f, 1.f * 0.17f, 0.f); //1.619 : 1
		AddChildUI(pSKillUI);

		LevelUI* pLevelUI = new LevelUI();
		pLevelUI->GetComponent<Transform>()->SetPosition(-5.8f, -0.18f, -0.01f);
		pLevelUI->GetComponent<Transform>()->SetScale(6.844 * 0.35f, 1.f * 0.35f, 0.f); //6.844 : 1
		AddChildUI(pLevelUI);

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