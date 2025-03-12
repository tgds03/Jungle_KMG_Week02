#pragma once
#include "Windows.h"
#include "ISingleton.h"
class Time :public ISingleton<Time> {
private:
	double _deltaTime;
	double _elapsedTime;
	LARGE_INTEGER _frequency, _startTime, _frameUpdateTime, _frameEndTime;
public:
	void Init();
	static double GetDeltaTime() { return Instance()._deltaTime; }
	static double GetElapsedTime() { return Instance()._elapsedTime; }
	void _query_frame_update_time();
	void _query_frame_end_time();
};



