#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

enum class eShaderStage
{
	VS,
	HS,
	DS,
	GS,
	PS,
	CS,
	END,
};

enum class eCBType
{
	Transform,
	END,
};

//버퍼의 공통적으로 받는 ID3D11buffer, 옵션 다 받을 수 있게
struct GpuBuffer
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	D3D11_BUFFER_DESC desc;

	GpuBuffer() :
		buffer(nullptr),
		desc{}
	{
		
	}

	//기본 소멸자
	virtual ~GpuBuffer() = default;
};