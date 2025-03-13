#pragma once
class UObject {
private:
	static uint32 _nextuuid;
	static TMap<void*, size_t> _allocationMap;
	static uint32 _totalCount;
	static uint32 _totalMemory;

private:
	uint32 _uuid;
public:
	UObject();
	virtual ~UObject();
	void* operator new(size_t size);
	void operator delete(void* p);

	inline bool operator==(const UObject& rhs) const {
		return _uuid == rhs._uuid;
	}

	uint32 GetUUID() { return _uuid; }
};

inline void* UObject::operator new(size_t size) {
	void* ptr = ::operator new(size);
	_allocationMap[ptr] = size;
	++_totalCount;
	_totalMemory += static_cast<uint32>(size);
	return ptr;
}

inline void UObject::operator delete(void* p) {
	--_totalCount;
	_totalMemory -= static_cast<uint32>(_allocationMap[p]);
	_allocationMap.erase(p);
	free(p);
}
