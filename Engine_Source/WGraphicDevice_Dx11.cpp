#include "WGraphicDevice_Dx11.h"
#include "WApplication.h"
#include "WRenderer.h"

extern W::Application application;

namespace W::graphics
{
	//ram���� gpu�׷���ī���� �ּҸ� ����Ű�� ������ �÷���
	//�⺻������ ���� ��������
	//getaddres�� �� ������ �ּҸ� ������ �� ����
	//���߹��۸� ���� �Լ��� �� �����Ϳ� ���� �Ҵ��ϰ� ����
	//desc �ɼǱ�� 

	//����ü�� �ȿ� ���۸� ����Ÿ�Ͽ� ����
	//��������
	//�Ӹ�-> �̸� �ؽ��ĵ��� ũ�⺰�� �����δ¹� ->�׶��׋� ������ �� �ʿ䰡����
	
	//������ �ϴ�, ȸ������ �ϱ� -> �������̳� ����̸� ��ü�� �Ǽ��� ���������� ���� �� �Ⱥ��� �� ����

	GraphicDevice_Dx11::GraphicDevice_Dx11()
	{
		//Device, Context ����
		HWND hwnd = application.GetHwnd();
		//�̰� �ؾ��� ����� ���� ���� �� ���� �������� �ٸ��ɷ�
		UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		//d3d ����̹� ��ɺ� 
		D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL)0;
		//int a = 10;
		//int* b = &a;
		//int** c = &b;
		//**c;
		//ID3D11Device* pDevice = nullptr;
		//ID3D11DeviceContext* pContext = nullptr;
		//ID3D11DeviceContext** ppContext = &pContext;

		//null����, ����̹����� Ÿ��, ����̹��� HARDWARE�� ��� null,
		//��Ÿ�� ����, featruelevel�� �� D3D11_SDK_VERSION���, 
		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
			deviceFlag, nullptr, 0, D3D11_SDK_VERSION,
			m_cpDevice.GetAddressOf(), &featureLevel,
			m_cpContext.GetAddressOf());


		//����ü�� �ɼ� (���۹� ǥ�� ��� ����)
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		//���� ���
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();

		if (!CreateSwapChain(&swapChainDesc, hwnd))
			return;

		// ����ü�ο� �ִ� ����Ÿ�� ��������
		if (FAILED(m_cpSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D)
			, (void**)m_cpRenderTarget.GetAddressOf())))
			return;

		//����Ÿ�ٺ� ����
		m_cpDevice->CreateRenderTargetView((ID3D11Resource*)m_cpRenderTarget.Get()
			, nullptr, m_cpRenderTargetView.GetAddressOf());

		//2d �ؽ��� �ɼ�(���̹���)
		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		//��� ���� ��������  ���� ���ٽ� ������� ���ε��մϴ�
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		//24��Ʈ
		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		//�ؽ�ó�� �а� ���� ����� �ĺ��ϴ� ���Դϴ�.
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		//���� �ػ�
		depthStencilDesc.Width = application.GetWidth();
		depthStencilDesc.Height = application.GetHeight();
		//�ؽ�ó �迭�� �ؽ�ó ���Դϴ�
		depthStencilDesc.ArraySize = 1;
	
		//�ȼ��� ���� ���� ���Դϴ�.
		//�̹��� ǰ�� �����Դϴ�. ǰ���� �������� ������ �������ϴ� 0 ~ 1
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;

		depthStencilDesc.MiscFlags = 0;
		//�ؽ�ó�� �ִ� Mipmap ���� ���Դϴ�
		depthStencilDesc.MipLevels = 0;
		

		D3D11_SUBRESOURCE_DATA data;
		if (!CreateTexture(&depthStencilDesc, &data))
			return;

		//ndc��ǥ -> window ��ǥ�� ��ȯ(����Ʈ��ȯ)(�»�� ���ϴ� ũ��, 
		//����Ʈ�� ��� �����ؾ� ��ũ���� �ٲ� ���� �ٲ�
		RECT winRect = {};
		GetClientRect(hwnd, &winRect);

		m_tViewPort =
		{
			0.f, 0.f,
			(float)(winRect.right - winRect.left),
			(float)(winRect.bottom - winRect.top),
			0.f,1.f
		};

		BindViewPort(&m_tViewPort);
		// ���ٽ� ���۸� ���-���� �ܰ迡 ���ε��մϴ�.
		m_cpContext->OMSetRenderTargets(1, m_cpRenderTargetView.GetAddressOf(), m_cpDepthStencilView.Get());

	}
	GraphicDevice_Dx11::~GraphicDevice_Dx11()
	{

	}
	bool GraphicDevice_Dx11::CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* _desc, HWND _hwnd)
	{
		DXGI_SWAP_CHAIN_DESC dxGiDesc = {};

		//���â window�ڵ鰪
		dxGiDesc.OutputWindow = _hwnd;
		//���â �������
		dxGiDesc.Windowed = true;

		dxGiDesc.BufferCount = _desc->BufferCount;
		dxGiDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;

		//ǥ�� �Ǵ� ���ҽ��� ��� ������ ������� ����մϴ�.
		dxGiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		dxGiDesc.BufferDesc.Width = _desc->BufferDesc.Width;
		dxGiDesc.BufferDesc.Height = _desc->BufferDesc.Height;
		//888 rgb 32��Ʈ
		dxGiDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		dxGiDesc.BufferDesc.RefreshRate.Numerator = 240;//�ִ� ������
		dxGiDesc.BufferDesc.RefreshRate.Denominator = 1; //�ּ� ������
		//������ ������� �ػ󵵿� �°� �̹����� �þ�� ��� (Ȯ����� ����) 
		dxGiDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		dxGiDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		//�ȼ��� ���� ���� ��, �̹��� ǰ�� ���� 0~1
		dxGiDesc.SampleDesc.Count = 1;
		dxGiDesc.SampleDesc.Quality = 0;

		//adapter = �����
		//GIdevice = ����Ÿ��
		//factory = ��üȭ��ó��
		Microsoft::WRL::ComPtr<IDXGIDevice> cpDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> cpDXGIAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> cpDXGIFactroy = nullptr;

		if (FAILED(m_cpDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)cpDXGIDevice.GetAddressOf())))
			return false;

		if (FAILED(cpDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)cpDXGIAdapter.GetAddressOf())))
			return false;

		if (FAILED(cpDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)cpDXGIFactroy.GetAddressOf())))
			return false;

		if (FAILED(cpDXGIFactroy->CreateSwapChain(m_cpDevice.Get(), &dxGiDesc, m_cpSwapChain.GetAddressOf())))
			return false;

		return true;
	}
	bool GraphicDevice_Dx11::CreateBuffer(ID3D11Buffer** _buffer, D3D11_BUFFER_DESC* _desc, D3D11_SUBRESOURCE_DATA* _data)
	{
		//D3D11_BUFFER_DESC triangleDesc = {};
		//triangleDesc.ByteWidth = desc->ByteWidth;
		//triangleDesc.BindFlags = desc->BindFlags;
		//triangleDesc.CPUAccessFlags = desc->CPUAccessFlags;


		/*D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;*/

		if(FAILED(m_cpDevice->CreateBuffer(_desc,_data,_buffer)))
			return false;

		return true;
	}
	bool GraphicDevice_Dx11::CreateShader()
	{
		//�����׸� ������Ʈ���� �����ϱ� ���ؼ��� ���� ������� �ʿ���
		
		//���� ��ġ -> �θ� ��ġ
		std::filesystem::path shaderPath =
			std::filesystem::current_path().parent_path();
		shaderPath += L"\\Shader_Source\\";

		std::filesystem::path vsPath(shaderPath.c_str());
		vsPath += L"TriangleVS.hlsl";

		//hlsl���� ������ ������ errorblob�� ����
		//�����Լ� ���ڿ��� , ����, 
		D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main", "vs_5_0", 0, 0, &W::renderer::triangleVSBlob, &W::renderer::errorBlob);

		if (W::renderer::errorBlob)
		{
			//���� �ɸ��� ������ӿ� ����
			OutputDebugStringA((char*)W::renderer::errorBlob->GetBufferPointer());
			W::renderer::errorBlob->Release();
		}
		
		m_cpDevice->CreateVertexShader(W::renderer::triangleVSBlob->GetBufferPointer(),
			W::renderer::triangleVSBlob->GetBufferSize(),
			nullptr, &W::renderer::triangleVSShader);
		
		std::filesystem::path psPath(shaderPath.c_str());
		psPath += L"TrianglePs.hlsl";

		D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, "main", "ps_5_0", 0, 0, &W::renderer::trianglePSBlob, &W::renderer::errorBlob);

		if (W::renderer::errorBlob)
		{
			//���� �ɸ��� ������ӿ� ����
			OutputDebugStringA((char*)W::renderer::errorBlob->GetBufferPointer());
			W::renderer::errorBlob->Release();
		}

		m_cpDevice->CreatePixelShader(W::renderer::trianglePSBlob->GetBufferPointer(),
			W::renderer::trianglePSBlob->GetBufferSize(),
			nullptr, &W::renderer::trianglePSShader);

		// Input layout ���� ���� ������ �Ѱ�����Ѵ�.
		// ���۰� �� �ø�ƽ�˷������
		//layer = ������ġ, ������ ũ��, ���������� �ø�ƽ �̸� �ø�ƽ �ѹ�
		//���� ���̴����� out��ȯ �ȼ� ���̴����� out���� ��ȯ���� �ȼ� �ϳ�
		//���� �����͸� gpu���� �˷������ (�Է������� �ܰ� , Input layout ���� ����)
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};
		//���� �� = 0
		arrLayout[0].AlignedByteOffset = 0;
		//�� ä�δ� 32��Ʈ�� �����ϴ� 3�� ���� ����� 96��Ʈ �ε� �Ҽ��� �����Դϴ�. 
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		//�Է� �����ʹ� �������� �������Դϴ�. (�ν��Ͻ� = 1)
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		//�ø�ƽ ���� �̸�
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		//vector(float3 12����Ʈ)�ڿ� color
		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		m_cpDevice->CreateInputLayout(arrLayout, 2,
			renderer::triangleVSBlob->GetBufferPointer(),
			renderer::triangleVSBlob->GetBufferSize(),
			&renderer::triangleLayout);

		return true;
	}
	

	bool GraphicDevice_Dx11::CreateTexture(const D3D11_TEXTURE2D_DESC* _desc, void* _pdata)
	{
		//2d �ؽ��� �ɼ�
		D3D11_TEXTURE2D_DESC dxGiDesc = {};
		dxGiDesc.BindFlags = _desc->BindFlags;
		dxGiDesc.Usage = _desc->Usage;
		dxGiDesc.CPUAccessFlags = 0;

		dxGiDesc.Format = _desc->Format;
		dxGiDesc.Width = _desc->Width;
		dxGiDesc.Height = _desc->Height;
		dxGiDesc.ArraySize = _desc->ArraySize;

		dxGiDesc.SampleDesc.Count = _desc->SampleDesc.Count;
		dxGiDesc.SampleDesc.Quality = 0;

		dxGiDesc.MipLevels = _desc->MipLevels;
		dxGiDesc.MiscFlags = _desc->MiscFlags;

		//���̹���
		if (FAILED(m_cpDevice->CreateTexture2D(&dxGiDesc, nullptr, m_cpDepthStencilBuffer.ReleaseAndGetAddressOf())))
			return false;

		//���̹��� ��
		if (FAILED(m_cpDevice->CreateDepthStencilView(m_cpDepthStencilBuffer.Get(), nullptr, m_cpDepthStencilView.GetAddressOf())))
			return false;

		return true;
	}
	void GraphicDevice_Dx11::BindViewPort(D3D11_VIEWPORT* _viewPort)
	{
		//����Ʈ ����
		m_cpContext->RSSetViewports(1, _viewPort);

	}
	void GraphicDevice_Dx11::SetConstantBuffer(ID3D11Buffer* _buffer, void* _data, UINT _iSize)
	{
		D3D11_MAPPED_SUBRESOURCE subRes = {};
		//���ҽ��� ��������� ���ε˴ϴ�. 
		m_cpContext->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
		//���� ����
		memcpy(subRes.pData, _data, _iSize);
		m_cpContext->Unmap(_buffer, 0);//����� unmap
	}
	void GraphicDevice_Dx11::BindConstantBuffer(eShaderStage _eStage, eCBType _eType, ID3D11Buffer* _buffer)
	{
		switch (_eStage)
		{
		case eShaderStage::VS:
			m_cpContext->VSSetConstantBuffers((UINT)_eType, 1, &_buffer);
			break;
		case eShaderStage::HS:
			m_cpContext->HSSetConstantBuffers((UINT)_eType, 1, &_buffer);
			break;
		case eShaderStage::DS:
			m_cpContext->DSSetConstantBuffers((UINT)_eType, 1, &_buffer);
			break;
		case eShaderStage::GS:
			m_cpContext->GSSetConstantBuffers((UINT)_eType, 1, &_buffer);
			break;
		case eShaderStage::PS:
			m_cpContext->PSSetConstantBuffers((UINT)_eType, 1, &_buffer);
			break;
		case eShaderStage::CS:
			m_cpContext->CSSetConstantBuffers((UINT)_eType, 1, &_buffer);
			break;
		case eShaderStage::END:
			break;
		default:
			break;
		}
	}
	void GraphicDevice_Dx11::BindsConstantBuffer(eShaderStage _eStage, eCBType _eType, ID3D11Buffer* _buffer)
	{
		m_cpContext->VSSetConstantBuffers((UINT)_eType, 1, &_buffer);
		m_cpContext->HSSetConstantBuffers((UINT)_eType, 1, &_buffer);
		m_cpContext->DSSetConstantBuffers((UINT)_eType, 1, &_buffer);
		m_cpContext->GSSetConstantBuffers((UINT)_eType, 1, &_buffer);
		m_cpContext->PSSetConstantBuffers((UINT)_eType, 1, &_buffer);
		m_cpContext->CSSetConstantBuffers((UINT)_eType, 1, &_buffer);

	}
	void GraphicDevice_Dx11::Draw()
	{
		//ȸ��
		FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		//����� �����
		m_cpContext->ClearRenderTargetView(m_cpRenderTargetView.Get(), bgColor);
		//���̹��� �����
		m_cpContext->ClearDepthStencilView(m_cpDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);

		//����Ʈ ������Ʈ
		HWND hWnd = application.GetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);
		m_tViewPort =
		{
			0.0f, 0.0f
			, (float)(winRect.right - winRect.left)
			, (float)(winRect.bottom - winRect.top)
			, 0.0f, 1.0f
		};
		
		BindViewPort(&m_tViewPort);
		m_cpContext->OMSetRenderTargets(1, m_cpRenderTargetView.GetAddressOf(), m_cpDepthStencilView.Get());
		
		// input assembler ���� ������ ����
		UINT vertexsize = sizeof(renderer::Vertex);
		UINT offset = 0;
		//������ ���� �迭�� �Է� ����� �ܰ迡 ���ε��մϴ�.
		m_cpContext->IASetVertexBuffers(0, 1, &renderer::triangleBuffer, &vertexsize, &offset);

		//UINT����Ʈ�ε���
		m_cpContext->IASetIndexBuffer(renderer::triangleIdxBuffer, DXGI_FORMAT_R32_UINT, 0);
		m_cpContext->IASetInputLayout(renderer::triangleLayout);
		//��� �׸���
		m_cpContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		//bind vs, ps
		m_cpContext->VSSetShader(renderer::triangleVSShader, 0, 0);
		m_cpContext->PSSetShader(renderer::trianglePSShader, 0, 0);

		//m_cpContext->Draw(12, 0);
		m_cpContext->DrawIndexed(3, 0, 0);

		//����Ÿ�ٿ� �ִ� �̹����� ȭ�鿡 �׷��ش�
		m_cpSwapChain->Present(0, 0);
	}


	// ps���� ���� �������� �����͵��� �����Ǳ� ������ �ȼ��� �߰����� ����
	//�����Ͷ��ؿ��� �޸����� ������ ����� �յΤӸ� �ǰ��ϱ� ������ ������ �����(���ֺ��������� �޸�) ���� �����°� �޶���

}
