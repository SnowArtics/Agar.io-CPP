#pragma once
#include "SnowEngine.h"
#include "snGraphics.h"

namespace sn::graphics
{
	class GraphicDevice_Dx11
	{
	public:
		GraphicDevice_Dx11();
		~GraphicDevice_Dx11();

	public:
		bool CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd);		
		bool CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data);
		bool CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, ID3DBlob* byteCode, ID3D11InputLayout** ppInputLayout);
		bool CreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data);
		bool CompileFromfile(const std::wstring& fileName, const std::string& funcName, const std::string& version, ID3DBlob** ppCode);
		bool CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11VertexShader** ppVertexShader);
		bool CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11PixelShader** ppPixelShader);

		void BindInputLayout(ID3D11InputLayout* pInputLayout);
		void BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);
		void BindVertexBuffer(UINT StartSlot, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets);
		void BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset);
		void BindVertexShader(ID3D11VertexShader* pVetexShader);
		void BindPixelShader(ID3D11PixelShader* pPixelShader);
		//이 함수는 생성한 constantBuffer를 GPU에 묶어주는 역할을 한다. 이렇게 하면 해당하는 데이터가
		//GPU에 생성해준다.
		void SetConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size);
		//위에서 생성한 데이터를 셰이터에 보내주는걸 이 함수가 한다.
		void BindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		//모든 스테이지에 다 보내준다. Switch Case 안씀
		void BindsConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		
		void BindViewPort(D3D11_VIEWPORT* viewPort);
		
		void DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
		void Draw();
		void Present();

	public:
		Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() { return mDevice; }
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetContext() { return mContext; }
		Microsoft::WRL::ComPtr<ID3D11Texture2D> GetRenderTarget() { return mRenderTarget; }
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRenderTargetView() { return mRenderTargetView; }
		Microsoft::WRL::ComPtr<ID3D11Texture2D> GetDepthStencil() { return mDepthStencilBuffer; }
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencilView() { return mDepthStencilView; }
		Microsoft::WRL::ComPtr<IDXGISwapChain> GetSwapChain() { return mSwapChain; }

		D3D11_VIEWPORT GetViewPort() { return mViewPort; }

	private:
		// 실제 그래픽카드 하드웨어 객체
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		//  dx11에서 직접적으로 디바이스객체 접근하지않고
		// 이객체를 이용하여 명령을 내린다.
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		// 최종적으로 그려질 텍스처(도화지)
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;
		// 렌더타겟에 직접접근하지 않고 렌더타겟뷰를 통해서 접근한다.
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
		// 깊이버퍼
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;
		// 깊이버퍼에 접근할수 있는 뷰
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;
		// 더블버퍼링 작업을 진행해주는 swapChain
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
		
		//NDC좌표계를 뷰포트로 변경해주기 위한 자료형 선언.
		D3D11_VIEWPORT mViewPort;
	};

	inline GraphicDevice_Dx11*& GetDevice() {
		static GraphicDevice_Dx11* device = nullptr;
		return device;
	}
}

