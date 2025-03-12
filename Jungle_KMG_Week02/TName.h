#pragma once
class TName {
private:
	static TMap<FString, uint32> names;
	static uint32 count;

	FString name;
public:
	TName() {};
	TName(FString name);
	TName(const TName& other) = default;
	TName& operator=(const TName& other) = default;
	bool operator==(const TName& name) const;

	friend struct std::hash<TName>;
};

namespace std {
	template <>
	struct hash<TName> {
		size_t operator()(const TName& t) const {
			hash<string> hash_func;
			return hash_func(t.name);
		}
	};
}