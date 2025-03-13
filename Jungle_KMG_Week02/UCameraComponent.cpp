#include "stdafx.h"
#include "UCameraComponent.h"
#include "Input.h"
#include "Time.h"
#include "AActor.h"
#include "ULineComponent.h"

void UCameraComponent::Update() {
	const float speed = 2.0f;
	auto loc = GetRelativeLocation();
	FVector movement = FVector::Zero;
	if ( Input::Instance().IsKeyDown(DIK_A) ) {
		movement -= Right();
	}
	if ( Input::Instance().IsKeyDown(DIK_D) ) {
		movement += Right();
	}
	if ( Input::Instance().IsKeyDown(DIK_W) ) {
		movement += Front();
	}
	if ( Input::Instance().IsKeyDown(DIK_S) ) {
		movement -= Front();
	}
	if ( Input::Instance().IsKeyDown(DIK_E) ) {
		movement += Up();
	}
	if ( Input::Instance().IsKeyDown(DIK_Q) ) {
		movement -= Up();
	}
	SetRelativeLocation(loc + movement * Time::GetDeltaTime() * speed);
	if ( Input::Instance().IsMouseButtonDown(1) ) {
		int dx, dy;
		Input::Instance().GetMouseDelta(dx, dy);
		auto rot = GetRelativeRotation();
		SetRelativeRotation(rot + FVector(degToRad(dy) * mouseSensitive, degToRad(dx) * mouseSensitive, 0));
	}
	if ( Input::Instance().IsMouseButtonReleased(0) ) {
		int x, y;
		Input::Instance().GetMouseLocation(x, y);
		
		auto linecomp = new ULineComponent();
		linecomp->SetStartVector(FVector(1, 1, 1));
		linecomp->SetEndVector(FVector(1, 2, 1));
		linecomp->SetMesh();

		AActor* line = new AActor();
		line->RegisterComponent(linecomp);
		AddActor(line);
	}

}

FMatrix UCameraComponent::Projection() {
	if ( orthogonal )
		return OrthgonalProjection();
	else
		return PerspectiveProjection();
}

FMatrix UCameraComponent::OrthgonalProjection() {

	float zRange = farDistance - nearDistance;
	const float scale = orthoScale;
#ifdef _COL_MAJOR_SYSTEM
	return FMatrix({
		scale / aspectRatio, 0.f, 0.f, 0.f,
		0.f, scale, 0.f, 0.f,
		0.f, 0.f, 1.f / zRange, 0.f,
		0.f, 0.f, -nearDistance / zRange, 1.f
	});
#else
	return FMatrix({
		scale / aspectRatio, 0.f, 0.f, 0.f,
		0.f, scale, 0.f, 0.f,
		0.f, 0.f, 1.f / zRange, -nearDistance / zRange,
		0.f, 0.f, 0.f, 1.f
	});
#endif //_COL_MAJOR_SYSTEM
}

FMatrix UCameraComponent::PerspectiveProjection() {
	float yScale = 1.0f / tanf(degToRad(fieldOfView * 0.5f)); // cot(FOV/2)
	float xScale = yScale / aspectRatio;
	float zRange = farDistance - nearDistance;
#ifdef _COL_MAJOR_SYSTEM
	return FMatrix({
		 xScale,  0.0f,   0.0f,                         0.0f,
		 0.0f,    yScale, 0.0f,                         0.0f,
		 0.0f,    0.0f,   farDistance / zRange,         - nearDistance * farDistance / zRange,
		 0.0f,    0.0f,  1.0f,							0.0f
	});
#else
	return FMatrix({
		 xScale,  0.0f,   0.0f,                         0.0f ,
		 0.0f,    yScale, 0.0f,                         0.0f,
		 0.0f,    0.0f,   farDistance / zRange,                1.0f ,
		 0.0f,    0.0f,  -nearDistance * farDistance / zRange,        0.0f
	});
#endif //_COL_MAJOR_SYSTEM
}

void UCameraComponent::Start() {}

void UCameraComponent::Render() {}

void UCameraComponent::Remove() {}
