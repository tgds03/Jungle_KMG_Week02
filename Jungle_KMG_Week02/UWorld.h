#pragma once
#include "AActor.h"
class UWorld: public UObject {
protected:
	TArray<AActor*> _actors;

public:
	virtual void Update();
	virtual void Render();
	void AddActor(AActor*);
	TArray<AActor*>::iterator ActorBegin() { return _actors.begin(); }
	TArray<AActor*>::iterator ActorEnd() { return _actors.end(); }
};


class UCameraComponent;
class UTestWorld: public UWorld {
public:
	UTestWorld();
	void Update();
	void Render();
	AActor* selected;
};