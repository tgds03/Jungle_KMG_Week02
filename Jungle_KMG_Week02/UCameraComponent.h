#pragma once
#include "USceneComponent.h"
class UCameraComponent :public USceneComponent {
public:
	bool orthogonal = false;
	float fieldOfView = 60.f;
	float orthoScale = 0.5f;
	float aspectRatio = SCR_WIDTH / (float)SCR_HEIGHT;
	float nearDistance = 1.01f, farDistance = 100.f;
	float mouseSensitive = 0.5f;
	virtual void Update() override;
	FMatrix Projection();
	FMatrix OrthgonalProjection();
	FMatrix PerspectiveProjection();

	// USceneComponent을(를) 통해 상속됨
	void Start() override;
	void Render() override;
	void Remove() override;
};

