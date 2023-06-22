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

	//input layout (���� ����)
	//ID3D11InputLayout* triangleLayout = nullptr;

	//W::Mesh* mesh = nullptr;//mesh class�� ��ü

	//���� ����
	//ID3D11Buffer* triangleBuffer = nullptr;
	//ID3D11Buffer* triangleIdxBuffer = nullptr;
	W::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::END] = {};

	//���� blop
	//ID3DBlob* errorBlob = nullptr;

	//���� ���̴� �ڵ� -> 2���ڵ�� ����
	//ID3DBlob* triangleVSBlob = nullptr;

	//���� ���̴�
	//ID3D11VertexShader* triangleVSShader = nullptr;

	//�ȼ� ���̴� �ڵ� -> 2�� �ڵ�
	//ID3DBlob* trianglePSBlob = nullptr;
	//W::Shader* shader = nullptr;//shader class�� ��ü
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_cpSamplerState[(UINT)eSamplerType::End] = {};
	//ID3D11PixelShader* trianglePSShader = nullptr;



	void SetupState()
	{
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
		
		pShader = W::Resources::Find<Shader>(L"SpriteShader");
		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 3,
			pShader->GetVSCode(),
			pShader->GetInputLayoutAddressOf());

		//smapler state ��� �׸��� �ɼ�
		D3D11_SAMPLER_DESC desc = {};
		desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;//���� �״��
		GetDevice()->CreateSampler(&desc, m_cpSamplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS,0, m_cpSamplerState[(UINT)eSamplerType::Point].GetAddressOf());
		
		desc.Filter = D3D11_FILTER_ANISOTROPIC;//��Ƽ���ϸ����
		GetDevice()->CreateSampler(&desc, m_cpSamplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, m_cpSamplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
	}


	void LoadBuffer()
	{
		//D3D11_BUFFER_DESC triangleDesc = {};
		////���۸� �а� ���� ����� �ĺ��մϴ�.(CPU������ GPU���� �б� ���Ⱑ ��������?)
		////GPU(�б� ����)�� CPU(���� ����)���� ��� �׼����� �� �ִ� ���ҽ��Դϴ�. 
		//triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		////��ü ����Ʈ ��
		//triangleDesc.ByteWidth = sizeof(Vertex) * 3;
		////���۰� ���������ο� ���ε��Ǵ� ����� �ĺ��մϴ�.
		//triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		////CPU �׼����� �ʿ��Ѱ�� �ƴϸ� 0
		//triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		//
		//D3D11_SUBRESOURCE_DATA triangleData = {};
		////�� ���� ����
		//triangleData.pSysMem = vertexes;
		////single
		////application.GetDevice().get()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);
		//W::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);

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
		
		//Vector4 pos(0.2f, 0.0f, 1.f, 1.f);
		//constantBuffer->SetData(&pos);
		//constantBuffer->Bind(eShaderStage::VS);

		//�ε��� ����
		//D3D11_BUFFER_DESC triangleIdxDesc = {};
		//triangleIdxDesc.ByteWidth = sizeof(UINT) * indexes.size(); //����Ʈ ũ��
		//triangleIdxDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		//triangleIdxDesc.Usage = D3D11_USAGE_DEFAULT;//cpu��� X
		//triangleIdxDesc.CPUAccessFlags = 0;
		//
		//D3D11_SUBRESOURCE_DATA triangleIdxData = {};
		//triangleIdxData.pSysMem = indexes.data();
		//W::graphics::GetDevice()->CreateBuffer(&triangleIdxBuffer, &triangleIdxDesc, &triangleIdxData);

		//��� ����
		//D3D11_BUFFER_DESC triangleCSDesc = {};
		//triangleCSDesc.ByteWidth = sizeof(Vector4);//16����Ʈ�� ������ ����
		//triangleCSDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		//triangleCSDesc.Usage = D3D11_USAGE_DYNAMIC;//cpu�б�
		//triangleCSDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		//
		//W::graphics::GetDevice()->CreateBuffer(&triangleConstantBuffer, &triangleCSDesc, nullptr);

		//bind
		//Vector4 pos = Vector4(0.3f, 0.0f, 0.0f, 1.0f);
		//W::graphics::GetDevice()->SetConstantBuffer(triangleConstantBuffer, &pos, sizeof(Vector4));
		//W::graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleConstantBuffer);

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

		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");

		std::shared_ptr<Material> pSpriteMaterial = std::make_shared<Material>();
		pSpriteMaterial->SetShader(pSpriteShader);
		pSpriteMaterial->SetTexture(pTex);
		Resources::Insert(L"SpriteMaterial", pSpriteMaterial);
	}

	

	void Initialize()
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

		LoadBuffer();
		LoadShader();
		SetupState();


		//�̹����ε� �� �ȼ����̵� ����
		std::shared_ptr<Texture> pTex =
			Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
		
		pTex =
			Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\Link.png");

		pTex->BindShader(eShaderStage::PS, 0);
	}

	void Release()
	{
		//if (triangleLayout != nullptr)
		//	triangleLayout->Release();

		//����Ʈ ������ ���
		//if (triangleBuffer != nullptr)
		//	triangleBuffer->Release();
		//
		//if (triangleIdxBuffer != nullptr)
		//	triangleIdxBuffer->Release();

		//if (triangleConstantBuffer != nullptr)
		//	triangleConstantBuffer->Release();

		//if (errorBlob != nullptr)
		//	errorBlob->Release();
		//
		//if (triangleVSBlob != nullptr)
		//	triangleVSBlob->Release();
		//
		//if (triangleVSShader != nullptr)
		//	triangleVSShader->Release();
		//
		//if (trianglePSBlob != nullptr)
		//	trianglePSBlob->Release();

		//if (trianglePSShader != nullptr)
		//	trianglePSShader->Release();

		
		for (ConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}
	}


}