#include "WRenderer.h"

namespace W::renderer
{
	//�ﰢ�� ���� ��
	Vertex vertexes[3] = {};

	//���� ����
	ID3D11Buffer* triangleBuffer = nullptr;

	//���� blop
	ID3DBlob* errorBlob = nullptr;

	//���� ���̴� �ڵ� -> 2���ڵ�� ����
	ID3DBlob* triangleVSBlob = nullptr;

	//���� ���̴�
	ID3D11VertexShader* triangleVSShader = nullptr;

	//�ȼ� ���̴� �ڵ� -> 2�� �ڵ�
	ID3DBlob* trianglePosBlob = nullptr;

	ID3D11PixelShader* trianglePSShader = nullptr;


	void SetupState()
	{

	}


	void LoadBuffer()
	{
		D3D11_BUFFER_DESC triangleDesc = {};
		//���۸� �а� ���� ����� �ĺ��մϴ�.(CPU������ GPU���� �б� ���Ⱑ ��������?)
		//GPU(�б� ����)�� CPU(���� ����)���� ��� �׼����� �� �ִ� ���ҽ��Դϴ�. 
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		//��ü ����Ʈ ��
		triangleDesc.ByteWidth = sizeof(Vertex) * 3;
		//���۰� ���������ο� ���ε��Ǵ� ����� �ĺ��մϴ�.
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		//CPU �׼����� �ʿ��Ѱ�� �ƴϸ� 0
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		//�� ���� ����
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
		//�ﰢ�� ������ġ, ���� ���ϱ�
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