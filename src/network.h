#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <vector>

#define BUF_SIZE 256

using namespace std;

enum IP_VERSION{IPV4, IPV6};

class Network {
  int sock_desc;
  IP_VERSION ip_version;

public:
  Network(IP_VERSION ip_version_);
  ~Network();

  // binds socket to PORT so it can listen and receive packets from outside coming to this port
  int bindSocket(string port);
  // receives incoming packet and returns a pointer to data, saves its LENGTH if passed, need to call bindSocket() first
  char* receive(sockaddr_storage* from, size_t* length = NULL);
  // send a packet with DATA of SIZE to given IP on given PORT
  int sendTo(string ip, string port, const char* data, size_t size);
  // returns string with printable ip (either v4 or v6) of SENDER
  char* printableIpOfSender(sockaddr_storage &sender);
};

#endif
