#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
//16바이트로만 만들게
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name 

//0번 슬롯 위치
#define CBSLOT_TRANSFORM		0
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
	Material,
	END,
};

enum class eSamplerType
{
	Point,
	Anisotropic,
	End,
};

enum class eRSType
{
	SolidBack,
	SolidFront,
	SolidNone,
	WireframeNone,
	End,
};

enum class eDSType
{
	Less,
	Greater,
	NoWrite,
	None,
	End,
};

enum class eBSType
{
	Default,
	AlphaBlend,
	OneOne,
	End,
};

enum class eRenderingMode
{
	Opaque,
	CutOut,
	Transparent,
	End,
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