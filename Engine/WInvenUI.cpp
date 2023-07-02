#include "WInvenUI.h"
#include "WInterfaceUI.h"
namespace W
{
	InvenUI::InvenUI()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"InvenTex0", L"..\\Resources\\Texture\\UI\\Interface\\InvenBt_0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"InvenMater0", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	InvenUI::~InvenUI()
	{
	}
	void InvenUI::Initialize()
	{

	}
	void InvenUI::Update()
	{
		UI::Update();
	}
	void InvenUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void InvenUI::Render()
	{
		UI::Render();
	}
	void InvenUI::MouseOn()
	{

	}
	void InvenUI::MouseLbtnDown()
	{
		UI* pParentUI = GetParentUI();
		InterfaceUI* pInterfaceUI = dynamic_cast<InterfaceUI*>(pParentUI);

		if (pInterfaceUI != nullptr)
			pInterfaceUI->ActiveInventory();
	}
	void InvenUI::MouseLbtnUp()
	{

	}
	void InvenUI::MouseLbtnClicked()
	{

	}
}