#pragma once
template <typename T>
class ISingleton {
public:
	static T& Instance() {
		static T _instance;
		return _instance;
	}

protected:
	ISingleton() = default;
	virtual ~ISingleton() = default;
	ISingleton(const ISingleton&) = delete;
	ISingleton& operator=(const ISingleton&) = delete;
	ISingleton(ISingleton&&) = delete;
	ISingleton& operator=(ISingleton&&) = delete;
};