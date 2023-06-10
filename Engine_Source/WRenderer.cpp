#include "WRenderer.h"
//#include "WApplication.h"

//extern W::Application application;

namespace renderer
{
	//삼각형 버퍼 수
	Vertex vertexes[4] = {};

	//input layout (정점 정보)
	//ID3D11InputLayout* triangleLayout = nullptr;

	W::Mesh* mesh = nullptr;//mesh class로 대체

	//정점 버퍼
	//ID3D11Buffer* triangleBuffer = nullptr;
	//ID3D11Buffer* triangleIdxBuffer = nullptr;
	W::graphics::ConstantBuffer* constantBuffer = nullptr;

	//에러 blop
	//ID3DBlob* errorBlob = nullptr;

	//정점 셰이더 코드 -> 2진코드로 받음
	//ID3DBlob* triangleVSBlob = nullptr;

	//정점 셰이더
	//ID3D11VertexShader* triangleVSShader = nullptr;

	//픽셀 셰이더 코드 -> 2진 코드
	//ID3DBlob* trianglePSBlob = nullptr;
	W::Shader* shader = nullptr;//shader class로 대체

	//ID3D11PixelShader* trianglePSShader = nullptr;



	void SetupState()
	{
		//Iinput layout 정점 구조 정보를 넘겨줘야한다.
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
			shader->GetVSCode(),
			shader->GetInputLayoutAddressOf());
	}


	void LoadBuffer()
	{
		//D3D11_BUFFER_DESC triangleDesc = {};
		////버퍼를 읽고 쓰는 방법을 식별합니다.(CPU에서나 GPU에서 읽기 쓰기가 가능한지?)
		////GPU(읽기 전용)와 CPU(쓰기 전용)에서 모두 액세스할 수 있는 리소스입니다. 
		//triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		////전체 바이트 수
		//triangleDesc.ByteWidth = sizeof(Vertex) * 3;
		////버퍼가 파이프라인에 바인딩되는 방법을 식별합니다.
		//triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		////CPU 액세스가 필요한경우 아니면 0
		//triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		//
		//D3D11_SUBRESOURCE_DATA triangleData = {};
		////내 점점 버퍼
		//triangleData.pSysMem = vertexes;
		////single
		////application.GetDevice().get()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);
		//W::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);
		mesh = new W::Mesh();
		mesh->CreateVertexBuffer(vertexes, 4);

		//그리는 순서 지정 (사각형)
		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());


		//constant buffer
		//constantBuffer = new W::graphics::ConstantBuffer(eCBType::Transform);
		//constantBuffer->Create(sizeof(Vector4));
		
		//Vector4 pos(0.2f, 0.0f, 0.0f, 1.0f);
		//constantBuffer->SetData(&pos);
		//constantBuffer->Bind(eShaderStage::VS);

		//인덱스 버퍼
		//D3D11_BUFFER_DESC triangleIdxDesc = {};
		//triangleIdxDesc.ByteWidth = sizeof(UINT) * indexes.size(); //바이트 크기
		//triangleIdxDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		//triangleIdxDesc.Usage = D3D11_USAGE_DEFAULT;//cpu사용 X
		//triangleIdxDesc.CPUAccessFlags = 0;
		//
		//D3D11_SUBRESOURCE_DATA triangleIdxData = {};
		//triangleIdxData.pSysMem = indexes.data();
		//W::graphics::GetDevice()->CreateBuffer(&triangleIdxBuffer, &triangleIdxDesc, &triangleIdxData);

		//상수 버퍼
		//D3D11_BUFFER_DESC triangleCSDesc = {};
		//triangleCSDesc.ByteWidth = sizeof(Vector4);//16바이트만 데이터 셋팅
		//triangleCSDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		//triangleCSDesc.Usage = D3D11_USAGE_DYNAMIC;//cpu읽기
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

		shader = new W::Shader();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePs.hlsl", "main");
	}

	

	void Initialize()
	{
		//삼각형 정점위치, 색깔 정하기
		//-1~ 1 ndc좌표계로 입력
		vertexes[0].Pos = Vector3(-0.5f, 0.5f, 0.f);
		vertexes[0].Color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		
		vertexes[1].Pos = Vector3(0.5f, 0.5f, 0.f);
		vertexes[1].Color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		
		vertexes[2].Pos = Vector3(0.5f, -0.5f, 0.f);
		vertexes[2].Color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		
		vertexes[3].Pos = Vector3(-0.5f, -0.5f, 0.f);
		vertexes[3].Color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		LoadBuffer();
		LoadShader();
		SetupState();

		//InitializeCircle();
	}

	void Release()
	{
		//if (triangleLayout != nullptr)
		//	triangleLayout->Release();

		//스마트 포인터 사용
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

		delete mesh;
		delete shader;
		delete constantBuffer;
	}

	//void InitializeCircle()
	//{
	//	//원
	//	float de = 0.f;
	//	//cosf(radian);
	//	//sinf(radian);
	//	for (UINT i = 0; i < 360; ++i)
	//	{
	//		float ra = (3.14159265f * de) / 180.f;
	//		float x = cosf(ra)/2.f;
	//		float y = sinf(ra)/2.f;
	//
	//		Circlevertexes[i].Pos = Vector3(0.5f + x, -0.3f + y, 0.f);
	//		Circlevertexes[i].Color = Vector4(0.f, 1.f, 0.f, 1.f);
	//
	//		de += 1.f;
	//	}
	//
	//}


}