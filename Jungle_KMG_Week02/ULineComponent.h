#pragma once
#include "USceneComponent.h"
#include "CMesh.h"
class ULineComponent :public USceneComponent {
private:
	FVector start, end;
public:
	
	void SetStartVector(FVector s);
	void SetEndVector(FVector s);
	void SetMesh();
	// USceneComponent을(를) 통해 상속됨
	void Start() override;
	void Update() override;
	void Render() override;
	void Remove() override;
};

