#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace sn::graphics
{
	enum class eShaderStage
	{
		VS, //VertexShader
		HS, //HullShader
		DS, //DynamicShader
		GS, //GraphicShader
		PS, //PixelShader
		CS, //Compute Shader
		End,
	};

	enum class eCBType//enumConstantBufferType
	{
		Transform,
		PlayerTransform,
		End,
	};

	struct GpuBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		D3D11_BUFFER_DESC desc;

		GpuBuffer()
			: buffer(nullptr)
			, desc{}
		{

		}
		virtual ~GpuBuffer() = default;
	};
}