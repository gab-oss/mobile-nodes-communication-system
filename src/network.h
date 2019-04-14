#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <vector>

using namespace std;

enum IP_VERSION{IPV4, IPV6};

class Network {
  int sock_desc;
  IP_VERSION ip_version; 

public:
  Network(IP_VERSION ip_version_);
  ~Network();
  int bindSocket(string port);
  int receive();
  int sendTo(string ip, string port, string data);
};

#endif