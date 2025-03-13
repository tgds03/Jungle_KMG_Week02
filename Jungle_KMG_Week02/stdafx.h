#pragma once

#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <d3d11.h>
#include <d3dcompiler.h>
#include <comdef.h>
#include <dxgidebug.h>

#include <fstream>
#include <assert.h>
#include <Windows.h>

#include <vector>
#include <list>
#include <unordered_map>
#include <functional>
#include <string>
#include <sstream>
template <typename T> using TArray = std::vector<T>;
template <typename T> using TLinkedList = std::list<T>;
template <typename K, typename V> using TMap = std::unordered_map<K, V>;
using int32 = int;
using uint32 = unsigned int;
using FString = std::string;
using FWString = std::wstring;

#include "FVector.h"
#include "FMatrix.h"
#define M_PI           3.14159265358979323846

#define _COL_MAJOR_SYSTEM
//#define SCR_WIDTH 1200
//#define SCR_HEIGHT 800

extern int SCR_WIDTH;
extern int SCR_HEIGHT;

template <typename T> inline void SafeRelease(T*& ppT) {
	if ( ppT ) {
		ppT->Release();
		ppT = nullptr;
	}
}

template <typename T> inline void SafeDelete(T*& ppT) {
	if ( ppT ) {
		delete ppT;
		ppT = nullptr;
	}
}

inline double degToRad(double deg) { return deg * M_PI / 180.f; }
inline double radToDeg(double rad) { return rad * 180.f / M_PI; }

//template <typename T> inline void SafeDelete(T** ppT) {
//	if ( *ppT ) {
//		delete *ppt;
//		*ppT = nullptr;
//	}
//}