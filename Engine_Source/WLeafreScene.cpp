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
#include "WLadder.h"
#include "WNPC.h"

namespace W
{
	LeafreScene::LeafreScene()
	{
		//ladder
		std::shared_ptr<Texture> pLadder7 =
			Resources::Load<Texture>(L"LadderTex7", L"..\\Resources\\Texture\\Object\\ladder\\7_.png");

		std::shared_ptr<Material> pLadderMater7 = std::make_shared<Material>();
		pLadderMater7->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pLadderMater7->SetTexture(pLadder7);
		Resources::Insert(L"LadderMater7", pLadderMater7);

		std::shared_ptr<Texture> pLadder7_ =
			Resources::Load<Texture>(L"LadderTex7_", L"..\\Resources\\Texture\\Object\\ladder\\7.png");

		std::shared_ptr<Material> pLadderMater7_ = std::make_shared<Material>();
		pLadderMater7_->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pLadderMater7_->SetTexture(pLadder7_);
		Resources::Insert(L"LadderMater7_", pLadderMater7_);


		//npc
		std::shared_ptr<Texture> pNPCTex =
			Resources::Load<Texture>(L"NPCTex0", L"..\\Resources\\Texture\\Object\\NPC\\npc0.png");

		std::shared_ptr<Material> pNPCMater = std::make_shared<Material>();
		pNPCMater->SetShader(Resources::Find<Shader>(L"ObjectShader"));
		pNPCMater->SetTexture(pNPCTex);
		Resources::Insert(L"NPC0", pNPCMater);

	}
	LeafreScene::~LeafreScene()
	{

	}
	void LeafreScene::Initialize()
	{
		CreateBackground();
		setobject();
		
		//NPC* pNPC = new NPC();
		//AddGameObject(eLayerType::NPC, pNPC);
		//MeshRenderer* pNPCRenderer = pNPC->AddComponent<MeshRenderer>();
		//pNPCRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//pNPCRenderer->SetMaterial();
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
			pBackGround->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);
			//1.829 : 1
			pBackGround->GetComponent<Transform>()->SetScale(1.829f * 13.f, 1.f * 13.f, 1.f);
		}
	}
	void LeafreScene::setobject()
	{
		Ladder* pLadder0 = new Ladder();
		AddGameObject(eLayerType::Ladder, pLadder0);
		MeshRenderer* pLadderMeshRender0 =  pLadder0->AddComponent<MeshRenderer>();
		pLadderMeshRender0->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRender0->SetMaterial(Resources::Find<Material>(L"LadderMater7"));
		pLadder0->GetComponent<Transform>()->SetPosition(-4.f, -1.55f, -1.f);
		pLadder0->GetComponent<Transform>()->SetScale(1.f * 0.6f, 3.5f * 0.6f, 0.f);

		Ladder* pLadder1 = new Ladder();
		AddGameObject(eLayerType::Ladder, pLadder1);
		MeshRenderer* pLadderMeshRender1 = pLadder1->AddComponent<MeshRenderer>();
		pLadderMeshRender1->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		pLadderMeshRender1->SetMaterial(Resources::Find<Material>(L"LadderMater7_"));
		pLadder1->GetComponent<Transform>()->SetPosition(3.6f, -1.32f, -1.f);
		pLadder1->GetComponent<Transform>()->SetScale(1.f * 0.6f, 3.5f * 0.6f, 0.f);
	}
}