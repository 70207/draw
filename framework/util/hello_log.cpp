//
//  hello_log.cpp
//  watchMyDraw
//
//  Created by peter chen on 2017/10/8.
//  Copyright © 2017年 chenxiaofei. All rights reserved.
//

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/syslog.h>
#include <stdarg.h>
#include <errno.h>
#include <algorithm>
#include <assert.h>

#include "hello_log.h"
#include "hello_thread.h"

namespace hello{
    Log::Log() : m_level(LOG__DEBUG), m_logFd(0), m_threadID(0),m_logFuncSet(false){
        
    }
    Log::~Log(){
        if(m_logFd){
            int fd = m_logFd;
            m_logFd = 0;
            close(fd);
        }
    }
    
    void Log::setPath(const std::string& path)
    {
        int fd = open(path.c_str(), O_APPEND|O_CREAT|O_WRONLY|O_CLOEXEC, DEFFILEMODE);
        if (fd < 0) {
            fprintf(stderr, "open log file %s failed. errno:%d, error msg: %s\n",
                    path.c_str(), errno, strerror(errno));
            return;
        }
        
        m_logFd = fd;
        m_logPath = path;
    }
    
    const char* g_levelStr[] = {
        "FATAL",
        "ERROR",
        "WARN",
        "INFO",
        "DEBUG",
    };
    
    void Log::setLogLevel(const char* l)
    {
        LogLevel ilevel = LOG__INFO;
        for (size_t i = 0; i < sizeof(g_levelStr)/sizeof(const char*); i++) {
            if (strcasecmp(g_levelStr[i], l) == 0) {
                ilevel = (LogLevel)i;
                break;
            }
        }
        setLogLevel(ilevel);
    }
    
    
    void Log::realLog(int l, const char* file, int line, const char* func, const char* fmt ...)
    {
        if (m_threadID == 0) {
            m_threadID = Thread::getThreadID();
        }
        if( l < 0){
            return;
        }
        
        if (l > m_level) {
            return;
        }
        
        char buffer[4*1024];
        char* p = buffer;
        char* limit = buffer + sizeof(buffer);
        
        struct timeval now_tv;
        gettimeofday(&now_tv, NULL);
        const time_t seconds = now_tv.tv_sec;
        struct tm t;
        localtime_r(&seconds, &t);
        p += snprintf(p, limit - p,
                      "%04d/%02d/%02d-%02d:%02d:%02d.%06d %lx %s %s:%d ",
                      t.tm_year + 1900,
                      t.tm_mon + 1,
                      t.tm_mday,
                      t.tm_hour,
                      t.tm_min,
                      t.tm_sec,
                      static_cast<int>(now_tv.tv_usec),
                      (long)m_threadID,
                      g_levelStr[l],
                      file,
                      line);
        va_list args;
        va_start(args, fmt);
        p += vsnprintf(p, limit-p, fmt, args);
        va_end(args);
        p = std::min(p, limit - 2);
        //trim the ending \n
        while (*--p == '\n') {
        }
        *++p = '\n';
        *++p = '\0';
        int fd = m_logFd == -1 ? 1 : m_logFd;
        if(m_logFuncSet){
            m_logFunc(buffer, p - buffer);
        }
        else{
            int count = ::write(fd, buffer, p - buffer);
            if (count != p-buffer) {
                fprintf(stderr, "write log file %s failed. written %d errmsg: %s\n",
                        m_logPath.c_str(), count, strerror(errno));
            }
        }
        if (l <= LOG__FATAL) {
            syslog(LOG_ERR, "%s", buffer+27);
        }
        if (l == LOG__FATAL) {
            fprintf(stderr, "%s", buffer);
            assert(0);
        }
    }
    
    

}
