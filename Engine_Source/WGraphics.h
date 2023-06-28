#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
//16����Ʈ�θ� �����
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name 

//0�� ���� ��ġ
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

//������ ���������� �޴� ID3D11buffer, �ɼ� �� ���� �� �ְ�
struct GpuBuffer
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	D3D11_BUFFER_DESC desc;

	GpuBuffer() :
		buffer(nullptr),
		desc{}
	{
		
	}

	//�⺻ �Ҹ���
	virtual ~GpuBuffer() = default;
};