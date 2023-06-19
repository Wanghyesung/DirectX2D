#pragma once

#include "Engine.h"
#include "WGraphics.h"

//DirectX 11 ���̺귯�� �߰�(����)


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

		void BindViewPort(D3D11_VIEWPORT* _viewPort);//����Ʈ�� ��ȯ

		void DrawIndexed(UINT _iIndexCount, UINT _iStartIndexLocation, INT _iBaseVertexLocation);
		void ClearTarget();
		void UpdateViewPort();
		void Draw();
		void Present();
		
		ID3D11Device* GetID3D11Device() { return m_cpDevice.Get(); }

	private:
		// ���� �׷���ī�� �ϵ���� ��ü
		Microsoft::WRL::ComPtr<ID3D11Device> m_cpDevice;

		//  dx11���� ���������� ����̽���ü ���������ʰ�
		// �̰�ü�� �̿��Ͽ� ����� ������.
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_cpContext;

		// ���������� �׷��� �ؽ�ó(��ȭ��)
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_cpRenderTarget;

		// ����Ÿ�ٿ� ������������ �ʰ� ����Ÿ�ٺ並 ���ؼ� �����Ѵ�.
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_cpRenderTargetView;

		// ���̹���
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_cpDepthStencilBuffer;

		// ���̹��ۿ� �����Ҽ� �ִ� ��
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_cpDepthStencilView;

		// ������۸� �۾��� �������ִ� swapChain
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_cpSwapChain;

		D3D11_VIEWPORT m_tViewPort;
	};

	inline GraphicDevice_Dx11*& GetDevice()
	{
		static GraphicDevice_Dx11* device = nullptr;
		return device;
 	}
}

