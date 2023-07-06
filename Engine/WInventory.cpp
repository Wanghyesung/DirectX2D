#include "WInventory.h"
#include "WAlixirUI.h"
#include "WTransform.h"
#include "WAlixirUI.h"
#include "WSceneManger.h"
#include "WInput.h"
#include "WHorntailItem.h"
#include "WInterfaceUI.h"

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
		m_vUIDiffPosition = Vector2(0.42f, -0.42f);
		//-0.68 1.2      -0.26 0.77 차이
		// 0.42 0.42 
		//0.58 -0.90

		AlixirUI* pAlixir = new AlixirUI();
		pAlixir->SetName(L"Alxir");
		Transform* pAlixirTransform = pAlixir->GetComponent<Transform>();
		//pAlixirTransform->SetPosition(-0.f, 0.f, -0.01f);
		pAlixirTransform->SetScale(0.1f * 2.5f, 0.1f * 2.5f, 0.f); //0.518 : 1
		AddItem(pAlixir,pAlixir->GetName());
		
		HorntailItem* pHorntailItem = new HorntailItem();
		pHorntailItem->SetName(L"pHorntailItem");
		Transform* pHorntailItemTr = pHorntailItem->GetComponent<Transform>();
		pHorntailItemTr->SetScale(0.1f * 2.5f, 0.1f * 2.5f, 0.f); //0.518 : 1
		AddItem(pHorntailItem, pHorntailItem->GetName());
		
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

			//m_vUIStartPosition += vDiff;
			//m_vUIEndPosition += vDiff;

			MoveToParent(vDiff);

			m_vDragStartPos = Input::GetMousePos();
		}

	}
	void Inventory::MouseLbtnDown()
	{
		m_bTargetOn = true;

		m_vDragStartPos = Input::GetMousePos();

	}
	void Inventory::MouseLbtnUp()
	{
		m_bTargetOn = false;

		m_vUIEndPosition = Input::GetMousePos();
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

		//새로운 아이템
		if (SetItemPosition(_pItem))
		{
			AddChildUI(_pItem, false);
			m_mapItems.insert(make_pair(_strName, _pItem));
			_pItem->SetParentUIType(eParentUI::Inventory);
		}
		
	}

	bool Inventory::SetItemPosition(ItemUI* _pItem)
	{
		//3.66 0.9 //3.2 0.45
		//인벤토리 위치
		Transform* pTransform = GetComponent<Transform>();
		Vector3 vPosition = pTransform->GetPosition();
		
		Transform* PItemTranform = _pItem->GetComponent<Transform>();
		Vector3 vItemPosition = PItemTranform->GetPosition();

		//비교할 벡터
		Vector2 vComaprePos = {};

		//1 : 1시작점
		Vector2 vStartPosition = Vector2(m_vUIStartPosition.x + vPosition.x, m_vUIStartPosition.y + vPosition.y);
		for (UINT y = 0; y < 6; ++y)
		{
			vComaprePos.y = vStartPosition.y + y * m_vUIDiffPosition.y;
			for (UINT x = 0; x < 4; ++x)
			{
				vComaprePos.x = vStartPosition.x + x * m_vUIDiffPosition.x;
				std::map<std::wstring, ItemUI*>::iterator iter = m_mapItems.begin();
				
				//처음 들어온 아이템이라면
				if (iter == m_mapItems.end())
				{
					PItemTranform->SetPosition(vComaprePos.x, vComaprePos.y, vItemPosition.z);
					_pItem->SetItemIndex(x, y);
					return true;
				}

				ItemUI* pITem = FindItemOnPosition(x, y);
				//빈칸
				if (pITem == nullptr)
				{
					PItemTranform->SetPosition(vComaprePos.x, vComaprePos.y, vItemPosition.z);
					_pItem->SetItemIndex(x, y);
					return true;
				}
			}
		}		

		return false;
	}

	bool Inventory::ChangeItemPosition(ItemUI* _pItem, Vector2 _vSetPosition)
	{	
		//인벤토리 위치
		Transform* pTransform = GetComponent<Transform>();
		Vector3 vPosition = pTransform->GetPosition();

		//들어올 아이템 트렌스폼
		Transform* pItemTransform = _pItem->GetComponent<Transform>();
		Vector3 vItemPosition = pItemTransform->GetPosition();

		Vector2 vStartPosition = Vector2(m_vUIStartPosition.x + vPosition.x, m_vUIStartPosition.y + vPosition.y);
		Vector2 vComaprePos = {};

		//마우스 둔 우치에서 가장 가까운곳 찾기
		Vector2 vMinValue = Vector2(2000.f, 2000.f);
		float fMinLen = 2000.f;
		UINT iMinX = 0;
		UINT iMinY = 0;

		for (UINT y = 0; y < 6; ++y)
		{
			vComaprePos.y = vStartPosition.y + y * m_vUIDiffPosition.y;
			for (UINT x = 0; x < 4; ++x)
			{

				vComaprePos.x = vStartPosition.x + x * m_vUIDiffPosition.x;

				Vector2 vDiff = _vSetPosition - vComaprePos;
				float fLen = abs(vDiff.Length());

				//아이템 둔곳에서 가장 가까운곳
				if (fLen <= fMinLen)
				{
					fMinLen = fLen;
					vMinValue = vComaprePos;
					iMinX = x;
					iMinY = y;
				}
			}
		}

		ItemUI* pFindItem = FindItemOnPosition(iMinX, iMinY);

		if (pFindItem != nullptr)
		{
			//이미 아이템이 있는 위치면 자리 바꾸기
			Transform* pFItemTr = pFindItem->GetComponent<Transform>();
			Vector3 vFItemPos = pFItemTr->GetPosition();

			Vector3 vItemStartPos = _pItem->GetStartPosition();
			int x = _pItem->GetItemindexX();
			int y =_pItem->GetItemIndexY();

			pFindItem->SetItemIndex(x, y);
			pFItemTr->SetPosition(vItemStartPos);

			pItemTransform->SetPosition(vMinValue.x, vMinValue.y, vItemPosition.z);
			_pItem->SetItemIndex(iMinX, iMinY);
		}
		else
		{
			pItemTransform->SetPosition(vMinValue.x, vMinValue.y, vItemPosition.z);
			_pItem->SetItemIndex(iMinX, iMinY);
		}

		return true;
	}

	void Inventory::CheckItemPosition(ItemUI* _pItem)
	{
		ItemUI* pUI = FindItem(_pItem->GetName());

		if (pUI != nullptr)
			return;

		//새로운 아이템
		AddChildUI(_pItem, false);
		m_mapItems.insert(make_pair(_pItem->GetName(), _pItem));
		//현재 아이템 위치
		_pItem->SetParentUIType(eParentUI::Inventory);

	}

	ItemUI* Inventory::FindItemOnPosition(UINT _iX, UINT _iY)
	{
		std::map<std::wstring, ItemUI*>::iterator iter = m_mapItems.begin();

		for (iter; iter != m_mapItems.end(); ++iter)
		{
			ItemUI* pITem = iter->second;
			UINT ITEM_X = pITem->GetItemindexX();
			UINT ITEM_Y = pITem->GetItemIndexY();

			//빈칸
			if (ITEM_X == _iX && ITEM_Y == _iY)
			{
				return iter->second;
			}
		}

		return nullptr;
	}
	ItemUI* Inventory::GetItemSamePos(ItemUI* _pItem)
	{
		std::map<std::wstring, ItemUI*>::iterator iter = m_mapItems.begin();

		for (iter; iter != m_mapItems.end(); ++iter)
		{
			if (iter->second == _pItem)
				continue;

			int x = iter->second->GetItemindexX();
			int y = iter->second->GetItemindexX();

			int _x = _pItem->GetItemindexX();
			int _y = _pItem->GetItemindexX();

			if (x == _x && y == _y)
			{
				return iter->second;
			}
		}
		return nullptr;
	}


}