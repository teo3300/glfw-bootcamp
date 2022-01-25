#pragma once
#include <stdio.h>

#define NOTHING {}

#define LOG_LEVEL_ERROR     0
#define log_level_error     LOG_LEVEL >= LOG_LEVEL_ERROR
#define LOG_LEVEL_WARNING   1
#define log_level_warning   LOG_LEVEL >= LOG_LEVEL_WARNING
#define LOG_LEVEL_LOG       2
#define log_level_log       LOG_LEVEL >= LOG_LEVEL_LOG
#define LOG_LEVEL_DEBUG     3
#define log_level_debug     LOG_LEVEL >= LOG_LEVEL_DEBUG

#define flog(stream, prefix, message)\
    fprintf(stream, "%s:\t%s\n", prefix, message)

#define fvarlog(stream, prefix, message, value)\
    fprintf(stream, "%s:\t(%p) %s\n", prefix, (void*) value, message)

#define log_error(message) flog(stderr, " ERROR", message)
#define log_error_var(message, value) fvarlog(stderr, "-ERROR:", message, value)

#if log_level_warning
    #define log_warning(message)  flog(stderr, " WARNING", message)
    #define log_warning_var(message, value) fvarlog(stderr, "-WARNING:", message, value)
#else
    #define log_warning(message) NOTHING
    #define log_warning_var(message, value) NOTHING
#endif

#if log_level_log
    #define log_log(message)  flog(stderr, " LOG", message)
    #define log_log_var(message, value) fvarlog(stderr, "-LOG:", message, value)
#else
    #define log_log(message) NOTHING
    #define log_log_var(message, value) NOTHING
#endif

#if log_level_debug
    #define log_debug(message)  flog(stderr, " DEBUG", message)
    #define log_debug_var(message, value) fvarlog(stderr, "-DEBUG", message, value)
#else
    #define log_debug(message) NOTHING
    #define log_debug_var(message, value) NOTHING
#endif

#define requires(value, message) if(!(value)){log_error(message); return 0;}

#define litteral(str)    char* str = #str