#ifndef INCL_LF_SERVER
#define INCL_LF_SERVER

#include <arpa/inet.h>
//#include <netinet/in.h>
// #include <stdio.h>
//#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
// #include <sys/types.h>
#include <thread>

#include "Logger.h"
#include "SMTPcodes.h"

class Server {

private:
    std::thread* _t = 0;
    int _sfd = 0; // Socket file descriptor
    sockaddr* _sin = 0;
    socklen_t _slen;

    /** Process SMTP routine with a client */
    void handleClient(int &cfd); // cfd = client file descriptor

public:
    /** Create a new socket, bind it and listen for new connections. */
    Server(int port = 25);

    /** Close the server */
    ~Server();

    /** Start the accept thread */
    void start();

    /** Wait until the accept thread is terminated */
    void join();
};


#endif