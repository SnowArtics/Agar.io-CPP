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
		//�� �Լ��� ������ constantBuffer�� GPU�� �����ִ� ������ �Ѵ�. �̷��� �ϸ� �ش��ϴ� �����Ͱ�
		//GPU�� �������ش�.
		void SetConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size);
		//������ ������ �����͸� �����Ϳ� �����ִ°� �� �Լ��� �Ѵ�.
		void BindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		//��� ���������� �� �����ش�. Switch Case �Ⱦ�
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
		// ���� �׷���ī�� �ϵ���� ��ü
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		//  dx11���� ���������� ����̽���ü ���������ʰ�
		// �̰�ü�� �̿��Ͽ� ������ ������.
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		// ���������� �׷��� �ؽ�ó(��ȭ��)
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;
		// ����Ÿ�ٿ� ������������ �ʰ� ����Ÿ�ٺ並 ���ؼ� �����Ѵ�.
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
		// ���̹���
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;
		// ���̹��ۿ� �����Ҽ� �ִ� ��
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;
		// �������۸� �۾��� �������ִ� swapChain
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
		
		//NDC��ǥ�踦 ����Ʈ�� �������ֱ� ���� �ڷ��� ����.
		D3D11_VIEWPORT mViewPort;
	};

	inline GraphicDevice_Dx11*& GetDevice() {
		static GraphicDevice_Dx11* device = nullptr;
		return device;
	}
}
