#ifndef MOBILE_NODE_H_INCLUDED
#define MOBILE_NODE_H_INCLUDED

#include <iomanip>
#include <ctime>
#include <sstream>

#include "network.h"
#include "message.h"

class MobileNode {
  Network* network = NULL;
  Message * message;
  std::string dataSequence;
  IP_VERSION ip_version;
  char* ip;
  char* port;

public:
  MobileNode(IP_VERSION ip_version_, char* ip_, char* port_);
  ~MobileNode();
  void sendData();
  void receiveData();
  void mainLoop();
  void getNewData();
};

#endif
