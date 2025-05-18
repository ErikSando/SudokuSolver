#ifndef ASSERT_H
#define ASSERT_H

#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#define Assert(expr)
#else
#define Assert(expr)\
if (!expr) {\
    printf("Assert failed: %s - ", #expr);\
    printf("file %s ", __FILE__);\
    printf("line %d\n", __LINE__);\
    printf("on %s ", __DATE__);\
    printf("at %s ", __TIME__);\
    exit(1);\
}
#endif

#endif