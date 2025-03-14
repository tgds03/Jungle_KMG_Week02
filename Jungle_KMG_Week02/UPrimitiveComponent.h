#pragma once
#include "USceneComponent.h"
#include "CRenderer.h"
#include "CMesh.h"
#include "Geometry.h"

class UPrimitiveComponent : public USceneComponent {
protected:
	BoundingBox aabb;
public:
	UPrimitiveComponent() {};
	inline BoundingBox GetAABB() const { return aabb; }
	inline virtual bool IsRayIntersect(Ray ray) {
		return false;
	};
	//virtual void Render() abstract;
};

