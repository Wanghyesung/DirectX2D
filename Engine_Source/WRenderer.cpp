#include "WRenderer.h"
//#include "WApplication.h"

//extern W::Application application;

namespace W::renderer
{
	//�ﰢ�� ���� ��
	Vertex vertexes[3] = {};

	//input layout (���� ����)
	ID3D11InputLayout* triangleLayout = nullptr;

	//���� ����
	ID3D11Buffer* triangleBuffer = nullptr;
	ID3D11Buffer* triangleIdxBuffer = nullptr;
	ID3D11Buffer* triangleConstantBuffer = nullptr;

	//���� blop
	ID3DBlob* errorBlob = nullptr;

	//���� ���̴� �ڵ� -> 2���ڵ�� ����
	ID3DBlob* triangleVSBlob = nullptr;

	//���� ���̴�
	ID3D11VertexShader* triangleVSShader = nullptr;

	//�ȼ� ���̴� �ڵ� -> 2�� �ڵ�
	ID3DBlob* trianglePSBlob = nullptr;

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
		//application.GetDevice().get()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);
		W::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);

		//�׸��� ���� ����
		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		//�ε��� ����
		D3D11_BUFFER_DESC triangleIdxDesc = {};
		triangleIdxDesc.ByteWidth = sizeof(UINT) * indexes.size(); //����Ʈ ũ��
		triangleIdxDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		triangleIdxDesc.Usage = D3D11_USAGE_DEFAULT;//cpu��� X
		triangleIdxDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA triangleIdxData = {};
		triangleIdxData.pSysMem = indexes.data();
		W::graphics::GetDevice()->CreateBuffer(&triangleIdxBuffer, &triangleIdxDesc, &triangleIdxData);

		//��� ����
		D3D11_BUFFER_DESC triangleCSDesc = {};
		triangleCSDesc.ByteWidth = sizeof(Vector4);//16����Ʈ��
		triangleCSDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		triangleCSDesc.Usage = D3D11_USAGE_DYNAMIC;
		triangleCSDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		W::graphics::GetDevice()->CreateBuffer(&triangleConstantBuffer, &triangleCSDesc, nullptr);

		//bind
		//Vector4 pos = Vector4(0.3f, 0.0f, 0.0f, 1.0f);
		//W::graphics::GetDevice()->SetConstantBuffer(triangleConstantBuffer, &pos, sizeof(Vector4));
		//W::graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleConstantBuffer);

	}

	void LoadShader()
	{
		//application.GetDevice().get()->CreateShader();
		W::graphics::GetDevice()->CreateShader();
	}

	

	void Initialize()
	{
		//�ﰢ�� ������ġ, ���� ���ϱ�
		//-1~ 1 ndc��ǥ��� �Է�
		vertexes[0].Pos = Vector3(0.0f, 0.5f, 0.0f);
		vertexes[0].Color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		
		vertexes[1].Pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[1].Color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		
		vertexes[2].Pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[2].Color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		//�簢��, ������, ��
		//������
		//vertexes[0].Pos = Vector3(0.f, 0.9f, 0.f);
		//vertexes[0].Color = Vector4(1.0f, 0.f, 0.f, 1.f);
		//
		//vertexes[1].Pos = Vector3(0.6f, 0.6f, 0.f);
		//vertexes[1].Color = Vector4(0.f, 1.f, 0.f, 1.f);
		//
		//vertexes[2].Pos = Vector3(-0.6f, 0.6f, 0.f);
		//vertexes[2].Color = Vector4(1.f, 0.f, 0.f, 1.f);
		//
		//vertexes[3].Pos = Vector3(0.f, 0.3f, 0.f);
		//vertexes[3].Color = Vector4(1.0f, 0.f, 0.f, 1.f);
		//
		//vertexes[4].Pos = Vector3(-0.6f, 0.6f, 0.f);
		//vertexes[4].Color = Vector4(1.f, 0.f, 0.f, 1.f);
		//
		//vertexes[5].Pos = Vector3(0.6f, 0.6f, 0.f);
		//vertexes[5].Color = Vector4(0.f, 1.f, 0.f, 1.f);
		//
		////�簢��
		//vertexes[6].Pos = Vector3(-0.9f, 0.0f, 0.f);
		//vertexes[6].Color = Vector4(1.0f, 0.f, 0.f, 1.f);
		//
		//vertexes[7].Pos = Vector3(-0.3f, 0.f, 0.f);
		//vertexes[7].Color = Vector4(0.f, 1.f, 0.f, 1.f);
		//
		//vertexes[8].Pos = Vector3(-0.3f, -0.6f, 0.f);
		//vertexes[8].Color = Vector4(1.f, 0.f, 0.f, 1.f);
		//
		//vertexes[9].Pos = Vector3(-0.3f, -0.6f, 0.f);
		//vertexes[9].Color = Vector4(1.0f, 0.f, 0.f, 1.f);
		//
		//vertexes[10].Pos = Vector3(-0.9f, -0.6f, 0.f);
		//vertexes[10].Color = Vector4(0.f, 1.f, 0.f, 1.f);
		//
		//vertexes[11].Pos = Vector3(-0.9f, -0.f, 0.f);
		//vertexes[11].Color = Vector4(1.f, 0.f, 0.f, 1.f);

		SetupState();
		LoadBuffer();
		LoadShader();

		//InitializeCircle();
	}

	//void InitializeCircle()
	//{
	//	//��
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