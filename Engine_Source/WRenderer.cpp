#include "WRenderer.h"

namespace W::renderer
{
	//삼각형 버퍼 수
	Vertex vertexes[12] = {};

	//input layout (정점 정보)
	ID3D11InputLayout* triangleLayout = nullptr;

	//정점 버퍼
	ID3D11Buffer* triangleBuffer = nullptr;

	//에러 blop
	ID3DBlob* errorBlob = nullptr;

	//정점 셰이더 코드 -> 2진코드로 받음
	ID3DBlob* triangleVSBlob = nullptr;

	//정점 셰이더
	ID3D11VertexShader* triangleVSShader = nullptr;

	//픽셀 셰이더 코드 -> 2진 코드
	ID3DBlob* trianglePSBlob = nullptr;

	ID3D11PixelShader* trianglePSShader = nullptr;



	//임시 원 버퍼
	Vertex Circlevertexes[360] = {};

	//input layout (정점 정보)
	ID3D11InputLayout* lineLayout = nullptr;

	//정점 버퍼
	ID3D11Buffer* lineBuffer = nullptr;

	//정점 셰이더 코드 -> 2진코드로 받음
	ID3DBlob* lineVSBlob = nullptr;

	//정점 셰이더
	ID3D11VertexShader* lineVSShader = nullptr;

	//픽셀 셰이더 코드 -> 2진 코드
	ID3DBlob* linePSBlob = nullptr;

	ID3D11PixelShader* linePSShader = nullptr;

	void SetupState()
	{

	}


	void LoadBuffer()
	{
		D3D11_BUFFER_DESC triangleDesc = {};
		//버퍼를 읽고 쓰는 방법을 식별합니다.(CPU에서나 GPU에서 읽기 쓰기가 가능한지?)
		//GPU(읽기 전용)와 CPU(쓰기 전용)에서 모두 액세스할 수 있는 리소스입니다. 
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		//전체 바이트 수
		triangleDesc.ByteWidth = sizeof(Vertex) * 12;
		//버퍼가 파이프라인에 바인딩되는 방법을 식별합니다.
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		//CPU 액세스가 필요한경우 아니면 0
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		//내 점점 버퍼
		triangleData.pSysMem = vertexes;
		//single
		W::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);
	}

	void LoadShader()
	{
		W::graphics::GetDevice()->CreateShader();
	}

	void LoadBufferCircle()
	{
		D3D11_BUFFER_DESC lineDesc = {};
		lineDesc.Usage = D3D11_USAGE_DYNAMIC;
		lineDesc.ByteWidth = sizeof(Vertex) * 360;
		lineDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		lineDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA lineData = {};
		lineData.pSysMem = Circlevertexes;

		W::graphics::GetDevice()->CreateBuffer(&lineBuffer, &lineDesc, &lineData);
	}

	void LoadShaderCircle()
	{
		W::graphics::GetDevice()->CreateCircleShader();
	}

	void Initialize()
	{
		//삼각형 정점위치, 색깔 정하기
		//-1~ 1 ndc좌표계로 입력
		//vertexes[0].Pos = Vector3(0.0f, 0.5f, 0.0f);
		//vertexes[0].Color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		//
		//vertexes[1].Pos = Vector3(0.5f, -0.5f, 0.0f);
		//vertexes[1].Color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		//
		//vertexes[2].Pos = Vector3(-0.5f, -0.5f, 0.0f);
		//vertexes[2].Color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		//사각형, 마름모, 원
		//마름모
		vertexes[0].Pos = Vector3(0.f, 0.9f, 0.f);
		vertexes[0].Color = Vector4(1.0f, 0.f, 0.f, 1.f);
		
		vertexes[1].Pos = Vector3(0.6f, 0.6f, 0.f);
		vertexes[1].Color = Vector4(0.f, 1.f, 0.f, 1.f);
		
		vertexes[2].Pos = Vector3(-0.6f, 0.6f, 0.f);
		vertexes[2].Color = Vector4(1.f, 0.f, 0.f, 1.f);
		
		vertexes[3].Pos = Vector3(0.f, 0.3f, 0.f);
		vertexes[3].Color = Vector4(1.0f, 0.f, 0.f, 1.f);
		
		vertexes[4].Pos = Vector3(-0.6f, 0.6f, 0.f);
		vertexes[4].Color = Vector4(1.f, 0.f, 0.f, 1.f);
		
		vertexes[5].Pos = Vector3(0.6f, 0.6f, 0.f);
		vertexes[5].Color = Vector4(0.f, 1.f, 0.f, 1.f);

		//사각형
		vertexes[6].Pos = Vector3(-0.9f, 0.0f, 0.f);
		vertexes[6].Color = Vector4(1.0f, 0.f, 0.f, 1.f);

		vertexes[7].Pos = Vector3(-0.3f, 0.f, 0.f);
		vertexes[7].Color = Vector4(0.f, 1.f, 0.f, 1.f);

		vertexes[8].Pos = Vector3(-0.3f, -0.6f, 0.f);
		vertexes[8].Color = Vector4(1.f, 0.f, 0.f, 1.f);

		vertexes[9].Pos = Vector3(-0.3f, -0.6f, 0.f);
		vertexes[9].Color = Vector4(1.0f, 0.f, 0.f, 1.f);
		
		vertexes[10].Pos = Vector3(-0.9f, -0.6f, 0.f);
		vertexes[10].Color = Vector4(0.f, 1.f, 0.f, 1.f);
		
		vertexes[11].Pos = Vector3(-0.9f, -0.f, 0.f);
		vertexes[11].Color = Vector4(1.f, 0.f, 0.f, 1.f);

		SetupState();
		LoadBuffer();
		LoadShader();

		InitializeCircle();
	}

	void InitializeCircle()
	{
		//원
		float de = 0.f;
		//cosf(radian);
		//sinf(radian);
		for (UINT i = 0; i < 360; ++i)
		{
			float ra = (3.14159265f * de) / 180.f;
			float x = cosf(ra)/2.f;
			float y = sinf(ra)/2.f;

			Circlevertexes[i].Pos = Vector3(0.5f + x, -0.3f + y, 0.f);
			Circlevertexes[i].Color = Vector4(0.f, 1.f, 0.f, 1.f);

			de += 1.f;
		}

		LoadBufferCircle();
		LoadShaderCircle();
	}


}