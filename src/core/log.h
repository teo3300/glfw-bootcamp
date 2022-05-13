#pragma once
#include <stdio.h>

// refer to https://www.keil.com/support/man/docs/armcc/armcc_chr1359124965789.htm

#define NOTHING do{}while(0)

#define LEVEL_ERROR     0
#define LEVEL_WARNING   1
#define LEVEL_LOG       2
#define LEVEL_DEBUG     3

#ifndef DLEVEL
    #define DLEVEL LEVEL_ERROR
#endif

#if DLEVEL < LEVEL_ERROR
    #error Please specify a valid debug level (LEVEL_ERROR, LEVEL_WARNING, LEVEL_LOG, LEVEL_DEBUG) or a positive integer
#endif

#define PRINT(__prefix, __format, ...) fprintf(stderr, "["__prefix"]: "__FILE__":%d > "__format"\n", __LINE__, ##__VA_ARGS__)

#if DLEVEL >= LEVEL_ERROR
    #define error(__format, ...) PRINT(" ERROR ", __format, ##__VA_ARGS__)
#else
    #define error(__format, ...) NOTHING
#endif

#if DLEVEL >= LEVEL_WARNING
    #define warning(__format, ...) PRINT("WARNING", __format, ##__VA_ARGS__)
#else
    #define warning(__format, ...) NOTHING
#endif

#if DLEVEL >= LEVEL_LOG
    #define log(__format, ...) PRINT("  LOG  ", __format, ##__VA_ARGS__)
#else
    #define log(__format, ...) NOTHING
#endif

#if DLEVEL >= LEVEL_DEBUG
    #define debug(__format, ...) PRINT(" DEBUG ", __format, ##__VA_ARGS__)
#else
    #define debug(__format, ...) NOTHING
#endif

#define requires(val, __format, ...) do{ if(!(val)){ error(__format, ##__VA_ARGS__); return 0; } }while(0)