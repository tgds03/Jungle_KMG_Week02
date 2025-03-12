#include "stdafx.h"
#include "USceneComponent.h"

FMatrix USceneComponent::Transformation() const {
    FMatrix m = FMatrix::Scale(RelativeScale3D);
    m = m * FMatrix::RotateXYZ(RelativeRotation);
    m = m * FMatrix::Translate(RelativeLocation);
    return m;
}

FVector USceneComponent::Right() {
	FVector4 r = Transformation().r1(); // (1,0,0,0) * getcomponenttransform
	return FVector(r.x, r.y, r.z).Normalized();
}

FVector USceneComponent::Up() {
	FVector4 r = Transformation().r2();
	return FVector(r.x, r.y, r.z).Normalized();
}

FVector USceneComponent::Front() {
	FVector4 r = Transformation().r3();
	return FVector(r.x, r.y, r.z).Normalized();
}
