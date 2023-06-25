#include "WRenderer.h"
//#include "WApplication.h"

//extern W::Application application;
#include "WResources.h"
#include "WTexture.h"
#include "WMaterial.h"

namespace renderer
{
	using namespace W;
	using namespace W::graphics;

	//삼각형 버퍼 수
	Vertex vertexes[4] = {};

	//input layout (정점 정보)
	//ID3D11InputLayout* triangleLayout = nullptr;

	//W::Mesh* mesh = nullptr;//mesh class로 대체

	//정점 버퍼
	//ID3D11Buffer* triangleBuffer = nullptr;
	//ID3D11Buffer* triangleIdxBuffer = nullptr;
	W::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::END] = {};

	//에러 blop
	//ID3DBlob* errorBlob = nullptr;

	//정점 셰이더 코드 -> 2진코드로 받음
	//ID3DBlob* triangleVSBlob = nullptr;

	//정점 셰이더
	//ID3D11VertexShader* triangleVSShader = nullptr;

	//픽셀 셰이더 코드 -> 2진 코드
	//ID3DBlob* trianglePSBlob = nullptr;
	//W::Shader* shader = nullptr;//shader class로 대체
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_cpSamplerState[(UINT)eSamplerType::End] = {};
	//ID3D11PixelShader* trianglePSShader = nullptr;



	void SetupState()
	{
		//Iinput layout 정점 구조 정보를 넘겨줘야한다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};
		
		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		std::shared_ptr<Shader> pShader = W::Resources::Find<Shader>(L"TriangleShader");

		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3,
			pShader->GetVSCode(),
			pShader->GetInputLayoutAddressOf());
		
		pShader = W::Resources::Find<Shader>(L"SpriteShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3,
			pShader->GetVSCode(),
			pShader->GetInputLayoutAddressOf());


		pShader = W::Resources::Find<Shader>(L"BackgroundShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3,
			pShader->GetVSCode(),
			pShader->GetInputLayoutAddressOf());

		pShader = W::Resources::Find<Shader>(L"GroundShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3,
			pShader->GetVSCode(),
			pShader->GetInputLayoutAddressOf());

		//smapler state 어떻게 그릴지 옵션
		D3D11_SAMPLER_DESC desc = {};
		desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSampler(&desc, m_cpSamplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, m_cpSamplerState[(UINT)eSamplerType::Point].GetAddressOf());

		desc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSampler(&desc, m_cpSamplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, m_cpSamplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
	}


	void LoadBuffer()
	{
		

		std::shared_ptr<Mesh> pMesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", pMesh);

		pMesh->CreateVertexBuffer(vertexes, 4);

		//그리는 순서 지정 (사각형)
		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		pMesh->CreateIndexBuffer(indexes.data(), indexes.size());
	
		//constant buffer
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));
		

	}

	void LoadShader()
	{
		//application.GetDevice().get()->CreateShader();
		//W::graphics::GetDevice()->CreateShader();

		std::shared_ptr<Shader> pShader = std::make_shared<Shader>();
		pShader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		pShader->Create(eShaderStage::PS, L"TrianglePs.hlsl", "main");
		W::Resources::Insert(L"TriangleShader", pShader);

		std::shared_ptr<Shader> pSpriteShader = std::make_shared<Shader>();
		pSpriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		pSpriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		W::Resources::Insert(L"SpriteShader", pSpriteShader);

		std::shared_ptr<Shader> pBackShader = std::make_shared<Shader>();
		pBackShader->Create(eShaderStage::VS, L"BackgroundVS.hlsl", "main");
		pBackShader->Create(eShaderStage::PS, L"BackgroundPS.hlsl", "main");
		W::Resources::Insert(L"BackgroundShader", pBackShader);

		std::shared_ptr<Shader> pGroundShader = std::make_shared<Shader>();
		pGroundShader->Create(eShaderStage::VS, L"BackgroundVS.hlsl", "main");
		pGroundShader->Create(eShaderStage::PS, L"BackgroundPS.hlsl", "main");
		W::Resources::Insert(L"GroundShader", pGroundShader);

		//background
		{
			std::shared_ptr<Texture> pTex =
				Resources::Load<Texture>(L"LeafreTex", L"..\\Resources\\Texture\\background\\Leafre_1.png");
			std::shared_ptr<Material> pBackgroundMater = std::make_shared<Material>();
			pBackgroundMater->SetShader(pBackShader);
			pBackgroundMater->SetTexture(pTex);
			Resources::Insert(L"LeafeMater", pBackgroundMater);

			//
			std::shared_ptr<Texture> pValleyTex =
				Resources::Load<Texture>(L"dragonValleyTex", L"..\\Resources\\Texture\\background\\dragonValley.png");
			std::shared_ptr<Material> pValleyMater = std::make_shared<Material>();
			pValleyMater->SetShader(pBackShader);
			pValleyMater->SetTexture(pValleyTex);
			Resources::Insert(L"dragonValleyMater", pValleyMater);


			std::shared_ptr<Texture> pWoodCaveTex =
				Resources::Load<Texture>(L"WoodCaveTex", L"..\\Resources\\Texture\\background\\woodCave.png");
			std::shared_ptr<Material> pWoodMater = std::make_shared<Material>();
			pWoodMater->SetShader(pBackShader);
			pWoodMater->SetTexture(pWoodCaveTex);
			Resources::Insert(L"WoodCaveMater", pWoodMater);
		}

		//ground
		{
			std::shared_ptr<Texture> pTex =
				Resources::Load<Texture>(L"GroundTex", L"..\\Resources\\Texture\\Ground\\0.png");

			std::shared_ptr<Material> pGroundMater = std::make_shared<Material>();
			pGroundMater->SetShader(pGroundShader);
			pGroundMater->SetTexture(pTex);

			Resources::Insert(L"GroundMater", pGroundMater);
		}
		
		//두 오브젝트 둘다 똑같은 메테리얼로 셋팅
		{
			std::shared_ptr<Texture> pTex =
				Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");

			std::shared_ptr<Material> pSpriteMaterial = std::make_shared<Material>();
			pSpriteMaterial->SetShader(pSpriteShader);
			pSpriteMaterial->SetTexture(pTex);
			Resources::Insert(L"SpriteMaterial", pSpriteMaterial);
		}

		{
			std::shared_ptr<Texture> pTex =
				Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");

			std::shared_ptr<Material> pSpriteMaterial = std::make_shared<Material>();
			pSpriteMaterial->SetShader(pSpriteShader);
			pSpriteMaterial->SetTexture(pTex);
			Resources::Insert(L"SpriteMaterial02", pSpriteMaterial);
		}
	}

	

	void Initialize()
	{
		//텍스쳐에서 색가져오기samlestate, uv좌표 때문에 정점정보도 uv좌표를 넣어서 바뀌어야함 vertex도한 uv추가, inputlayout도 추가 (3개로)
		vertexes[0].Pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].Color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].UV = Vector2(0.0f, 0.0f);

		vertexes[1].Pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].Color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].UV = Vector2(1.0f, 0.0f);

		vertexes[2].Pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].Color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].UV = Vector2(1.0f, 1.0f);

		vertexes[3].Pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].Color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].UV = Vector2(0.0f, 1.0f);

		LoadBuffer();
		LoadShader();
		SetupState();


		//이미지로드 후 픽셀셰이두 묶기
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");

		pTex->BindShader(eShaderStage::PS, 0);

		std::shared_ptr<Texture> pLink =
			Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");
		pLink->BindShader(eShaderStage::PS, 0);

		std::shared_ptr<Texture> pTexBack =
			Resources::Load<Texture>(L"LeafreTex", L"..\\Resources\\Texture\\background\\Leafre_1.png");
		pTexBack->BindShader(eShaderStage::PS, 0);

		//ground
		std::shared_ptr<Texture> pGround =
			Resources::Load<Texture>(L"GroundTex", L"..\\Resources\\Texture\\Ground\\0.png");
		pTexBack->BindShader(eShaderStage::PS, 0);

		std::shared_ptr<Texture> pValleyTex =
			Resources::Load<Texture>(L"dragonValleyTex", L"..\\Resources\\Texture\\background\\dragonValley.png");
		pValleyTex->BindShader(eShaderStage::PS, 0);

		std::shared_ptr<Texture> pWoodCaveTex =
			Resources::Load<Texture>(L"WoodCaveTex", L"..\\Resources\\Texture\\background\\woodCave.png");
		pWoodCaveTex->BindShader(eShaderStage::PS, 0);
		
	}

	void Release()
	{
		
		
		for (ConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}
	}


}