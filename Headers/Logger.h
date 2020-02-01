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
    #define logIl(x) std::cout << x << std::flush
    #define log(x) std::cout << std::endl << x << std::flush
    #define logln() std::cout << std::endl

    #ifdef LOG_COLORIZED 
        #define COLOR_INFO    "\033[34m" <<
        #define COLOR_SUCCESS "\033[32m" <<
        #define COLOR_WARN    "\033[33m" <<
        #define COLOR_ERROR   "\033[31m" <<
        #define COLOR_RESET   "\033[0m"  <<
    #else
        #define COLOR_INFO
        #define COLOR_SUCCESS
        #define COLOR_WARN
        #define COLOR_ERROR
        #define COLOR_RESET
    #endif


    #if VERBOSE >= 3
        #define logInfo(x) std::cout << std::endl << COLOR_INFO "[ Info  ] " << x << COLOR_RESET std::flush
        #define logIlInfo(x) std::cout << COLOR_INFO x << COLOR_RESET std::flush

        #define logSuccess(x) std::cout << std::endl << COLOR_SUCCESS "[Success] " << x << COLOR_RESET std::flush
        #define logIlSuccess(x) std::cout << COLOR_SUCCESS x << COLOR_RESET std::flush
    #else
        #define logInfo(x)
        #define logIlInfo(x)
        
        #define logSuccess(x)
        #define logIlSuccess(x)
    #endif

    #if VERBOSE >= 2
        #define logWarn(x) std::cout << std::endl << COLOR_WARN "[Warning] " << x << COLOR_RESET std::flush
        #define logIlWarn(x) std::cout << COLOR_WARN x << COLOR_RESET std::flush
    #else
        #define logWarn(x)
        #define logIlWarn(x)
    #endif

    #if VERBOSE >= 1
        #define logError(x) std::cout << std::endl << COLOR_ERROR "[ Error ] " << x << COLOR_RESET std::flush
        #define logIlError(x) std::cout << COLOR_ERROR x << COLOR_RESET std::flush
    #else
        #define logError(x)
        #define logIlError(x)
    #endif

#else
    #define log(x)
#endif

#endif