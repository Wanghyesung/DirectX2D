#include "WScene.h"
#include "WGameObject.h"

#include "WInput.h"
#include "WTime.h"
#include "WPlayer.h"
#include "WChildPlayer.h"

namespace W
{
	using namespace math;
	Scene::Scene():
		m_fCurTime(0.f),
		m_CreateTime(0.f)
	{
	}
	Scene::~Scene()
	{
	}
	void Scene::Initialize()
	{
		Player* m_pGameObj = new Player;
		
		m_pGameObj->Initialize();
		m_vecGameObject.push_back(m_pGameObj);
		SetPlayer(m_pGameObj);
	}
	void Scene::Update()
	{
		m_fCurTime += Time::DeltaTime();
		m_CreateTime += Time::DeltaTime();
		if (Input::GetKeyDown(eKeyCode::SPACE) && m_CreateTime >= 1.f)
		{
			m_CreateTime = 0.f;
			Vector3 vPos =m_pPlayer->GetPos();
			vPos.z -= 0.1f;
			m_pPlayer->SetPos(vPos);
			ChildPlayer* pChild = new ChildPlayer;
			pChild->SetPos(m_pPlayer->GetPos());
			pChild->Initialize();
			pChild->m_pOwner = m_pPlayer;
			m_pPlayer->AddChild(pChild);
			pChild->move();
			m_vecGameObject.push_back(pChild);
		}

		if (m_fCurTime >= 2.f)
		{
			float x = (rand() % 100) / 100.f;
			float y = (rand() % 100) / 100.f;
			float min = (rand() % 100) / 100.f;
			x -= min;
			y -= min;
			GameObject* m_pGameObj = new GameObject;
			m_pGameObj->SetPos(math::Vector3(x,y,1.f));
			m_pGameObj->Initialize();
			m_vecGameObject.push_back(m_pGameObj);
			m_fCurTime = 0.f;
		}
		for (GameObject* gameObj : m_vecGameObject)
		{
			gameObj->Update();
		}

		Check();
	}
	void Scene::LateUpdate()
	{
	}
	void Scene::Render()
	{
		for (GameObject* gameObj : m_vecGameObject)
		{
			gameObj->Render();
		}
	}
	bool Scene::Check()
	{
		//math::Vector3 vPos = m_pPlayer->GetPos();
		//float fScale = 0.2f * m_pPlayer->GetPos().z;
		////vPos.x *= fScale;
		////vPos.y *= fScale;
		//
		//for (GameObject* gameObj : m_vecGameObject)
		//{
		//	if (gameObj == m_pPlayer)
		//		continue;
		//
		//	math::Vector3 vOtherPos = gameObj->GetPos();
		//	float fOtherScale = 0.2f;
		//
		//	if (abs(vPos.x - vOtherPos.x) <= abs((fScale + fOtherScale) / 2.f) &&
		//		abs(vPos.y - vOtherPos.y) <= abs((fScale + fOtherScale) / 2.f))
		//	{
		//		DeleteObject(gameObj);
		//		m_pPlayer->UpScale();
		//		return true;
		//	}
		//}
		//return false;
		math::Vector3 vPos = m_pPlayer->GetPos();
		float fScale = 0.1f * vPos.z;

		for (GameObject* gameObj : m_vecGameObject)
		{
			if (gameObj == m_pPlayer)
				continue;

			if (dynamic_cast<ChildPlayer*>(gameObj))
				continue;

			//float fOtherScale = 0.1f;
			math::Vector3 vOtherPos = gameObj->GetPos();
			Vector2 vMin = Vector2(vOtherPos.x - vPos.x, vOtherPos.y - vPos.y);
			float fLen = vMin.Length();//±Ê¿Ã
			
			if (fLen <= fScale)
			{
				DeleteObject(gameObj);
				m_pPlayer->UpScale();
				return true;
			}
		}
		return false;
	}
	void Scene::DeleteObject(GameObject* _pObj)
	{
		std::vector<GameObject*>::iterator iter = m_vecGameObject.begin();

		for (iter; iter != m_vecGameObject.end(); ++iter)
		{
			if (*iter == _pObj)
			{
				m_vecGameObject.erase(iter);
				delete _pObj;
				return;
			}
		}
	}
}