#pragma once
#include "AActor.h"
class UWorld: public UObject {
	TArray<AActor*> _actors;

public:
	void Update();
	void Render();
	void AddActor(AActor*);
};

