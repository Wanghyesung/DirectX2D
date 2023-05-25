#include "WGraphicDevice_Dx11.h"
#include "WApplication.h"
#include "WRenderer.h"

extern W::Application application;

namespace W::graphics
{
	//ram위에 gpu그래픽카드의 주소를 가르키는 변수를 올려둠
	//기본적으로 전부 포인터임
	//getaddres로 그 변수의 주소를 가져올 수 있음
	//이중버퍼를 통한 함수로 그 포인터에 값을 할당하고 나옴
	//desc 옵션기능 

	//스왑체인 안에 버퍼를 렌더타켓에 전달
	//엘리러싱
	//밉맵-> 미리 텍스쳐들의 크기별로 만들어두는법 ->그때그떄 연산을 할 필요가없다
	
	//바탕은 하늘, 회색으로 하기 -> 검은색이나 흰색이면 물체를 실수로 검은색으로 했을 떄 안보일 수 있음

	GraphicDevice_Dx11::GraphicDevice_Dx11()
	{
		//Device, Context 생성
		HWND hwnd = application.GetHwnd();
		//이걸 해야지 디버그 모드로 돌릴 수 있음 배포용은 다른걸로
		UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		//d3d 드라이버 기능별 
		D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL)0;
		//int a = 10;
		//int* b = &a;
		//int** c = &b;
		//**c;
		//ID3D11Device* pDevice = nullptr;
		//ID3D11DeviceContext* pContext = nullptr;
		//ID3D11DeviceContext** ppContext = &pContext;

		//null전달, 드라이버형식 타입, 드라이버가 HARDWARE일 경우 null,
		//런타입 계층, featruelevel의 수 D3D11_SDK_VERSION사용, 
		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
			deviceFlag, nullptr, 0, D3D11_SDK_VERSION,
			m_cpDevice.GetAddressOf(), &featureLevel,
			m_cpContext.GetAddressOf());


		//스왑체인 옵션 (백퍼버 표시 모드 설명)
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		//버퍼 계수
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = application.GetWidth();
		swapChainDesc.BufferDesc.Height = application.GetHeight();

		if (!CreateSwapChain(&swapChainDesc, hwnd))
			return;

		// 스왑체인에 있는 렌더타겟 가져오기
		if (FAILED(m_cpSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D)
			, (void**)m_cpRenderTarget.GetAddressOf())))
			return;

		//렌더타겟뷰 생성
		m_cpDevice->CreateRenderTargetView((ID3D11Resource*)m_cpRenderTarget.Get()
			, nullptr, m_cpRenderTargetView.GetAddressOf());

		//2d 텍스쳐 옵션(깊이버퍼)
		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		//출력 병합 과정에서  깊이 스텐실 대상으로 바인딩합니다
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		//24비트
		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		//텍스처를 읽고 쓰는 방법을 식별하는 값입니다.
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		//버퍼 해상도
		depthStencilDesc.Width = application.GetWidth();
		depthStencilDesc.Height = application.GetHeight();
		//텍스처 배열의 텍스처 수입니다
		depthStencilDesc.ArraySize = 1;

		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA data;
		if (!CreateTexture(&depthStencilDesc, &data))
			return;

		// 스텐실 버퍼를 출력-병합 단계에 바인딩합니다.
		m_cpContext->OMSetRenderTargets(1, m_cpRenderTargetView.GetAddressOf(), m_cpDepthStencilView.Get());

	}
	GraphicDevice_Dx11::~GraphicDevice_Dx11()
	{

	}
	bool GraphicDevice_Dx11::CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* _desc, HWND _hwnd)
	{
		DXGI_SWAP_CHAIN_DESC dxGiDesc = {};

		//출력창 window핸들값
		dxGiDesc.OutputWindow = _hwnd;
		//출력창 모드인지
		dxGiDesc.Windowed = true;

		dxGiDesc.BufferCount = _desc->BufferCount;
		dxGiDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;

		//표면 또는 리소스를 출력 렌더링 대상으로 사용합니다.
		dxGiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		dxGiDesc.BufferDesc.Width = _desc->BufferDesc.Width;
		dxGiDesc.BufferDesc.Height = _desc->BufferDesc.Height;
		//888 rgb 32비트
		dxGiDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		dxGiDesc.BufferDesc.RefreshRate.Numerator = 240;//최대 프레임
		dxGiDesc.BufferDesc.RefreshRate.Denominator = 1; //최소 프레임
		//지정된 모니터의 해상도에 맞게 이미지가 늘어나는 방식 (확대비율 지정) 
		dxGiDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		dxGiDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		//픽셀당 다중 샘플 수, 이미지 품질 수준 0~1
		dxGiDesc.SampleDesc.Count = 1;
		dxGiDesc.SampleDesc.Quality = 0;

		//adapter = 모니터
		//GIdevice = 렌더타겟
		//factory = 전체화면처리
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

		//공유항목 프로젝트끼리 연결하기 위해서는 파일 입출력이 필요함
		ID3DBlob* vsBolp = nullptr;
		//현재 위치 -> 부모 위치
		std::filesystem::path shaderPath =
			std::filesystem::current_path().parent_path();
		shaderPath += L"\\Shader_Source\\";

		std::filesystem::path vsPath(shaderPath.c_str());
		vsPath += L"TriangleVS.hlsl";

		//hlsl파일 컴파일 오류는 errorblob에 나옴
		//메인함수 문자열로 , 버전, 
		D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main", "vs_5_0", 0, 0, &W::renderer::triangleVSBlob, &W::renderer::errorBlob);

		if (W::renderer::errorBlob)
		{
			//에러 걸리면 에러블롭에 나옴
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
		//2d 텍스쳐 옵션
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
		//회색
		FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		//백버퍼 지우기
		m_cpContext->ClearRenderTargetView(m_cpRenderTargetView.Get(), bgColor);

		//렌더링된 이미지 표시
		m_cpSwapChain->Present(0, 0);
	}
}
