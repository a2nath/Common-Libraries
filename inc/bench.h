#pragma once
#include <chrono>

struct Bench
{
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	std::chrono::steady_clock::time_point mark_time;
	long long delta;

	inline auto get()
	{
		return delta;
	}

	inline void bench_start()
	{
		begin = std::chrono::steady_clock::now();
		mark_time = begin;
	}

	inline void mark()
	{
		delta = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - mark_time).count();
		mark_time = std::chrono::steady_clock::now();
	}

	inline void bench_stop()
	{
		end = std::chrono::steady_clock::now();
		delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	}

	Bench() : delta(0) {}
};
