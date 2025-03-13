#pragma once
#include "USceneComponent.h"
#include "CMesh.h"
class UGridComponent :public USceneComponent {
private:

public:
	UGridComponent();

	virtual void Render();

	// USceneComponent을(를) 통해 상속됨
	void Start() override;
	void Update() override;
	void Remove() override;
};

