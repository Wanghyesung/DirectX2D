#pragma once

#include "Engine.h"
#include "WGraphics.h"

//DirectX 11 ���̺귯�� �߰�(����)
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace W::graphics
{
	class GraphicDevice_Dx11
	{
	
	public:
		GraphicDevice_Dx11();
		~GraphicDevice_Dx11();

		bool CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* _desc, HWND _hwnd);
		bool CreateBuffer(ID3D11Buffer** _buffer, D3D11_BUFFER_DESC* _desc, D3D11_SUBRESOURCE_DATA* _data);
		bool CreateShader();
		bool CreateTexture(const D3D11_TEXTURE2D_DESC* _desc, void* _pdata);

		void BindViewPort(D3D11_VIEWPORT* _viewPort);//����Ʈ�� ��ȯ

		void SetConstantBuffer(ID3D11Buffer* _buffer, void* _data, UINT _iSize);
		void BindConstantBuffer(eShaderStage _eStage, eCBType _eType, ID3D11Buffer* _buffer);
		void BindsConstantBuffer(eShaderStage _eStage, eCBType _eType, ID3D11Buffer* _buffer);

		void Draw();
		//�ӽ�
		//void DrawCircle();

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

