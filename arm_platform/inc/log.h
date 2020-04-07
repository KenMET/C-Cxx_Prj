//
// Created by ken on 19-08-03.
//

#ifndef __LOG_H__
#define __LOG_H__

#include <iostream> 
#include <cstring>
using namespace std;

//#define EASYLOGGINGXX

#if defined(SPDLOG)

#elif defined(EASYLOGGINGXX)

#define KB 1024.0                                               //  2^10
#define MB 1048576.0                                        //  2^20
#define GB 1073741824.0      

#define MAX_LOG_NUM 50
#define MIN_DISK_SPACE 1000 //MB

void easy_log_loadconfig(const char* fileName);
void easy_log_write(int lv,  const char* fmt, ...);
void easy_log_write_hex(int lv, const uint8_t* data, uint32_t len, const char* fmt, ...);
void removeFile(char * path);
void diskSpace();

enum LOG_LEVEL { LV_TRACE, LV_DEBUG, LV_INFO, LV_WARN, LV_ERROR, LV_FATAL};
#define LOG_TRACE(FMT, ...) easy_log_write(LV_TRACE, FMT, ##__VA_ARGS__)
#define LOG_DEBUG(FMT, ...) easy_log_write(LV_DEBUG, FMT, ##__VA_ARGS__)
#define LOG_INFO(FMT, ...) easy_log_write(LV_INFO, FMT, ##__VA_ARGS__)
#define LOG_WARN(FMT, ...) easy_log_write(LV_WARN, FMT, ##__VA_ARGS__)
#define LOG_ERROR(FMT, ...) easy_log_write(LV_ERROR, FMT, ##__VA_ARGS__)
#define LOG_FATAL(FMT, ...) easy_log_write(LV_FATAL, FMT, ##__VA_ARGS__)

#else   // non-thread-safe
#define LOG_ERROR(...)      do{printf("[\033[1;31;40mError\033[0m]:");printf(__VA_ARGS__);printf("\n");}while(0)
#define LOG_WARN(...)       do{printf("[\033[1;34;40mWarn\033[0m]:");printf(__VA_ARGS__);printf("\n");}while(0)
#define LOG_DEBUG(...)      do{printf("[\033[1;33;40mDebug\033[0m]:");printf(__VA_ARGS__);printf("\n");}while(0)
#define LOG_TRACE(...)      do{printf("[\033[1;32;40mTrace\033[0m]:");printf(__VA_ARGS__);printf("\n");}while(0)
#endif


#endif //__LOG_H__
