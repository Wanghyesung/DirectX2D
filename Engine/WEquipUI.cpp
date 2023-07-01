#include "WEquipUI.h"

namespace W
{
	EquipUI::EquipUI()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"EquipBtTex0", L"..\\Resources\\Texture\\UI\\Interface\\EquipBt_0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"EquipBtMater0", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	EquipUI::~EquipUI()
	{

	}
	void EquipUI::Initialize()
	{
	}
	void EquipUI::Update()
	{
		UI::Update();
	}
	void EquipUI::LateUpdate()
	{
		UI::LateUpdate();
	}
	void EquipUI::Render()
	{
		UI::Render();
	}
	void EquipUI::MouseOn()
	{
	}
	void EquipUI::MouseLbtnDown()
	{
	}
	void EquipUI::MouseLbtnUp()
	{
	}
	void EquipUI::MouseLbtnClicked()
	{
	}
}