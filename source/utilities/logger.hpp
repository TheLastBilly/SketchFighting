#ifndef logger_hpp__
#define logger_hpp__

#include <cstdio>
#include <ctime>

#include <iostream>
#include <mutex>

#include "utilities/exceptions.hpp"

#define register_logger()                                                                                                           \
    inline void info(const std::string &msg) {utilities::logger::log(std::string("[") + __FILENAME__ + "] [info] " + msg);}         \
    inline void warning(const std::string &msg) {utilities::logger::log(std::string("[") + __FILENAME__ + "] [warning] " + msg);}   \
    inline void error(const std::string &msg) {utilities::logger::log(std::string("[") + __FILENAME__ + "] [error] " + msg);}

namespace utilities
{
    class logger
    {   
    public:
        static void log(const std::string &msg)
        {
            std::unique_lock<std::mutex> lck(logger_mutex);

            time_t t = time(NULL);
            struct tm* tm = localtime(&t);

            char buf[35] = {0};
            snprintf(buf, 34, "%02d:%02d:%02d", tm->tm_mday, tm->tm_hour, tm->tm_min);

            std::cout << "[" + std::string(buf) + "] " + msg + "\n";
        }

    private:    
        static std::mutex logger_mutex;
    };
}

#endif