#pragma once
#ifdef PLATFORM_Linux
	#include <time.h>
	typedef timespec HighResTime;
#else
	#include <chrono>
	typedef std::chrono::steady_clock::time_point HighResTime;
#endif

class Time
{
public:
	Time();
	~Time();
	void Start();
	void Update();
	float GetTime();
	float DeltaTime();
	float FPS();

private:
	//Platform abstraction
	HighResTime Now()const;
	HighResTime Diff(const HighResTime &start, const HighResTime &end)const;
	template<typename T>
	T HRTCast(const HighResTime &lhs)const
	{
#ifdef PLATFORM_Linux
		return (T)lhs.tv_sec+((T)lhs.tv_nsec/1000000000);
#else
		return ((T)(std::chrono::duration_cast<std::chrono::nanoseconds>(lhs).count()))*1e-9f;
#endif
	}

	HighResTime begin;
	HighResTime last;
	float m_DeltaTime;
};

