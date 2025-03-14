#include "stdafx.h"
#include "UWorld.h"
#include "UCameraComponent.h"
#include "UCubeComponent.h"
#include "UGridComponent.h"
#include "Input.h"
#include "UCameraComponent.h"
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

UTestWorld::UTestWorld(): selected(nullptr) {
	UCubeComponent* comp1 = new UCubeComponent();
	comp1->SetRelativeLocation(FVector(5, 0, 0));
	comp1->SetRelativeRotation(FVector(M_PI / 4, 0, 0));

	UCubeComponent* comp2 = new UCubeComponent();
	comp2->SetRelativeLocation(FVector(0, 5, 0));
	comp2->SetRelativeRotation(FVector(M_PI / 4, M_PI / 4, 0));

	UCubeComponent* comp3 = new UCubeComponent();
	comp3->SetRelativeLocation(FVector(0, 0, 5));

	UCameraComponent* cam = new UCameraComponent();
	cam->SetRelativeLocation(FVector(0, 0, 0));
	CRenderer::SetMainCamera(cam);

	AActor* actor = new AActor();
	actor->RegisterComponent(comp1);
	AddActor(actor);

	actor = new AActor();
	actor->RegisterComponent(comp2);
	AddActor(actor);

	actor = new AActor();
	actor->RegisterComponent(comp3);
	AddActor(actor);

	actor = new AActor();
	actor->RegisterComponent(cam);
	AddActor(actor);

	UGridComponent* grid = new UGridComponent();

	actor = new AActor();
	actor->RegisterComponent(grid);
	AddActor(actor);
	
}

void UTestWorld::Update() {
	UWorld::Update();

	if ( Input::Instance().IsMouseButtonReleased(0) ) {
		int x, y;
		Input::Instance().GetMouseLocation(x, y);
		CRenderer::GetMainCamera()->CreateRayObject(x, y);
		Ray ray = CRenderer::GetMainCamera()->CreateRay(x, y, 100.f);
		AActor* s = nullptr;
		OutputDebugString(L"\n");
		for ( auto actorIter = ActorBegin(); actorIter != ActorEnd(); actorIter++ ) {
			AActor* actor = (*actorIter);
			for ( auto compIter = actor->ComponentBegin(); compIter != actor->ComponentEnd(); compIter++ ) {
				UPrimitiveComponent* sceneComp;
				if ( (sceneComp = dynamic_cast<UPrimitiveComponent*>(*compIter)) && sceneComp->IsRayIntersect(ray) ) {
					OutputDebugString(L"hit\n");
					s = actor;
				}
			}
		}
		selected = s;
	}

}

void UTestWorld::Render() {
	for ( int i = 0; i < _actors.size(); i++ ) {
		if (_actors[i] == selected)
			CRenderer::SetPixelShader("SelectedPixelShader");
		else
			CRenderer::SetPixelShader("PixelShader");
		_actors[i]->Render();
	}
	//UWorld::Render();
}
