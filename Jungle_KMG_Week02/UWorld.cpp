#include "stdafx.h"
#include "UWorld.h"

void UWorld::Update() {
	for(auto& actor: _actors) {
		actor->Update();
	}
}

void UWorld::Render() {
	for ( auto& actor : _actors ) {
		actor->Render();
	}
}

void UWorld::AddActor(AActor* actor) {
	_actors.push_back(actor);
}
