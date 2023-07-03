#include "WInventory.h"
#include "WAlixirUI.h"
#include "WTransform.h"
#include "WAlixirUI.h"
#include "WSceneManger.h"
#include "WInput.h"
namespace W
{
	Inventory::Inventory():
		m_bRenderOn(false),
		m_mapItems{},
		m_vUIStartPosition(Vector2::One),
		m_vUIEndPosition(Vector2::One),
		m_vUIDiffPosition(Vector2::One)
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
		Transform* pTransform = GetComponent<Transform>();
		pTransform->SetPosition(0.f, 0.f, -0.25f);
		pTransform->SetScale(0.518f * 3.8f, 1.f * 3.8f, 0.f); //0.518 : 1

		m_vUIStartPosition = Vector2(-0.68f, 1.2f);
		m_vUIEndPosition = Vector2(0.58f, -9.f);
		m_vUIDiffPosition = Vector2(-0.26f, 0.77f);
		//-0.68 1.2      -0.26 0.77 차이
		// 0.42 0.42 
		//0.58 -0.90

		AlixirUI* pAlixir = new AlixirUI();
		Transform* pAlixirTransform = pAlixir->GetComponent<Transform>();
		pAlixirTransform->SetPosition(-0.68f, 1.2f, -0.03f);
		pAlixirTransform->SetScale(0.1f * 2.5f, 0.1f * 2.5f, 0.f); //0.518 : 1
		AddItem(pAlixir,pAlixir->GetName());
		//AddChildUI(pAlixir);
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

		UI::MouseOn();
	}
	void Inventory::MouseLbtnDown()
	{
		m_bTargetOn = true;

		m_vDragStartPos = Input::GetMousePos();

		UI::MouseLbtnDown();
	}
	void Inventory::MouseLbtnUp()
	{
		m_bTargetOn = false;

		m_vDragStartPos = Input::GetMousePos();

		UI::MouseLbtnUp();
	}
	void Inventory::MouseLbtnClicked()
	{
		UI::MouseLbtnClicked();
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
		
		//새로운 아이템
		if (setitemposition(_pItem))
		{
			AddChildUI(_pItem);
			m_mapItems.insert(make_pair(_strName, _pItem));
		}
	}


	bool Inventory::setitemposition(ItemUI* _pItem)
	{
		//3.66 0.9 //3.2 0.45
		//인벤토리 위치
		Transform* pTransform = GetComponent<Transform>();
		Vector3 vPosition = pTransform->GetPosition();
		
		Transform* PItemTranform = _pItem->GetComponent<Transform>();
		Vector3 vItemPosition = PItemTranform->GetPosition();

		//1 : 1시작점
		Vector2 vStartPosition = Vector2(m_vUIStartPosition.x + vPosition.x, m_vUIStartPosition.y + vPosition.y);
		for (UINT y = 0; y < 6; ++y)
		{
			vStartPosition.y += y * m_vUIDiffPosition.y;
			for (UINT x = 0; x < 4; ++x)
			{
				vStartPosition.x += x * m_vUIDiffPosition.x;
				std::map<std::wstring, ItemUI*>::iterator iter = m_mapItems.begin();
				
				//처음 들어온 아이템이라면
				if (iter == m_mapItems.end())
				{
					PItemTranform->SetPosition(vStartPosition.x, vStartPosition.y, vItemPosition.z);
					_pItem->SetItemIndex(x, y);
					return true;
				}

				for (iter; iter != m_mapItems.end(); ++iter)
				{
					ItemUI* pITem = iter->second;
					UINT ITEM_X = pITem->GetItemindexX();
					UINT ITEM_Y = pITem->GetItemIndexY();

					//빈칸
					if (ITEM_X != x && ITEM_Y != y)
					{
						PItemTranform->SetPosition(vStartPosition.x,vStartPosition.y,vItemPosition.z);
						_pItem->SetItemIndex(x, y);
						return true;
					}
				}
			}
		}

		return false;
	}
}