#pragma once
#include "AActor.h"
class UWorld: public UObject {
	TArray<AActor*> _actors;

public:
	virtual void Update();
	virtual void Render();
	void AddActor(AActor*);
};

class UTestWorld: public UWorld {
public:
	UTestWorld();
	void Update();
	void Render();
};