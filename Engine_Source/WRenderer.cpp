#include "WRenderer.h"
//#include "WApplication.h"

//extern W::Application application;

namespace renderer
{
	//�ﰢ�� ���� ��
	Vertex vertexes[4] = {};

	//input layout (���� ����)
	//ID3D11InputLayout* triangleLayout = nullptr;

	W::Mesh* mesh = nullptr;//mesh class�� ��ü

	//���� ����
	//ID3D11Buffer* triangleBuffer = nullptr;
	//ID3D11Buffer* triangleIdxBuffer = nullptr;
	W::graphics::ConstantBuffer* constantBuffer = nullptr;

	//���� blop
	//ID3DBlob* errorBlob = nullptr;

	//���� ���̴� �ڵ� -> 2���ڵ�� ����
	//ID3DBlob* triangleVSBlob = nullptr;

	//���� ���̴�
	//ID3D11VertexShader* triangleVSShader = nullptr;

	//�ȼ� ���̴� �ڵ� -> 2�� �ڵ�
	//ID3DBlob* trianglePSBlob = nullptr;
	W::Shader* shader = nullptr;//shader class�� ��ü

	//ID3D11PixelShader* trianglePSShader = nullptr;



	void SetupState()
	{
		//Iinput layout ���� ���� ������ �Ѱ�����Ѵ�.
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
		mesh = new W::Mesh();
		mesh->CreateVertexBuffer(vertexes, 4);

		//�׸��� ���� ���� (�簢��)
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

		shader = new W::Shader();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePs.hlsl", "main");
	}

	

	void Initialize()
	{
		//�ﰢ�� ������ġ, ���� ���ϱ�
		//-1~ 1 ndc��ǥ��� �Է�
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

		delete mesh;
		delete shader;
		delete constantBuffer;
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