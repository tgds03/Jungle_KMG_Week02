#pragma once
#include "UObject.h"
class AActor;
class UActorComponent: public UObject {
	friend class AActor;
	AActor* _owner;
public:
	void AddActor(AActor*);
	template<typename T>
	T* GetComponent();
	virtual void Start() abstract;
	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void Remove() abstract;
	inline AActor* GetActor() {
		return _owner;
	};
};

template<typename T>
inline T* UActorComponent::GetComponent() {
	if ( _owner == nullptr )
		return nullptr;
	return _owner->template GetComponent<T>();
}
