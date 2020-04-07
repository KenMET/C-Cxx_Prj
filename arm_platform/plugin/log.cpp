// Copyright [2019] <Cgutech>
//  Created by cgutech on 18-10-31.
//

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <dirent.h>
#include <sys/statfs.h>
#include <sys/stat.h>
#include <cstdint>
#include <iostream>
#include <set>
#include <queue>
#include <string>
#include "log.h"

#if defined(SPDLOG)

#elif defined(EASYLOGGINGXX)
#include "easylogging/easylogging++.h"

const __uint32_t LOG_DATA_BUFFER_SIZE (1024 * 40);

char buffer[LOG_DATA_BUFFER_SIZE] = { 0 };
char message[LOG_DATA_BUFFER_SIZE]{ 0 };

const char B2H[] = {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F'
};

pthread_mutex_t _oMutex = PTHREAD_MUTEX_INITIALIZER;

void CopyFile(const char* src, const char* dst) {
    FILE *in, *out;
    if ((in = fopen(src, "rb")) == NULL) {
        return;
    }
    if ((out = fopen(dst, "wb")) == NULL) {
        fclose(in);
        return;
    }

    char buffer[1024] = {0};
    size_t len = 0;
    while ((len = fread(buffer, 1, 1024, in)) > 0) {
        fwrite(buffer, 1, len, out);
    }
    fclose(in);
    fclose(out);
}

int _rollIndex = 0;
//std::queue<std::string> q_filename;
static void defaultPreRollOutCallback(const char* fileName, std::size_t size) {
    if (size > 0) {
        /*
        char filePath[260] = { 0 };
        sprintf(filePath, "%s.%d", fileName, ++_rollIndex);
        std::cout << filePath << std::endl;
        if (MAX_LOG_NUM == _rollIndex) {
            _rollIndex = 0;
        }
        // CopyFile(fileName, filePath);
        // rename(fileName, filePath);

        while ((int)q_filename.size() > MAX_LOG_NUM) {
            remove(q_filename.front().c_str());
            q_filename.pop();
        }
        q_filename.push(fileName);
        */
        diskSpace();
    }
}

int BytesToHexString(const uint8_t * src, int len, char* dst, int dstsize) {
    if (NULL == src || NULL == dst) {
        return 0;
    }

    int l, h, i = 0;

    if (dstsize < len * 2) {
        len = (dstsize - 1) / 2;
    }
    for (i = 0 ; i < len; i++) {
        if (i == 0x20e) {
            i = 0x20e;
            //auto d = src[i];
        }
        h = (src[i] >> 4) & 0x0F;
        l = src[i] & 0x0F;
        dst[2 * i] = B2H[h];
        dst[2 * i + 1] = B2H[l];
    }
    dst[2 * i] = '\0';
    return len * 2;
}

void easy_log_loadconfig(const char* fileName) {
    el::Configurations conf(fileName);

    el::Loggers::reconfigureLogger("default", conf);
    el::Loggers::reconfigureAllLoggers(conf);
    el::Helpers::installPreRollOutCallback(defaultPreRollOutCallback);
}


void easy_log_write(int lv, const char * fmt, ...) {
    pthread_mutex_lock(&_oMutex);

    va_list arg;
    va_start(arg, fmt);
    vsnprintf(buffer, LOG_DATA_BUFFER_SIZE - 1, fmt, arg);
    va_end(arg);

    switch (lv) {
        case LV_TRACE: {  LOG(TRACE) << buffer; break;}
        case LV_DEBUG: {  LOG(DEBUG) << buffer; break;}
        case LV_INFO: { LOG(INFO) << buffer; break;}
        case LV_WARN: {  LOG(WARNING) << buffer; break;}
        case LV_ERROR: {  LOG(ERROR) << buffer; break;}
        case LV_FATAL: {  LOG(FATAL) << buffer; break;}
        default: { LOG(INFO) << buffer; break;}
    }
    pthread_mutex_unlock(&_oMutex);
}

void easy_log_write_hex(int lv, const uint8_t* data, uint32_t len, const char* fmt, ...) {
    pthread_mutex_lock(&_oMutex);

    char hex[len * 2 + 1] = { 0 };
    BytesToHexString(data, len, hex, sizeof(hex));
    va_list arg;
    va_start(arg, fmt);
    vsnprintf(buffer, LOG_DATA_BUFFER_SIZE - 1, fmt, arg);
    va_end(arg);

    snprintf(message, LOG_DATA_BUFFER_SIZE - 1, "%s - %s", buffer, hex);

    switch (lv) {
        case LV_TRACE: {  LOG(TRACE) << message; break;}
        case LV_DEBUG: {  LOG(DEBUG) << message; break;}
        case LV_INFO: { LOG(INFO) << message; break;}
        case LV_WARN: {  LOG(WARNING) << message; break;}
        case LV_ERROR: {  LOG(ERROR) << message; break;}
        case LV_FATAL: {  LOG(FATAL) << message; break;}
        default: { LOG(INFO) << message; break;}
    }
    pthread_mutex_unlock(&_oMutex);
}

__uint64_t get_disk_free_space(const char * path) // MB
{
    struct statfs diskInfo;
    statfs(path, &diskInfo);
    __uint64_t blocksize = diskInfo.f_bsize;                  //  Ã¿¸öblockÀï°üº¬µÄ×Ö½ÚÊý
    //__uint64_t totalsize = blocksize * diskInfo.f_blocks;     //  ×ÜµÄ×Ö½ÚÊý£¬f_blocksÎªblockµÄÊýÄ¿

    //__uint64_t freeDisk = diskInfo.f_bfree * blocksize;      //  Ê£Óà¿Õ¼äµÄ´óÐ¡
    __uint64_t availableDisk = diskInfo.f_bavail * blocksize; //  ¿ÉÓÃ¿Õ¼ä´óÐ¡
    return availableDisk;
}


void diskSpace() {
    char path[128] = "/home/root/logs";
    __uint64_t availableDisk = get_disk_free_space(path);
    printf("avaliableDisk %f\n", (availableDisk / MB));
    if ((availableDisk / MB) <= MIN_DISK_SPACE) {
        removeFile(path);
    }
}

void removeFile(char * path) {
    std::set<std::string> s_file;
    std::set<std::string> s_dir;
    struct dirent * dirt = NULL;
    DIR * pDir, * subDir;
    pDir = opendir(path);
    //char filename[100] = {0};
    while (NULL != (dirt=readdir(pDir))) {
        if (!strcmp(dirt->d_name, ".") || !strcmp(dirt->d_name, "..")) {
            continue;
        }
        if (dirt->d_type == 4) {
            s_dir.insert(dirt->d_name);
        }
    }
    std::cout << "Dir Count: " << s_dir.size() << std::endl;
    for (auto it = s_dir.begin(); it != s_dir.end(); ++it) {
        char dirpath[512] = {0};
        sprintf(dirpath, "%s/%s", path, (*it).c_str());
        subDir = opendir(dirpath);
        printf("Open dir %s\n", dirpath);
        while (NULL != (dirt=readdir(subDir))) {
            if (!strcmp(dirt->d_name, ".") || !strcmp(dirt->d_name, "..")) {
                continue;
            }
            if (dirt->d_type == 8) {
                if (!strcmp(dirt->d_name, "error")) {
                    continue;
                }
                s_file.insert(dirt->d_name);
            }
        }
        // printf("after while 2 dir [%s], size [%ld]\n", (*it).c_str(), s_file.size());
        int delNum = s_file.size();
        auto it2 = s_file.begin();
        // printf("delNum [%d]", delNum);
        for (int i = 0; i < delNum; ++it2, ++i) {
            char delFilename[512] = {0};
            sprintf(delFilename, "%s/%s", dirpath, (*it2).c_str());
            if (0 == remove(delFilename)) {
                printf("del file[%s]\n", (*it2).c_str());
            } else {
                perror(" fail to remove");
            }
        }
        if (0 == remove(dirpath)) {
            printf("del Path[%s]\n", dirpath);
        } else {
            perror(" fail to remove");
        }
        // printf("after while 2 dir [%s], size [%ld]\n", (*it).c_str(), s_file.size());
        s_file.clear();
        // printf("after clear dir [%s], size [%ld]\n", (*it).c_str(), s_file.size());
        __uint64_t availableDisk = get_disk_free_space(path);
        printf("del avaliableDisk %f\n", (availableDisk / MB));
        if ((availableDisk / MB) > MIN_DISK_SPACE) {
            break;
        }

    }
}


#else   // non-thread-safe

#endif

