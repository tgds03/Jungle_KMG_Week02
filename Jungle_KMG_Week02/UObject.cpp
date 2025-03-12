#include "stdafx.h"
#include "UObject.h"

std::unordered_map<void*, size_t> UObject::_allocationMap = std::unordered_map<void*, size_t>();
uint32 UObject::_nextuuid = 0;
uint32 UObject::_totalCount = 0;
uint32 UObject::_totalMemory = 0;

UObject::UObject() {}

UObject::~UObject() {}

inline void* UObject::operator new(size_t size) {
	void* ptr = ::operator new(size);
	_allocationMap[ptr] = size;
	++_totalCount;
	_totalMemory += size;
	return ptr;
}

inline void UObject::operator delete(void* p) {
	--_totalCount;
	_totalMemory -= _allocationMap[p];
	_allocationMap.erase(p);
	free(p);
}
