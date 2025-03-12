#include "stdafx.h"
#include "UCameraComponent.h"

void UCameraComponent::Update() {}

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
