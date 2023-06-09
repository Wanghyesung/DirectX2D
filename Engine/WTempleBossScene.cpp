#include "WTempleBossScene.h"
#include "WResources.h"
#include "WShader.h"
#include "WGameObject.h"
#include "WMesh.h"
#include "WMaterial.h"
#include "WMeshRenderer.h"
#include "WTransform.h"
#include "WInput.h"
#include "WSceneManger.h"
#include "WCamera.h"
#include "WCameraScript.h"
#include "WNPC.h"
namespace W
{
	TempleBossScene::TempleBossScene()
	{

	}
	TempleBossScene::~TempleBossScene()
	{

	}
	void TempleBossScene::Initialize()
	{
		CreateBackground();

		NPC* pNPC = new NPC();
		AddGameObject(eLayerType::NPC, pNPC);
		MeshRenderer* pMeshRender = pNPC->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"NPCMater5"));
		pNPC->GetComponent<Transform>()->SetPosition(-7.f, -2.f, -1.f);
		pNPC->GetComponent<Transform>()->SetScale(0.547f * 1.2, 1.f * 1.2f, 0.f);
		pNPC->GetComponent<Transform>()->SetRotation(0.f, 0.f, 0.f);

		GameObject* pCamera = new GameObject();
		AddGameObject(eLayerType::Player, pCamera);
		pCamera->GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, -10.f));
		Camera* pCameraComp = pCamera->AddComponent<Camera>();
		pCamera->AddComponent<CameraScript>();
	}
	void TempleBossScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SceneManger::LoadScene(L"Move1");
		}
	}
	void TempleBossScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TempleBossScene::Render()
	{
		Scene::Render();
	}
	void TempleBossScene::OnEnter()
	{
	}
	void TempleBossScene::OnExit()
	{
	}
	void TempleBossScene::CreateBackground()
	{
		GameObject* pBackGround = new GameObject();
		AddGameObject(eLayerType::Background, pBackGround);
		MeshRenderer* pMeshRender = pBackGround->AddComponent<MeshRenderer>();
		pMeshRender->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pMeshRender->SetMaterial(Resources::Find<Material>(L"TempleBossMater"));
		pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
		//2 : 1
		pBackGround->GetComponent<Transform>()->SetScale(2.f * 8.f, 1.f * 8.f, 1.f);
	}
}