#include "stdafx.h"
#include "UActorComponent.h"
#include "AActor.h"

void UActorComponent::AddActor(AActor* actor) {
	_owner->AddActor(actor);
}
