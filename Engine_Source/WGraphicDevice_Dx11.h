#pragma once

#include "Engine.h"
#include "WGraphics.h"

//DirectX 11 라이브러리 추가(정적)


namespace W::graphics
{
	class GraphicDevice_Dx11
	{
	
	public:
		GraphicDevice_Dx11();
		~GraphicDevice_Dx11();

		bool CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* _desc, HWND _hwnd);
		bool CreateTexture(const D3D11_TEXTURE2D_DESC* _desc, void* _pdata);
		bool CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* _pInputElementDescs, UINT _iNumElements, ID3DBlob* _byteCode, ID3D11InputLayout** _ppInputLayout);
		bool CreateBuffer(ID3D11Buffer** _buffer, D3D11_BUFFER_DESC* _desc, D3D11_SUBRESOURCE_DATA* _data);
		bool CompileFromfile(const std::wstring& _wstrFileName, const std::string& _strFunName, const std::string& _strVersion, ID3DBlob** _ppCod);
		bool CreateVertexShader(const void* _pShaderByteCode, SIZE_T _BytecodeLength, ID3D11VertexShader** _ppVertexShader);
		bool CreatePixelShader(const void* _pShaderByteCode, SIZE_T _BytecodeLength, ID3D11PixelShader** _ppPixelShader);


		
		void BindInputLayout(ID3D11InputLayout* _pInputLayout);
		void BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology);
		void BindVertexBuffer(UINT _iStartSlot, ID3D11Buffer* const* _ppVertexBuffers, const UINT* _pStrides, const UINT* _pOffsets);
		void BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT _Format, UINT _iOffset);
		void BindVertexShader(ID3D11VertexShader* _pVertexShader);
		void BindPixelShader(ID3D11PixelShader* _pPixelShader);
		void SetConstantBuffer(ID3D11Buffer* _buffer, void* _data, UINT _iSize);
		void BindConstantBuffer(eShaderStage _eStage, eCBType _eType, ID3D11Buffer* _buffer);
		void BindsConstantBuffer(eShaderStage _eStage, eCBType _eType, ID3D11Buffer* _buffer);
		void BindShaderResource(eShaderStage _eStage, UINT _iStartSlot, ID3D11ShaderResourceView** _ppSRV);

		void BindViewPort(D3D11_VIEWPORT* _viewPort);//뷰포트로 전환

		void DrawIndexed(UINT _iIndexCount, UINT _iStartIndexLocation, INT _iBaseVertexLocation);
		void ClearTarget();
		void UpdateViewPort();
		void Draw();
		void Present();
		
		ID3D11Device* GetID3D11Device() { return m_cpDevice.Get(); }

	private:
		// 실제 그래픽카드 하드웨어 객체
		Microsoft::WRL::ComPtr<ID3D11Device> m_cpDevice;

		//  dx11에서 직접적으로 디바이스객체 접근하지않고
		// 이객체를 이용하여 명령을 내린다.
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_cpContext;

		// 최종적으로 그려질 텍스처(도화지)
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_cpRenderTarget;

		// 렌더타겟에 직접접근하지 않고 레더타겟뷰를 통해서 접근한다.
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_cpRenderTargetView;

		// 깊이버퍼
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_cpDepthStencilBuffer;

		// 깊이버퍼에 접근할수 있는 뷰
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_cpDepthStencilView;

		// 더블버퍼링 작업을 진행해주는 swapChain
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_cpSwapChain;

		D3D11_VIEWPORT m_tViewPort;
	};

	inline GraphicDevice_Dx11*& GetDevice()
	{
		static GraphicDevice_Dx11* device = nullptr;
		return device;
 	}
}

