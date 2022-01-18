#pragma once
#include <stdio.h>

#define LOG_LEVEL_ERROR     0
#define LOG_LEVEL_WARNING   1
#define LOG_LEVEL_LOG       2
#define LOG_LEVEL_DEBUG     3

#define flog(stream, prefix, message)\
    fprintf(stream, "%s:\t%s\n", prefix, message)

#define log_error(message) flog(stderr, "ERROR", message)

#if LOG_LEVEL >= LOG_LEVEL_WARNING
    #define log_warning(message)  flog(stderr, "WARNING", message)
#else
    #define log_warning(message) 
#endif

#if LOG_LEVEL >= LOG_LEVEL_LOG
    #define log_log(message)  flog(stderr, "LOG", message)
#else
    #define log_log(message) 
#endif

#if LOG_LEVEL >= LOG_LEVEL_DEBUG
    #define log_debug(message)  flog(stderr, "DEBUG", message)
#else
    #define log_debug(message) 
#endif

#define requires(value, message) if(!(value)){log_error(message); return 0;}

#define litteral(str)    char* str = #str