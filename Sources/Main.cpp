/* lfSMTPd - LazyFox SMTP daemon
 * Author  : <nbardon@lazyfox.fr>
 * Created : 16 jan 2020
 */

#include "Logger.h"
#include "Server.h"
#include "Config.h"


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
