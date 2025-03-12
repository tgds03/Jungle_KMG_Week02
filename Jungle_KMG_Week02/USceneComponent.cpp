#include "stdafx.h"
#include "USceneComponent.h"

FMatrix USceneComponent::Transformation() const {
    FMatrix m = FMatrix::Scale(RelativeScale3D);
    m = m * FMatrix::RotateXYZ(RelativeRotation);
    m = m * FMatrix::Translate(RelativeLocation);
    return m;
}
