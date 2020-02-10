#ifndef INCL_LF_CONFIG
#define INCL_LF_CONFIG

#include "Logger.h"
#include <sstream>
#include <string>
#include <fstream>
#include <list>
//#include <cstdlib>

#define EXITCODE_ERR_OPNFILE -1
#define EXITCODE_DEFAULT_CONF_CREATED -2

/** Structure to store running configuration */
struct RunningConfig {
    char *hostname = NULL;
    int port;
    int timeout;
    int maxMessageSize;

    int motdDelay;
    int motqDelay;
    std::list<std::string> motd;
    std::list<std::string> motq;
};

extern RunningConfig Config;

int parseConfig(const char *filename);
int createDefaultConfig(const char *filename);
int initConfig(const char *filename);

#endif