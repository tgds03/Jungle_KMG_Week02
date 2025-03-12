#pragma once
#include "UActorComponent.h"
class USceneComponent :public UActorComponent {
private:
	FVector RelativeLocation;
	FVector RelativeRotation;
	FVector RelativeScale3D = FVector::One;
public:

	inline void SetRelativeLocation(FVector pos) noexcept;
	inline void SetRelativeRotation(FVector pos) noexcept;
	inline void SetRelativeScale(FVector pos) noexcept;

	inline FVector GetRelativeLocation() noexcept;
	inline FVector GetRelativeRotation() noexcept;
	inline FVector GetRelativeScale() noexcept;

	FMatrix Transformation() const;
	FVector Right();
	FVector Up();
	FVector Front();
};

inline void USceneComponent::SetRelativeLocation(FVector pos) noexcept {
	RelativeLocation = pos;
}

inline void USceneComponent::SetRelativeRotation(FVector rot) noexcept {
	RelativeRotation = rot;
}

inline void USceneComponent::SetRelativeScale(FVector scale) noexcept {
	RelativeScale3D = scale;
}

inline FVector USceneComponent::GetRelativeLocation() noexcept {
	return RelativeLocation;
}

inline FVector USceneComponent::GetRelativeRotation() noexcept {
	return RelativeRotation;
}

inline FVector USceneComponent::GetRelativeScale() noexcept {
	return RelativeScale3D;
}

