#pragma once
#include "Engine.h"
#include "WGraphicDevice_Dx11.h"


using namespace W::math;
namespace W::renderer
{
	struct Vertex
	{
		Vector3 Pos;
		Vector4 Color;
	};

	extern Vertex vertexes[];
	extern ID3D11Buffer* triangleBuffer;
	extern ID3DBlob* errorBlob;
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVSShader;
	extern ID3DBlob* trianglePosBlob;
	extern ID3D11PixelShader* trianglePSShader;



	void Initialize();
}

