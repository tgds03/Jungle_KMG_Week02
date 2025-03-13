#pragma once
class CInputLayout {
public:
	CInputLayout(ID3D11Device* device) : _device(device), _inputLayout(nullptr) {};
	~CInputLayout() { 
		SafeRelease(_inputLayout); 
	};
	void Release() {};
	ID3D11InputLayout* Get() { return _inputLayout; }

	void Create(const std::vector<D3D11_INPUT_ELEMENT_DESC>& descs, ID3DBlob* vsblob);

private:
	ID3D11Device* _device;
	ID3D11InputLayout* _inputLayout;
};

struct FVertexColor {
	float x, y, z;
	float r, g, b, a;
	FVertexColor(float x, float y, float z, float r, float g, float b, float a) :
		x(x), y(y), z(z), r(r), g(g), b(b), a(a) {};
	static TArray<D3D11_INPUT_ELEMENT_DESC> descs;
};

struct FVertexTexture {
	float x, y, z, w;
	float u, v;
	FVertexTexture(float x, float y, float z, float u, float v) :
		x(x), y(y), z(z), u(u), v(v) {};
	static TArray<D3D11_INPUT_ELEMENT_DESC> descs;
};