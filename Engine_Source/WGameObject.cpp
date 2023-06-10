#include <random>
#include "WGameObject.h"
#include "WRenderer.h"
#include "WGraphicDevice_Dx11.h"

#include "WInput.h"
#include "WTime.h"


namespace W
{
	GameObject::GameObject() :
		m_eState(eState::Active),
		m_vPos(0.f, 0.f, 1.f),
		m_pConstantBuffer(nullptr),
		m_pMesh(nullptr),
		m_pShader(nullptr)
	{
		m_pMesh = new Mesh();
		m_pShader = new Shader();
		m_pConstantBuffer = new graphics::ConstantBuffer(eCBType::Transform);
	}
	GameObject::~GameObject()
	{
		//여기 릭 잡기
		delete m_pConstantBuffer;
		delete m_pMesh;
		delete m_pShader;
	}
	void GameObject::Initialize()
	{
		//m_pMesh->CreateVertexBuffer();
		//vertexes[0].
		//m_pMesh->CreateVertexBuffer(); 정점버퍼는 냅두고 정점, 픽셀 셰이더 로드하고 정점버퍼 들어올 때 바뀌게 register 해두기 색이나 위치 바뀌게

		SetBuffer();
		SetShader("main2");

		SetupState();

		ConstantBuffer();

	}
	void GameObject::Update()
	{
		//if (!m_bIsPlayer)
		//	return;
		//
		//if (Input::GetKey(eKeyCode::RIGHT))
		//	m_vPos.x += 1.f * Time::DeltaTime();
		//if (Input::GetKey(eKeyCode::LEFT))
		//	m_vPos.x -= 1.f * Time::DeltaTime();
		//if (Input::GetKey(eKeyCode::UP))
		//	m_vPos.y += 1.f * Time::DeltaTime();
		//if (Input::GetKey(eKeyCode::DOWN))
		//	m_vPos.y -= 1.f * Time::DeltaTime();
		//
		//
		//m_pConstantBuffer->SetData(&m_vPos);
		//m_pConstantBuffer->Bind(eShaderStage::VS);

	}

	void GameObject::LateUpdate()
	{

	}

	void GameObject::Render()
	{
		m_pMesh->BindBuffer();
		m_pShader->Binds();
		graphics::GetDevice()->DrawIndexed(m_pMesh->GetIndexCount(), 0, 0);
	}


	void GameObject::SetupState()
	{
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

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


		W::graphics::GetDevice()->CreateInputLayout(arrLayout, 2,
			m_pShader->GetVSCode(),
			m_pShader->GetInputLayoutAddressOf());
	}
	void GameObject::SetBuffer()
	{
		float color = (rand() % 100) / 100.f;
		m_fColor = color;
		float x = m_vPos.x;
		float y = m_vPos.y;
		
		Vector3 pos = GetPos();
		renderer::Vertex vertexes[362];
		std::vector<UINT> indexes = {};

		//순서를 가운데 먼저 찍고 사계방향으로
		vertexes[0].Pos = Vector3(x, y, 0.f);
		vertexes[0].Color = Vector4(color, 0.0f, 0.0f, 1.0f);
	
		for (int de = 0; de < 361; ++de)
		{
			float radian = (de / 180.f) * 3.141592f;
			float cx = cosf(radian)/2.f;
			float sy = sinf(radian)/2.f;
			cx /= 10.f;
			sy /= 10.f;
			vertexes[de+1].Pos = Vector3(x + cx,y + sy,0.f);
			vertexes[de+1].Color = Vector4(color, 0.0f, 0.0f, 1.0f);
		}
		
		for (int i = 361; i >= 1 ; --i)
		{
			indexes.push_back(0);
			indexes.push_back(i);
			indexes.push_back(i-1);
		}

		
		m_pMesh->CreateVertexBuffer(vertexes, 362);
		m_pMesh->CreateIndexBuffer(indexes.data(), indexes.size());

		//renderer::Vertex vertexes[4];
		//vertexes[0].Pos = Vector3(x - 0.1f, y + 0.1f, 0.f);
		//vertexes[0].Color = Vector4(color, 0.0f, 0.0f, 1.0f);
		//
		//vertexes[1].Pos = Vector3(x + 0.1f, y + 0.1f, 0.f);
		//vertexes[1].Color = Vector4(0.f, color, 0.f, 1.0f);
		//
		//vertexes[2].Pos = Vector3(x + 0.1f, y - 0.1f, 0.f);
		//vertexes[2].Color = Vector4(0.f, 0.0f, color, 1.0f);
		//
		//vertexes[3].Pos = Vector3(x - 0.1f, y - 0.1f, 0.f);
		//vertexes[3].Color = Vector4(color, 0.0f, 0.0f, 1.0f);
		//
		//
		//std::vector<UINT> indexes = {};
		//indexes.push_back(0);
		//indexes.push_back(1);
		//indexes.push_back(2);
		//
		//indexes.push_back(0);
		//indexes.push_back(2);
		//indexes.push_back(3);
		//
		//m_pMesh->CreateVertexBuffer(vertexes, 4);
		//m_pMesh->CreateIndexBuffer(indexes.data(), indexes.size());
	}
	void GameObject::SetShader(std::string _strFunName)
	{
		m_pShader->Create(eShaderStage::VS, L"TriangleVS.hlsl", _strFunName);
		m_pShader->Create(eShaderStage::PS, L"TrianglePs.hlsl", "main");
	}
	void GameObject::ConstantBuffer()
	{
		m_pConstantBuffer->Create(sizeof(Vector4));
		m_pConstantBuffer = new graphics::ConstantBuffer(eCBType::Transform);
	}
}