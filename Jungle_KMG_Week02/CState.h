#pragma once
class CState {
public:
	CState(ID3D11Device* device) : _device(device) {};
	virtual ~CState() {};

protected:
	ID3D11Device* _device;
};

class CSamplerState : public CState {
	using Super = CState;
public:
	CSamplerState(ID3D11Device* device) : Super(device), _samplerState(nullptr) {};
	~CSamplerState() { 
		SafeRelease(_samplerState);
	};
	ID3D11SamplerState* Get() { return _samplerState; }

	
	void SetAddress(D3D11_TEXTURE_ADDRESS_MODE u, D3D11_TEXTURE_ADDRESS_MODE v, D3D11_TEXTURE_ADDRESS_MODE w);
	void SetBorderColor(float r, float g, float b, float a);
	void Create();

private:
	ID3D11SamplerState* _samplerState;
	D3D11_SAMPLER_DESC _desc = {};
};

class CRasterizerState : public CState {
	using Super = CState;
public:
	CRasterizerState(ID3D11Device* device) : Super(device), _rasterizerState(nullptr) {};
	~CRasterizerState() {
		SafeRelease(_rasterizerState);
	};
	ID3D11RasterizerState* Get() { return _rasterizerState; }

	void Create();
private:
	ID3D11RasterizerState* _rasterizerState;
};

class CBlendState : public CState {
	using Super = CState;
public:
	CBlendState(ID3D11Device* device) : Super(device), _blendState(nullptr) {};
	~CBlendState() {
		SafeRelease(_blendState);
	}
	ID3D11BlendState* Get() { return _blendState; }

	void Create();
	void SetSrcBlend(D3D11_BLEND srcBlend, D3D11_BLEND srcBlendAlpha);
	void SetDescBlend(D3D11_BLEND destBlend, D3D11_BLEND destBlendAlpha);
	void SetOp(D3D11_BLEND_OP op);
private:
	ID3D11BlendState* _blendState;
	D3D11_BLEND_DESC _desc = {};
};

class CDepthStencilState: public CState {
	using Super = CState;
public:
	CDepthStencilState(ID3D11Device* device) : Super(device), _depthStencilState(nullptr) {};
	~CDepthStencilState() {
		SafeRelease(_depthStencilState);
	}
	ID3D11DepthStencilState* Get() { return _depthStencilState; }

	void Create();
private:
	ID3D11DepthStencilState* _depthStencilState;
};