#pragma once
#include "UActorComponent.h"
class UWorld;

class AActor : public UObject {
private:
	TArray<UActorComponent*> _components;
	UWorld* _owner;
	friend class UWorld;
public:
	void RegisterComponent(UActorComponent* comp);
	void AddActor(AActor*);
	void Start();
	void Update();
	void Render();
	void Remove();

	template <typename T>
	T* GetComponent();
};

template<typename T>
inline T* AActor::GetComponent() {
	T* downcast;
	for(auto& comp: _components) {
		if (downcast = dynamic_cast<T>(comp)) {
			return downcast;
		}
	}
	return nullptr;
}
