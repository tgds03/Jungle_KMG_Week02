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

