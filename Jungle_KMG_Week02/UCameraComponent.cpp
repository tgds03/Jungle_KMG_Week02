#include "stdafx.h"
#include "UCameraComponent.h"
#include "Input.h"
#include "Time.h"

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
		SetRelativeRotation(rot - FVector(degToRad(dy) * mouseSensitive, degToRad(dx) * mouseSensitive, 0));

		//RelativeRotation.y -= degToRad(dx) * mouseSensitive;
		//RelativeRotation.x -= degToRad(dy) * mouseSensitive;
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
	return FMatrix({
		scale / aspectRatio, 0.f, 0.f, 0.f,
		0.f, scale, 0.f, 0.f,
		0.f, 0.f, 1.f / zRange, -nearDistance / zRange,
		0.f, 0.f, 0.f, 1.f
	});
}

FMatrix UCameraComponent::PerspectiveProjection() {
	float yScale = 1.0f / tanf(degToRad(fieldOfView * 0.5f)); // cot(FOV/2)
	float xScale = yScale / aspectRatio;
	float zRange = farDistance - nearDistance;

	return FMatrix({
		 xScale,  0.0f,   0.0f,                         0.0f ,
		 0.0f,    yScale, 0.0f,                         0.0f,
		 0.0f,    0.0f,   farDistance / zRange,                1.0f ,
		 0.0f,    0.0f,  -nearDistance * farDistance / zRange,        0.0f
	});
}

void UCameraComponent::Start() {}

void UCameraComponent::Render() {}

void UCameraComponent::Remove() {}
