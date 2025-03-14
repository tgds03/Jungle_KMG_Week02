#pragma once
#include "FVector.h"

struct Ray {
	FVector start;
	FVector end;
	Ray(FVector s, FVector e);
	FVector GetDirection();
	FVector GetDistance();
};

struct BoundingBox {
	FVector min;
	FVector max;
};