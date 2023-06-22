#pragma once
#include "Engine.h"
#include "WGraphicDevice_Dx11.h"
#include "WMesh.h"
#include "WShader.h"
#include "WConstantBuffer.h"

using namespace W::math;
namespace renderer
{
	struct Vertex
	{
		Vector3 Pos;
		Vector4 Color;
		Vector2 UV;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix m_mWorld;
		Matrix m_mView;
		Matrix m_mProjection;
	};

	extern Vertex vertexes[];
	//extern ID3D11InputLayout* triangleLayout;
	//extern ID3D11Buffer* triangleBuffer;
	//extern ID3D11Buffer* triangleIdxBuffer;
	//extern W::Mesh* mesh;
	extern W::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::END];
	//extern ID3DBlob* errorBlob;
	//extern ID3DBlob* triangleVSBlob;
	//extern ID3D11VertexShader* triangleVSShader;
	//extern ID3DBlob* trianglePSBlob;
	//extern W::Shader* shader;
	//extern ID3D11PixelShader* trianglePSShader;



	void Initialize();
	void Release();
}

