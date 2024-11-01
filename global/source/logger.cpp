#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#include "error_debug.h"
#include "logger.h"

typedef struct {
    char          logFileName[128];
    FILE*         logFile;
    enum LogLevel logLevel;
    enum LogMode  logMode;
} logState_t;

static logState_t logger = {.logFileName    = "log.txt",
                            .logFile        = NULL,
                            .logLevel       = L_ZERO,
                            .logMode        = L_TXT_MODE};



static struct tm getTime();
static void logTime();

static struct tm getTime() {
    time_t currentTime = time(NULL);
    struct tm result = *localtime(&currentTime);
    return result;
}

static void logTime() {
    MY_ASSERT(logger.logFile, abort());
    struct tm currentTime = getTime();
    fprintf(logger.logFile, "[%.2d.%.2d.%d %.2d:%.2d:%.2d] ",
        currentTime.tm_mday, currentTime.tm_mon, currentTime.tm_year + 1900,
        currentTime.tm_hour, currentTime.tm_min, currentTime.tm_sec);
}

static enum status constructFileName(const char *fileName) {
    strcpy(logger.logFileName, "logs/");
    if (fileName != NULL && strlen(fileName) > 0) {
        if (strchr(fileName, '/') != NULL) {
            fprintf(stderr, "Making folders isn't supported\n");
            return ERROR;
        }

        const char *lastDot = strrchr(fileName, '.');
        if (lastDot != NULL)
            strncat(logger.logFileName, fileName, lastDot - fileName);
        else
            strcat(logger.logFileName, fileName);

    } else
        strcat(logger.logFileName, "log");

    if (logger.logMode == L_TXT_MODE)
        strcat(logger.logFileName, ".txt");
    else if (logger.logMode == L_HTML_MODE)
        strcat(logger.logFileName, ".html");

    return SUCCESS;
}

enum status logOpen(const char *fileName, enum LogMode mode) {
    system("mkdir -p logs");

    logger.logMode = mode;
    if ((mode != L_TXT_MODE) && (mode != L_HTML_MODE)) {
        fprintf(stderr, "Unknown logging mode\n");
        return ERROR;
    }

    if (constructFileName(fileName) != SUCCESS)
        return ERROR;

    logger.logFile = fopen(logger.logFileName, "w");
    if (!logger.logFile) return ERROR;

    if (mode == L_HTML_MODE)
        fprintf(logger.logFile, "<pre>");

    fprintf(logger.logFile, "------------------------------------------\n");
    logTime();
    fprintf(logger.logFile, "Starting logging session\n");
    return SUCCESS;
}

enum status logDisableBuffering() {
    if (!logger.logFile) return ERROR;
    setbuf(logger.logFile, NULL); //disabling buffering
    return SUCCESS;
}

enum status logClose() {
    if (!logger.logFile) return ERROR;


    logTime();
    fprintf(logger.logFile, "Ending logging session \n");
    fprintf(logger.logFile, "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");

    if (logger.logMode == L_HTML_MODE)
        fprintf(logger.logFile, "</pre>");
    fclose(logger.logFile);

    return SUCCESS;
}

void setLogLevel(enum LogLevel level) {
    logger.logLevel = level;
}

enum LogLevel getLogLevel() {
    return logger.logLevel;
}

enum status logPrintWithTime(enum LogLevel level, bool copyToStderr, const char* fmt, ...) {
    MY_ASSERT(logger.logFile, abort());
    if (level > logger.logLevel)
        return SUCCESS;

    va_list args;

    if (copyToStderr) {
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
    }
    va_start(args, fmt);
    logTime();
    vfprintf(logger.logFile, fmt, args);

    va_end(args);
    return SUCCESS;
}

enum status logPrint(enum LogLevel level, bool copyToStderr, const char* fmt, ...) {
    MY_ASSERT(logger.logFile, abort());
    if (level > logger.logLevel)
        return SUCCESS;

    va_list args;

    if (copyToStderr) {
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
    }
    va_start(args, fmt);
    vfprintf(logger.logFile, fmt, args);

    va_end(args);
    return SUCCESS;
}

