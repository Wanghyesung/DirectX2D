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

	//�ﰢ�� ���� ��
	Vertex vertexes[4] = {};

	W::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::END] = {};

	
	
	//�ؽ��� �̹��� ������ albedo
	//��º��մܰ迡�� �����׽�Ʈ, �����׽�Ʈ ����
	//�����Ͷ����� (�ø� ��� : ��ü�� �޸�(�޽����� �ո��������� �޸���������) solidback �޸����� , front�� none(���� x), wireframeNone(mesh���̰�)
	// ��ī�̹ڽ� (ex::front �ո��� ���� ī�޶�Ͱ��� ���������� �޸��� ����)
	//���� ������Ʈ (���� ex: z���� ������������ ū�������� �յ��Ǻ�, ������ü ������) (less�� ������ �տ�, greater ū��, none X 
	// ����Ÿ���� �ȼ����� ���������� ���Ͽ� �ȼ����̴����� �����ɷ� ��(less) (���ٽǹ��� -> ����ȭ Ʋ?)
	//���� ������Ʈ (���� ����) default , alphablend(��������) 
	//bindpixle �� � �����Ͷ�����, ����, ���� �����̴��� ���� ����
	//���̴����� ���°� ������
	//om->���̻���,����
	//�ؽ��Ŀ��� ���÷� 
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_cpSamplerState[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_cpRasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_cpDepthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_cpBlendStates[(UINT)eBSType::End] = {};

	std::vector<W::Camera*> vecCameras = {};

	void SetupState()
	{
#pragma region InputLayout
		//Iinput layout ���� ���� ������ �Ѱ�����Ѵ�.
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
		
		pShader = W::Resources::Find<Shader>(L"GridShader");
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

		pShader = W::Resources::Find<Shader>(L"ObjectShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3,
			pShader->GetVSCode(),
			pShader->GetInputLayoutAddressOf());

		pShader = W::Resources::Find<Shader>(L"UIShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3,
			pShader->GetVSCode(),
			pShader->GetInputLayoutAddressOf());
#pragma endregion

#pragma region Sampler State
		//smapler state ��� �׸��� �ɼ�
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSampler(&samplerDesc, m_cpSamplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, m_cpSamplerState[(UINT)eSamplerType::Point].GetAddressOf());

		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSampler(&samplerDesc, m_cpSamplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, m_cpSamplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion

#pragma region Rasterizer State
		D3D11_RASTERIZER_DESC tRasterizerDesc = {};
		tRasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;//���������� ������ �ﰢ���� ä��ϴ�. ������ �������� �׷����� �ʽ��ϴ�.
		tRasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;//�޸�����
		GetDevice()->CreateRasterizeState(&tRasterizerDesc,
			m_cpRasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		tRasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;// ���������� ������ �ﰢ���� ä��ϴ�.������ �������� �׷����� �ʽ��ϴ�.
		tRasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;//�ո�����
		GetDevice()->CreateRasterizeState(&tRasterizerDesc,
			m_cpRasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		tRasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;//���������� ������ �ﰢ���� ä��ϴ�. ������ �������� �׷����� �ʽ��ϴ�.
		tRasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;//����X
		GetDevice()->CreateRasterizeState(&tRasterizerDesc,
			m_cpRasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		tRasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;//�������� �����ϴ� ���� �׸��ϴ�. ������ �������� �׷����� �ʽ��ϴ�.
		tRasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;//�޸�����
		GetDevice()->CreateRasterizeState(&tRasterizerDesc,
			m_cpRasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());	
#pragma endregion

#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC tDepthStencilDesc = {};

		//z���� �������� �Ⱥ��̰�
		tDepthStencilDesc.DepthEnable = true;
		tDepthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		tDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		tDepthStencilDesc.StencilEnable = false; //Ʋ

		GetDevice()->CreateDepthStencilState(&tDepthStencilDesc,
			m_cpDepthStencilStates[(UINT)eDSType::Less].GetAddressOf());
		
		//z���� ū ���� ���̰�
		tDepthStencilDesc.DepthEnable = true;
		tDepthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		tDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		tDepthStencilDesc.StencilEnable = false; //Ʋ

		GetDevice()->CreateDepthStencilState(&tDepthStencilDesc,
			m_cpDepthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		tDepthStencilDesc.DepthEnable = true;
		tDepthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		tDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;//���� ���ٽ� ���ۿ� ���� ���⸦ ���ϴ�.
		tDepthStencilDesc.StencilEnable = false; //Ʋ

		GetDevice()->CreateDepthStencilState(&tDepthStencilDesc,
			m_cpDepthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		tDepthStencilDesc.DepthEnable = false;
		tDepthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		tDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		tDepthStencilDesc.StencilEnable = false; //Ʋ

		GetDevice()->CreateDepthStencilState(&tDepthStencilDesc,
			m_cpDepthStencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion

#pragma region Blend State
		D3D11_BLEND_DESC tBlendDesc = {};

		//default
		m_cpBlendStates[(UINT)eBSType::Default] = nullptr;

		//alpha blend
		tBlendDesc.AlphaToCoverageEnable = false;
		tBlendDesc.IndependentBlendEnable = false;
		tBlendDesc.RenderTarget[0].BlendEnable = true;
		tBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		tBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		tBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		tBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		tBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		tBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		tBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&tBlendDesc,
			m_cpBlendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		//one one
		tBlendDesc.AlphaToCoverageEnable = false;
		tBlendDesc.IndependentBlendEnable = false;

		tBlendDesc.RenderTarget[0].BlendEnable = true;
		tBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		tBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		tBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		tBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&tBlendDesc,
			m_cpBlendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion
	}

	void LoadMesh()
	{
		//�ؽ��Ŀ��� ����������samlestate, uv��ǥ ������ ���������� uv��ǥ�� �־ �ٲ����� vertex���� uv�߰�, inputlayout�� �߰� (3����)
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
	}

	void LoadBuffer()
	{
		std::shared_ptr<Mesh> pMesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", pMesh);

		pMesh->CreateVertexBuffer(vertexes, 4);

		//�׸��� ���� ���� (�簢��)
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
		
		//grid buffer
		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

	}

	void LoadShader()
	{
		//application.GetDevice().get()->CreateShader();
		//W::graphics::GetDevice()->CreateShader();

		std::shared_ptr<Shader> pShader = std::make_shared<Shader>();
		pShader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		pShader->Create(eShaderStage::PS, L"TrianglePs.hlsl", "main");
		W::Resources::Insert(L"TriangleShader", pShader);

		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		Resources::Insert(L"GridShader", gridShader);

		std::shared_ptr<Shader> pSpriteShader = std::make_shared<Shader>();
		pSpriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		pSpriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		W::Resources::Insert(L"SpriteShader", pSpriteShader);

		std::shared_ptr<Shader> pBackShader = std::make_shared<Shader>();
		pBackShader->Create(eShaderStage::VS, L"BackgroundVS.hlsl", "main");
		pBackShader->Create(eShaderStage::PS, L"BackgroundPS.hlsl", "main");
		W::Resources::Insert(L"BackgroundShader", pBackShader);

		std::shared_ptr<Shader> pObjcetShader = std::make_shared<Shader>();
		pObjcetShader->Create(eShaderStage::VS, L"BackgroundVS.hlsl", "main");
		pObjcetShader->Create(eShaderStage::PS, L"ObjectPS.hlsl", "main");
		W::Resources::Insert(L"ObjectShader", pObjcetShader);

		std::shared_ptr<Shader> pUIShader = std::make_shared<Shader>();
		pUIShader->Create(eShaderStage::VS, L"UIVS.hlsl", "main");
		pUIShader->Create(eShaderStage::PS, L"UIPS.hlsl", "main");
		W::Resources::Insert(L"UIShader", pUIShader);

	}

	void LoadMaterial()
	{
#pragma region background
		{
			std::shared_ptr<Texture> pTex =
				Resources::Load<Texture>(L"LeafreTex", L"..\\Resources\\Texture\\background\\Leafre_2.png");
			std::shared_ptr<Material> pBackgroundMater = std::make_shared<Material>();
			pBackgroundMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
			pBackgroundMater->SetTexture(pTex);
			Resources::Insert(L"LeafeMater", pBackgroundMater);

			//
			std::shared_ptr<Texture> pValleyTex =
				Resources::Load<Texture>(L"dragonValleyTex", L"..\\Resources\\Texture\\background\\dragonValley.png");
			std::shared_ptr<Material> pValleyMater = std::make_shared<Material>();
			pValleyMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
			pValleyMater->SetTexture(pValleyTex);
			Resources::Insert(L"dragonValleyMater", pValleyMater);

			std::shared_ptr<Texture> pValleyTex2 =
				Resources::Load<Texture>(L"dragonValleyTex2", L"..\\Resources\\Texture\\background\\dragonValley_2.png");
			std::shared_ptr<Material> pValleyMater2 = std::make_shared<Material>();
			pValleyMater2->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
			pValleyMater2->SetTexture(pValleyTex2);
			Resources::Insert(L"dragonValleyMater2", pValleyMater2);


			std::shared_ptr<Texture> pWoodCaveTex =
				Resources::Load<Texture>(L"WoodCaveTex", L"..\\Resources\\Texture\\background\\woodCave.png");
			std::shared_ptr<Material> pWoodMater = std::make_shared<Material>();
			pWoodMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
			pWoodMater->SetTexture(pWoodCaveTex);
			Resources::Insert(L"WoodCaveMater", pWoodMater);

			std::shared_ptr<Texture> pTempleTex =
				Resources::Load<Texture>(L"TempleTex", L"..\\Resources\\Texture\\background\\Temple.png");
			std::shared_ptr<Material> pTempleMater = std::make_shared<Material>();
			pTempleMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
			pTempleMater->SetTexture(pTempleTex);
			Resources::Insert(L"TempleMater", pTempleMater);

			std::shared_ptr<Texture> pTempleTex2 =
				Resources::Load<Texture>(L"TempleTex2", L"..\\Resources\\Texture\\background\\temple_2.png");
			pTempleTex2->BindShader(eShaderStage::PS, 0);
			std::shared_ptr<Material> pTempleMater2 = std::make_shared<Material>();
			pTempleMater2->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
			pTempleMater2->SetTexture(pTempleTex2);
			Resources::Insert(L"TempleMater2", pTempleMater2);

			std::shared_ptr<Texture> pTempleBossTex =
				Resources::Load<Texture>(L"TempleBossTex", L"..\\Resources\\Texture\\background\\temple_boss.png");
			pTempleBossTex->BindShader(eShaderStage::PS, 0);
			std::shared_ptr<Material> pTempleBossMater = std::make_shared<Material>();
			pTempleBossMater->SetShader(Resources::Find<Shader>(L"BackgroundShader"));
			pTempleBossMater->SetTexture(pTempleBossTex);
			Resources::Insert(L"TempleBossMater", pTempleBossMater);
		}
#pragma endregion

		//�� ������Ʈ �Ѵ� �Ȱ��� ���׸���� ����
		
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");

		std::shared_ptr<Material> pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"SpriteShader"));
		pMater->SetTexture(pTex);
		Resources::Insert(L"SpriteMaterial", pMater);
		

		
		pTex = Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");

		pMater = std::make_shared<Material>();
		pMater->SetShader(Resources::Find<Shader>(L"SpriteShader"));
		pMater->SetTexture(pTex);
		pMater->SetRenderinMode(eRenderingMode::Transparent);
		Resources::Insert(L"SpriteMaterial02", pMater);
		
		std::shared_ptr<Shader> girdShader = Resources::Find<Shader>(L"GridShader");
		pMater = std::make_shared<Material>();
		pMater->SetShader(girdShader);
		Resources::Insert(L"GridMaterial", pMater);
	}
	

	void Initialize()
	{
		LoadMesh();
		LoadBuffer();
		LoadShader();
		SetupState();
		LoadMaterial();
		
	}
	void Render()
	{
		for (Camera* cam : vecCameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}
		//��ü �׸��� ���� �����
		vecCameras.clear();
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