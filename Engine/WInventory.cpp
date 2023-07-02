#include "WInventory.h"
#include "WAlixirUI.h"
#include "WTransform.h"
namespace W
{
	Inventory::Inventory():
		m_bRenderOn(false),
		m_mapItems{}
	{
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"Inven0Tex", L"..\\Resources\\Texture\\UI\\InvenUI\\Inven0.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"UIShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"Inven0Mater", pMater);

		MeshRenderer* pMeshRender = AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(pMater);
	}
	Inventory::~Inventory()
	{

	}
	void Inventory::Initialize()
	{
		AlixirUI* pAlixir = new AlixirUI();

	}
	void Inventory::Update()
	{
		if (!m_bRenderOn)
			return;

		UI::Update();
	}
	void Inventory::LateUpdate()
	{
		if (!m_bRenderOn)
			return;

		UI::LateUpdate();
	}
	void Inventory::Render()
	{
		if (!m_bRenderOn)
			return;

		UI::Render();
	}
	void Inventory::MouseOn()
	{

	}
	void Inventory::MouseLbtnDown()
	{

	}
	void Inventory::MouseLbtnUp()
	{

	}
	void Inventory::MouseLbtnClicked()
	{
	}

	ItemUI* Inventory::FindItem(std::wstring _strName)
	{
		std::map<std::wstring, ItemUI*>::iterator iter =
			m_mapItems.find(_strName);

		if (iter == m_mapItems.end())
			return nullptr;

		return iter->second;
	}
	void Inventory::AddItem(ItemUI* _pItem , std::wstring _strName)
	{
		//-3.6 -0.8
		ItemUI* pItem = FindItem(_strName);

		if (pItem != nullptr)//아이템이 있음
			return;
		
		m_mapItems.insert(make_pair(_strName, _pItem));
	}

	void Inventory::setitemposition(ItemUI* _pItem)
	{
		Transform* pTransform = _pItem->GetComponent<Transform>();
		Vector3 vPosition = pTransform->GetPosition();
		Vector3 vScale = pTransform->GetScale();
		


	}
}