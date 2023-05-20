#pragma once

#include "Engine.h"

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

	private:
		// ���� �׷���ī�� �ϵ���� ��ü
		Microsoft::WRL::ComPtr<ID3D11Device> m_gDevice;

		//  dx11���� ���������� ����̽���ü ���������ʰ�
		// �̰�ü�� �̿��Ͽ� ����� ������.
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_gContext;

		// ���������� �׷��� �ؽ�ó(��ȭ��)
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_gRenderTarget;

		// ����Ÿ�ٿ� ������������ �ʰ� ����Ÿ�ٺ並 ���ؼ� �����Ѵ�.
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_gRenderTargetView;

		// ���̹���
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_gDepthStencilBuffer;

		// ���̹��ۿ� �����Ҽ� �ִ� ��
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_gDepthStencilView;

		// ������۸� �۾��� �������ִ� swapChain
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_gSwapChain;
	};
}

