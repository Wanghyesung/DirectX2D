#include "WLeafreScene.h"
#include "WShader.h"
#include "WMeshRenderer.h"
#include "WMesh.h"
#include "WResources.h"
#include "WGameObject.h"
#include "WTransform.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WGround.h"
#include "WInput.h"
#include "WSceneManger.h"

namespace W
{
	LeafreScene::LeafreScene()
	{
		

	}
	LeafreScene::~LeafreScene()
	{

	}
	void LeafreScene::Initialize()
	{
		CreateBackground();

		
		//Ground* pGround = new Ground();
		//AddGameObject(eLayerType::Ground, pGround);
		//MeshRenderer* pMeshRender = pGround->AddComponent<MeshRenderer>();
		//pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//pMeshRender->SetMaterial(Resources::Find<Material>(L"GroundMater"));
		//pGround->GetComponent<Transform>()->SetPosition(0.f, -4.5f, 0.f);
		////1.471 : 1
		//pGround->GetComponent<Transform>()->SetScale(3.f,3.f,1.f);

		//{
		//	GameObject* pPlayer = new GameObject();
		//	AddGameObject(eLayerType::Player, pPlayer);
		//	MeshRenderer* pMeshRender = pPlayer->AddComponent<MeshRenderer>();
		//	pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	pMeshRender->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		//	pPlayer->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.f));
		//}

		//camera
		GameObject* pCamera = new GameObject();
		AddGameObject(eLayerType::Player, pCamera);
		pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
		Camera* pCameraComp = pCamera->AddComponent<Camera>();
		pCamera->AddComponent<CameraScript>();
	}
	void LeafreScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SceneManger::LoadScene(L"Valley");
		}
	}
	void LeafreScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void LeafreScene::Render()
	{
		Scene::Render();
	}
	void LeafreScene::OnEnter()
	{
	}
	void LeafreScene::OnExit()
	{
	}
	void LeafreScene::CreateBackground()
	{
		//¹ÙÅÁ
		{
			GameObject* pBackGround = new GameObject();
			AddGameObject(eLayerType::Background, pBackGround);
			MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
			pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			pMeshRender->SetMaterial(Resources::Find<Material>(L"LeafeMater"));
			pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 1.f);
			//1.829 : 1
			pBackGround->GetComponent<Transform>()->SetScale(1.829f * 13.f, 1.f * 13.f, 1.f);
		}
	}
}