#include "WInventory.h"
#include "WAlixirUI.h"
#include "WTransform.h"
#include "WAlixirUI.h"
#include "WSceneManger.h"
#include "WInput.h"
#include "WHorntailItem.h"

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
		//-0.68 1.2      -0.26 0.77 ����
		// 0.42 0.42 
		//0.58 -0.90

		//AlixirUI* pAlixir = new AlixirUI();
		//pAlixir->SetName(L"Alxir");
		//Transform* pAlixirTransform = pAlixir->GetComponent<Transform>();
		////pAlixirTransform->SetPosition(-0.f, 0.f, -0.01f);
		//pAlixirTransform->SetScale(0.1f * 2.5f, 0.1f * 2.5f, 0.f); //0.518 : 1
		//AddItem(pAlixir,pAlixir->GetName());
		//
		//HorntailItem* pHorntailItem = new HorntailItem();
		//pHorntailItem->SetName(L"pHorntailItem");
		//Transform* pHorntailItemTr = pHorntailItem->GetComponent<Transform>();
		//pHorntailItemTr->SetScale(0.1f * 2.5f, 0.1f * 2.5f, 0.f); //0.518 : 1
		//AddItem(pHorntailItem, pHorntailItem->GetName());
		
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

		if (pItem != nullptr)//�������� ����
			return;
		
		//���ο� ������
		if (SetItemPosition(_pItem))
		{
			AddChildUI(_pItem,false);
			m_mapItems.insert(make_pair(_strName, _pItem));
			_pItem->SetParentUIType(eParentUI::Inventory);
		}
	}


	bool Inventory::SetItemPosition(ItemUI* _pItem)
	{
		//3.66 0.9 //3.2 0.45
		//�κ��丮 ��ġ
		Transform* pTransform = GetComponent<Transform>();
		Vector3 vPosition = pTransform->GetPosition();
		
		Transform* PItemTranform = _pItem->GetComponent<Transform>();
		Vector3 vItemPosition = PItemTranform->GetPosition();

		//���� ����
		Vector2 vComaprePos = {};

		//1 : 1������
		Vector2 vStartPosition = Vector2(m_vUIStartPosition.x + vPosition.x, m_vUIStartPosition.y + vPosition.y);
		for (UINT y = 0; y < 6; ++y)
		{
			vComaprePos.y = vStartPosition.y + y * m_vUIDiffPosition.y;
			for (UINT x = 0; x < 4; ++x)
			{
				vComaprePos.x = vStartPosition.x + x * m_vUIDiffPosition.x;
				std::map<std::wstring, ItemUI*>::iterator iter = m_mapItems.begin();
				
				//ó�� ���� �������̶��
				if (iter == m_mapItems.end())
				{
					PItemTranform->SetPosition(vComaprePos.x, vComaprePos.y, vItemPosition.z);
					_pItem->SetItemIndex(x, y);
					return true;
				}

				ItemUI* pITem = FindItemOnPosition(x, y);
				//��ĭ
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
		//�� ��ġ�� �������� �ִٸ� , �������� â �ۿ��� �θ�
		
		//�κ��丮 ��ġ
		Transform* pTransform = GetComponent<Transform>();
		Vector3 vPosition = pTransform->GetPosition();

		//���� ������ Ʈ������
		Transform* pItemTransform = _pItem->GetComponent<Transform>();
		Vector3 vItemPosition = pItemTransform->GetPosition();

		Vector2 vStartPosition = Vector2(m_vUIStartPosition.x + vPosition.x, m_vUIStartPosition.y + vPosition.y);
		Vector2 vComaprePos = {};

		Vector3 vUIEndPosition = vPosition + m_vUIEndPosition;
		Vector3 vUIStartPosition = vPosition + m_vUIStartPosition;
		//�κ��丮 ���� ���̸�
		if (_vSetPosition.x >= vUIEndPosition.x + m_vUIDiffPosition.x || _vSetPosition.x <= vUIStartPosition.x - m_vUIDiffPosition.x ||
			_vSetPosition.y <= vUIEndPosition.y + m_vUIDiffPosition.y || _vSetPosition.y >= vUIStartPosition.y - m_vUIDiffPosition.y)
		{
			return false;
		}

		//���콺 �� ��ġ���� ���� ������ ã��
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

				//������ �а����� ���� ������
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
			//�̹� �������� �ִ� ��ġ�� �ڸ� �ٲٱ�
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

	ItemUI* Inventory::FindItemOnPosition(UINT _iX, UINT _iY)
	{
		std::map<std::wstring, ItemUI*>::iterator iter = m_mapItems.begin();

		for (iter; iter != m_mapItems.end(); ++iter)
		{
			ItemUI* pITem = iter->second;
			UINT ITEM_X = pITem->GetItemindexX();
			UINT ITEM_Y = pITem->GetItemIndexY();

			//��ĭ
			if (ITEM_X == _iX && ITEM_Y == _iY)
			{
				return iter->second;
			}
		}

		return nullptr;
	}
}