#include "network.h"

#include <cstring>

int main(int argc, char *argv[]) {
  if(argc != 3) {
    cout << "Usage: " << argv[0] << " (IPV4 | IPV6) port" << endl;
    return 0;
  }

  IP_VERSION ip_version;

  if(strcmp(argv[1], "IPV4") == 0)
    ip_version = IPV4;
  else if(strcmp(argv[1], "IPV6") == 0)
    ip_version = IPV6;
  else {
    cout << argv[1] << "Allowed protocols: IPV4, IPV6" << endl;
    return 0;
  }

  char* port = argv[2];

  Network* network = new Network(ip_version);
  network->bindSocket(port);

  cout << "Waiting for packets..." << endl;
  while(true) {
    sockaddr_storage sender;
    size_t length;
    char* data = network->receive(&sender, &length);
    
    if(data != NULL) {
      char* sender_ip = network->printableIpOfSender(sender);
      cout << "Received " << length << " bytes: " << data << " from " << sender_ip << ":" << port << endl;
    }
  }

  return 0;
}