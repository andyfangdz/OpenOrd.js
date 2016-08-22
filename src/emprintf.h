//
// Created by Andy Fang on 8/18/16.
//

#ifndef EMPRINTF_H
#define EMPRINTF_H

#include <stdio.h>
#include <stdarg.h>
#include <sstream>
#include <string>
#include <emscripten/emscripten.h>
#include <iostream>

#define MAX_MSG_LEN 1000

/* NOTE: Don't pass format strings that contain single quote (') or newline
* characters. */
static void emprintf(const char *format, ...) {
    char msg[MAX_MSG_LEN];
    char consoleMsg[MAX_MSG_LEN + 16];
    va_list args;

    /* create the string */
    va_start(args, format);
    vsnprintf(msg, MAX_MSG_LEN, format, args);
    va_end(args);

    /* wrap the string in a console.log('') statement */
    snprintf(consoleMsg, MAX_MSG_LEN + 16, "console.log('%s')", msg);

    /* send the final string to the JavaScript console */
    emscripten_run_script(consoleMsg);
}

class emstream : public std::stringstream {
public:

    std::string buffer{};
    void flush() {
        auto str = buffer;
        if (!str.empty()) {
            auto pos = str.find_first_of('\n');
            if (pos == -1) {
                emprintf("%s", str.c_str());
                str.clear();
            } else {
                auto should_commit = str.substr(0, pos - 1);
                auto left = str.substr(pos, std::string::npos);
                emprintf("%s", *should_commit.c_str());
                this->str(left);
                flush();
            }
            
        }
    }

    template <typename T>
    emstream& operator<<( T &other )
    {
        
        buffer += std::to_string(other);
        emprintf("%s", buffer.c_str());
        return *this;
    }

    emstream& operator<<( const char *other )
    {
        
        buffer += other;
        return *this;
    }

    emstream& operator<<( std::ostream&(*f)(std::ostream&) )
    {
        buffer += "\n";
        flush();
        return *this;
    }


    ~emstream() {
        flush();
    }
};

emstream emcout;

#endif  /* EMPRINTF_H */
