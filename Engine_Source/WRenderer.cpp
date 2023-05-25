#include "WRenderer.h"

namespace W::renderer
{
	//삼각형 버퍼 수
	Vertex vertexes[3] = {};

	//정점 버퍼
	ID3D11Buffer* triangleBuffer = nullptr;

	//에러 blop
	ID3DBlob* errorBlob = nullptr;

	//정점 셰이더 코드 -> 2진코드로 받음
	ID3DBlob* triangleVSBlob = nullptr;

	//정점 셰이더
	ID3D11VertexShader* triangleVSShader = nullptr;

	//픽셀 셰이더 코드 -> 2진 코드
	ID3DBlob* trianglePosBlob = nullptr;

	ID3D11PixelShader* trianglePSShader = nullptr;


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
		triangleDesc.ByteWidth = sizeof(Vertex) * 3;
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


	void Initialize()
	{
		//삼각형 정점위치, 색깔 정하기
		vertexes[0].Pos = Vector3(0.0f, 0.5f, 1.0f);
		vertexes[0].Color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[1].Pos = Vector3(0.5f, -0.5f, 1.0f);
		vertexes[1].Color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[2].Pos = Vector3(-0.5f, -0.5f, 1.0f);
		vertexes[2].Color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		SetupState();
		LoadBuffer();
		LoadShader();
	}


}