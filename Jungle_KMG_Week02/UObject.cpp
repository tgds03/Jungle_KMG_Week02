#include "stdafx.h"
#include "UObject.h"

std::unordered_map<void*, size_t> UObject::_allocationMap = std::unordered_map<void*, size_t>();
uint32 UObject::_nextuuid = 0;
uint32 UObject::_totalCount = 0;
uint32 UObject::_totalMemory = 0;

UObject::UObject() {
	_uuid = _nextuuid++;
}

UObject::~UObject() {}