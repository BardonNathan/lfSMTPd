#ifndef INC_LF_LOGGER
#define INC_LF_LOGGER

/* Set VERBOSE preprocessor to enable Logging
 * Set verbose value (integer) to define logging level.
 *   - 1: Error
 *   - 2: Warning
 *   - 3: Info
 *   - 4: Verbose 
 * 
 *  Define LOG_COLORIZED to enable bash colors
 */

#define VERBOSE 4
#define LOG_COLORIZED

#ifdef VERBOSE
    #include <iostream>
    #define log(x) std::cout << x
    #define logln(x) std::cout << x << std::endl

    #ifdef LOG_COLORIZED 
        #define COLOR_INFO  "\033[34m" <<
        #define COLOR_WARN  "\033[33m" <<
        #define COLOR_ERROR "\033[31m" <<
        #define COLOR_RESET "\033[0m"  <<
    #else
        #define COLOR_WARN
        #define COLOR_ERROR
        #define COLOR_RESET
    #endif


    #if VERBOSE >= 3
        #define logInfo(x) std::cout << COLOR_INFO "[Info] " << x << COLOR_RESET std::endl
    #else
        #define logInfo(x)
    #endif

    #if VERBOSE >= 2
        #define logWarn(x) std::cout << COLOR_WARN "[Warn] " << x << COLOR_RESET std::endl
    #else
        #define logWarn(x)
    #endif

    #if VERBOSE >= 1
        #define logError(x)std::cout << COLOR_ERROR "[Error] " << x << COLOR_RESET std::endl
    #else
        #define logError(x)
    #endif

#else
    #define log(x)
#endif

#endif