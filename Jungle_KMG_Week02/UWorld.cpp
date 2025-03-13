#include "stdafx.h"
#include "UWorld.h"
#include "UCameraComponent.h"
#include "UCubeComponent.h"
#include "UGridComponent.h"

void UWorld::Update() {
	//for(auto& actor: _actors) {
	for (int i = 0; i < _actors.size(); i++) {
		_actors[i]->Update();
	}
}

void UWorld::Render() {
	/*for ( auto& actor : _actors ) {*/
	for ( int i = 0; i < _actors.size(); i++ ) {
		_actors[i]->Render();
	}
}

void UWorld::AddActor(AActor* actor) {
	_actors.push_back(actor);
	actor->_owner = this;
}

UTestWorld::UTestWorld() {
	UCubeComponent* comp1 = new UCubeComponent();
	comp1->SetRelativeLocation(FVector(5, 0, 0));

	UCubeComponent* comp2 = new UCubeComponent();
	comp2->SetRelativeLocation(FVector(0, 5, 0));

	UCubeComponent* comp3 = new UCubeComponent();
	comp3->SetRelativeLocation(FVector(0, 0, 5));

	UCameraComponent* cam = new UCameraComponent();
	cam->SetRelativeLocation(FVector(0, 0, 0));
	CRenderer::SetMainCamera(cam);

	AActor* actor = new AActor();
	actor->RegisterComponent(comp1);
	actor->RegisterComponent(comp2);
	actor->RegisterComponent(comp3);
	actor->RegisterComponent(cam);
	AddActor(actor);

	UGridComponent* grid = new UGridComponent();

	actor = new AActor();
	actor->RegisterComponent(grid);
	AddActor(actor);
	
}

void UTestWorld::Update() {
	UWorld::Update();
}

void UTestWorld::Render() {
	UWorld::Render();
}
