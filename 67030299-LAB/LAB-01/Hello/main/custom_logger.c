#include "custom_logger.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "esp_timer.h"   // เอาไว้แสดง timestamp us ตั้งแต่ boot
#include <inttypes.h>   // สำหรับ PRIu64 / PRId64
static clog_level_t s_min_level = CLOG_INFO;

void clog_set_level(clog_level_t level) {
    s_min_level = level;
}

static const char* level_name(clog_level_t lv) {
    switch (lv) {
        case CLOG_ERROR:   return "E";
        case CLOG_WARN:    return "W";
        case CLOG_INFO:    return "I";
        case CLOG_DEBUG:   return "D";
        case CLOG_VERBOSE: return "V";
        default:           return "?";
    }
}

static const char* level_color(clog_level_t lv) {
#if CUSTOM_LOG_USE_COLOR
    switch (lv) {
        case CLOG_ERROR:   return LOG_BOLD(LOG_COLOR_RED);
        case CLOG_WARN:    return LOG_BOLD(LOG_COLOR_YELLOW);
        case CLOG_INFO:    return LOG_BOLD(LOG_COLOR_GREEN);
        case CLOG_DEBUG:   return LOG_BOLD(LOG_COLOR_CYAN);
        case CLOG_VERBOSE: return LOG_BOLD(LOG_COLOR_BLUE);
        default:           return "";
    }
#else
    (void)lv;
    return "";
#endif
}

void clog_print(clog_level_t level, const char* tag, const char* fmt, ...) {
    if (level > s_min_level) return;  // กรองต่ำกว่าระดับที่ตั้งไว้

    // timestamp (ms)
    uint64_t us = esp_timer_get_time();
    uint32_t ms = (uint32_t)(us / 1000ULL);

#if CUSTOM_LOG_USE_COLOR
    const char* color = level_color(level);
    printf("%s[%s] %u ms [%s] ", color, level_name(level), ms, tag);
#else
    printf("[%s] %u ms [%s] ", level_name(level), ms, tag);
#endif

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

#if CUSTOM_LOG_USE_COLOR
    printf(LOG_RESET_COLOR);
#endif
    printf("\n");
}