#ifndef MOBILE_NODE_H_INCLUDED
#define MOBILE_NODE_H_INCLUDED

#include "network.h"

#include <boost/uuid/uuid.hpp>            
#include <boost/uuid/uuid_generators.hpp> 
#include <boost/uuid/uuid_io.hpp>    
#include <boost/lexical_cast.hpp>  
#include <string>


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