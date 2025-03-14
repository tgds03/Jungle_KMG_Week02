#include "stdafx.h"
#include "USceneComponent.h"

FMatrix USceneComponent::Transformation() const {
#ifdef _ROW_MAJOR_SYSTEM
	FMatrix m = FMatrix::Scale(RelativeScale3D) * FMatrix::RotateXYZ(RelativeRotation) * FMatrix::Translate(RelativeLocation);
#else
    FMatrix m = FMatrix::Translate(RelativeLocation) * FMatrix::RotateXYZ(RelativeRotation) * FMatrix::Scale(RelativeScale3D);
#endif
    return m;
}

FVector USceneComponent::Right() {
#ifdef _ROW_MAJOR_SYSTEM
	FVector4 r = Transformation().r1(); // (1,0,0,0) * getcomponenttransform
#else
	FVector4 r = Transformation().c1(); // (1,0,0,0) * getcomponenttransform
#endif
	return FVector(r.x, r.y, r.z).Normalized();
}

FVector USceneComponent::Up() {
#ifdef _ROW_MAJOR_SYSTEM
	FVector4 r = Transformation().r2();
#else
	FVector4 r = Transformation().c2();
#endif
	return FVector(r.x, r.y, r.z).Normalized();
}

FVector USceneComponent::Front() {
#ifdef _ROW_MAJOR_SYSTEM
	FVector4 r = Transformation().r3();
#else
	FVector4 r = Transformation().c3();
#endif
	return FVector(r.x, r.y, r.z).Normalized();
}
