#include "stdafx.h"
#include "AActor.h"

void AActor::RegisterComponent(UActorComponent* comp) {
	_components.push_back(comp);
}

void AActor::Start() {
	for( auto& comp: _components ) {
		comp->Start();
	}
}

void AActor::Update() {
	for ( auto& comp : _components ) {
		comp->Update();
	}
}

void AActor::Render() {
	for ( auto& comp : _components ) {
		comp->Render();
	}
}

void AActor::Remove() {
	for ( auto& comp : _components ) {
		comp->Remove();
	}
}
