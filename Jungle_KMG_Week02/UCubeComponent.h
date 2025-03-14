#pragma once
#include "UPrimitiveComponent.h"
class UCubeComponent: public UPrimitiveComponent {
public:
	UCubeComponent();

	virtual bool IsRayIntersect(Ray ray);

	void Update() override;
	void Render() override;

	// UPrimitiveComponent을(를) 통해 상속됨
	void Start() override;
	void Remove() override;
};

