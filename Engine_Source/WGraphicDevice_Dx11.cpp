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

		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA data;
		if (!CreateTexture(&depthStencilDesc, &data))
			return;

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
		///* [annotation] */
		//_In_reads_(BytecodeLength)  const void* pShaderBytecode,
		//	/* [annotation] */
		//	_In_  SIZE_T BytecodeLength,
		//	/* [annotation] */
		//	_In_opt_  ID3D11ClassLinkage* pClassLinkage,
		//	/* [annotation] */
		//	_COM_Outptr_opt_  ID3D11VertexShader** ppVertexShader

		//�����׸� ������Ʈ���� �����ϱ� ���ؼ��� ���� ������� �ʿ���
		ID3DBlob* vsBolp = nullptr;
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

		if (FAILED(m_cpDevice->CreateTexture2D(&dxGiDesc, nullptr, m_cpDepthStencilBuffer.ReleaseAndGetAddressOf())))
			return false;

		if (FAILED(m_cpDevice->CreateDepthStencilView(m_cpDepthStencilBuffer.Get(), nullptr, m_cpDepthStencilView.GetAddressOf())))
			return false;

		return true;
	}
	void GraphicDevice_Dx11::Draw()
	{
		//ȸ��
		FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		//����� �����
		m_cpContext->ClearRenderTargetView(m_cpRenderTargetView.Get(), bgColor);

		//�������� �̹��� ǥ��
		m_cpSwapChain->Present(0, 0);
	}
}
