// custom_logger.h
#pragma once

#include <stdint.h>

// Enable color by default; can be overridden before include
#ifndef CUSTOM_LOG_USE_COLOR
#define CUSTOM_LOG_USE_COLOR 1
#endif

#define LOG_COLOR_BLACK   "30"
#define LOG_COLOR_RED     "31"
#define LOG_COLOR_GREEN   "32"
#define LOG_COLOR_YELLOW  "33"
#define LOG_COLOR_BLUE    "34"
#define LOG_COLOR_PURPLE  "35"
#define LOG_COLOR_CYAN    "36"

#define LOG_BOLD(COLOR)  "\033[1;" COLOR "m"
#define LOG_RESET_COLOR  "\033[0m"

typedef enum {
    CLOG_ERROR = 0,
    CLOG_WARN  = 1,
    CLOG_INFO  = 2,
    CLOG_DEBUG = 3,
    CLOG_VERBOSE = 4,
} clog_level_t;

void clog_set_level(clog_level_t level);
void clog_print(clog_level_t level, const char* tag, const char* fmt, ...);