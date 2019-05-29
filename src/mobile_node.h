#ifndef MOBILE_NODE_H_INCLUDED
#define MOBILE_NODE_H_INCLUDED

#define MAX_RECENT_UUIDS 5
#define RESEARCH_TIME 4

#include <iomanip>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <list>
#include <time.h>

#include "network.h"
#include "message.h"

class MobileNode {
  bool is_serv;
  Network* network = NULL;
  Message * message;
  std::string dataSequence;
  IP_VERSION ip_version;
  char* ip;
  char* port;
  std::list<std::string> recent_uuids;


public:
  MobileNode(IP_VERSION ip_version_, char* ip_, char* port_, bool is_serv);
  ~MobileNode();
  void sendData();
  void receiveData();
  void mainLoop();
  void getNewData();
};

#endif
