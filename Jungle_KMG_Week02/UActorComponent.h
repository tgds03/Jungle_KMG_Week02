#pragma once
#include "UObject.h"
class UActorComponent: public UObject {
public:
	virtual void Start() abstract;
	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void Remove() abstract;
};

