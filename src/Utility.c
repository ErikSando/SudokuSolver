#include <stdio.h>
#include <stdlib.h>

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

void GetRandomOrder(int* list) {
    for (int i = 0; i < 9; i++) {
        list[i] = i + 1;
    }

    for (int i = 8; i > 0; i--) {
        int j = rand() % (i + 1);
        int _ = list[i];
        list[i] = list[j];
        list[j] = _;
    }
}