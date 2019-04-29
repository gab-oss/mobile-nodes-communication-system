#ifndef MOBILE_NODE_H_INCLUDED
#define MOBILE_NODE_H_INCLUDED

#include "network.h"

class MobileNode {
  Network* network = NULL;
  unsigned char dataSequence = 0;
  IP_VERSION ip_version;
  char* ip;
  char* port;

public:
  MobileNode(IP_VERSION ip_version_, char* ip_, char* port_);
  ~MobileNode();
  void sendData();
  void receiveData();
  void mainLoop();
};

#endif