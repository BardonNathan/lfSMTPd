/* lfSMTPd - LazyFox SMTP daemon
 * Author  : <nbardon@lazyfox.fr>
 * Created : 16 jan 2020
 */

#include "Logger.h"
#include "Server.h"

// Config parser
#include <sstream>
#include <string>
#include <fstream>
#include <list>
//#include <cstdlib>

#define EXITCODE_ERR_OPNFILE          -1
#define EXITCODE_DEFAULT_CONF_CREATED -2


/* ============================================================
 *  Config parser
 *  -------------
 */

/** Structure to store running configuration */
struct {
	char* hostname;
	int port;
	int timeout;
	int maxMessageSize;

	int motdDelay;
	int motqDelay;
	std::list<std::string> motd;
	std::list<std::string> motq;
} Config;

/** Parse configuration from filename.
  * @arg filename : path to configuration file
  * @return 0 on success or EXITCODE_*
  */
int parseConfig(const char* filename) {
	logInfo("Reading configuration " << filename << "... ");

    std::string line;
    std::ifstream file(filename, std::ifstream::in);

	if (!file)
		return EXITCODE_ERR_OPNFILE;

    while (std::getline(file, line)) {
        std::istringstream is_line(line);
        std::string key;
    
	    if (std::getline(is_line, key, '=')) {
            std::string value;
            if (std::getline(is_line, value)) {
				if (key == "port")
					Config.port = std::stoi(value);
				
				else if (key == "hostname")
					Config.hostname = const_cast<char*>(value.c_str());
				
				else if (key == "timeout")
					Config.timeout = std::stoi(value);

				else if (key == "motdDelay")
					Config.motdDelay = std::stoi(value);
					
				else if (key == "motqDelay")
					Config.motqDelay = std::stoi(value);
				
				else if (key == "maxMessageSize")
					Config.maxMessageSize = std::stoi(value);

				else if (key == "motd")
					Config.motd.push_back(value);

				else if (key == "motq")
					Config.motq.push_back(value);

				else
					log('\'' << key << "' = '" << value << '\'');
			}
        }
    }

	logIlSuccess("Done");

	return 0;
}

/**	Set default configuration and save it to filename.
  * @arg filename : path to configuration file
  * @return 0 on success or EXITCODE_*
  */
int createDefaultConfig(const char* filename) {
	logInfo("Writting default configuration... ");

	Config.hostname = const_cast<char *>("your.top.level.domain");
	Config.port = 25;
	Config.timeout = 3000;

	Config.maxMessageSize = 4194304;

	Config.motd = std::list<std::string>(1, "Hello");
	Config.motq = std::list<std::string>(1, "Bye");
	Config.motdDelay = 0;
	Config.motqDelay = 0;

	time_t now = time(0);

	std::ofstream fs(filename, std::ofstream::out);
	if (!fs)
		return EXITCODE_ERR_OPNFILE;

	fs << "# lfSMTPd configuration file" << std::endl << 
		  "# Generated " << ctime(&now)  << std::endl;

	fs << "port="           << Config.port           << std::endl;
	fs << "hostname="       << Config.hostname       << std::endl;
	fs << "timeout="        << Config.timeout        << std::endl;
	fs << "maxMessageSize=" << Config.maxMessageSize << std::endl;
	fs << "motdDelay="      << Config.motdDelay      << std::endl;
	fs << "motqDelay="      << Config.motqDelay      << std::endl;

	std::list<std::string>::iterator it;
	for (it = Config.motd.begin(); it != Config.motd.end(); ++it)
		fs << "motd=" << *it << std::endl;
  

	for (it = Config.motq.begin(); it != Config.motq.end(); ++it)
		fs << "motq=" << *it << std::endl;
	

	fs.close();

	logIlSuccess("Done");

	return 0;
}

/** Initialize configuration.
  * Parse it and or create default configuration on fail.
  *
  * @arg filename Path to configuration file
  * @return EXITCODE_DEFAULT_CONF_CREATED, return of parseConfig(const char*) or 0 on success.
  * @see parseConfig(const char*)
  */
int initConfig(const char* filename) {
	int parseResult = parseConfig(filename);
	if (parseResult == EXITCODE_ERR_OPNFILE) {
		logIlWarn(" Failed");

		parseResult = createDefaultConfig(filename);
		if (parseResult != 0) {
			logError("Unable to create '" << filename << "' with default configuration");
			return parseResult;
		}

		return EXITCODE_DEFAULT_CONF_CREATED;
	}
	else if (parseResult != 0)
		return parseResult;
	
	return 0;
}

/* ============================================================
 *  Main function
 *  --------------
 */

int main(int argc, const char** argv) {
	log("Starting LazyFox SMTP daemon...");
	

	int cfgResult = initConfig("config.cfg");
	if (cfgResult == EXITCODE_DEFAULT_CONF_CREATED) {
		cfgResult = initConfig("config.cfg");
		if (cfgResult != 0) {
			logError("Unable to load default configuration");
			return cfgResult;
		}
		logSuccess("Default configuration loaded");
	} else if (cfgResult != 0) {
		logError("Unable to load configuration");
		return cfgResult;
	} else 
		logSuccess("Configuration loaded");
	
	Server s(Config.port);
	s.start();

	s.join();

	logln();
}
