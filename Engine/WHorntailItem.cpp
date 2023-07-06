#include "WHorntailItem.h"

namespace W
{
	HorntailItem::HorntailItem()
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"horntailItemTex", L"..\\Resources\\Texture\\UI\\ItemUI\\horntailItem.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"horntailItemMater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	HorntailItem::~HorntailItem()
	{

	}
	void HorntailItem::Initialize()
	{

	}
	void HorntailItem::Update()
	{
		ItemUI::Update();
	}
	void HorntailItem::LateUpdate()
	{
		ItemUI::LateUpdate();
	}
	void HorntailItem::Render()
	{
		ItemUI::Render();
	}
	void HorntailItem::MouseOn()
	{
		ItemUI::MouseOn();
	}
	void HorntailItem::MouseLbtnDown()
	{
		ItemUI::MouseLbtnDown();
	}
	void HorntailItem::MouseLbtnUp()
	{
		ItemUI::MouseLbtnUp();
	}
	void HorntailItem::MouseLbtnClicked()
	{
		ItemUI::MouseLbtnClicked();
	}
}