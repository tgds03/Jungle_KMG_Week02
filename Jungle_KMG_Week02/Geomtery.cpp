#include "stdafx.h"
#include "Geometry.h"

Ray::Ray(FVector s, FVector e): start(s), end(e) {}

FVector Ray::GetDirection() {
    return end - start;
}

FVector Ray::GetDistance() {
    return (end - start).Magnitude();
}
