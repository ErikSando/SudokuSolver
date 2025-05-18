#include <stdio.h>

#ifdef WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

int GetTimeMS() {
    #ifdef WIN32
    return GetTickCount();
    #else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
    #endif
}