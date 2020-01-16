/* lfSMTPd - LazyFox SMTP daemon
 * Author  : <nbardon@lazyfox.fr>
 * Created : 16 jan 2020
 */

#include "Logger.h"
#include "Server.h"

int main(int argc, const char** argv) {
	logln("Starting LazyFox SMTP daemon...");
	
	Server s;
	s.start();
	s.join();
}
