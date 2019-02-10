#ifndef AQUAENGINE_UTIL_CLOCK_H
#define AQUAENGINE_UTIL_CLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#elif defined(__linux__)
//#include <sys/time.h>
//#include <unistd.h>
#include <time.h>
#else
#include <time.h>
#endif

typedef struct Clock {
//	#if defined(_WIN32)
//	__int64 start;
//	#elif defined(__linux__)
//	struct timespec start;
//	#else
	clock_t start;
//	#endif
	double DeltaTime;
} Clock;

void Clock_Initialize(Clock* active_clock);
void Clock_TickBegin(Clock* active_clock);
void Clock_TickEnd(Clock* active_clock);
void Clock_Delay(unsigned int ms);

#ifdef __cplusplus
}
#endif

#endif
