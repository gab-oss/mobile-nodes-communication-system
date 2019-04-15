#include "network.h"

#include <cstring>

void ipv6_to_str_unexpanded(char * str, const struct in6_addr * addr) {
   sprintf(str, "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
                 (int)addr->s6_addr[0], (int)addr->s6_addr[1],
                 (int)addr->s6_addr[2], (int)addr->s6_addr[3],
                 (int)addr->s6_addr[4], (int)addr->s6_addr[5],
                 (int)addr->s6_addr[6], (int)addr->s6_addr[7],
                 (int)addr->s6_addr[8], (int)addr->s6_addr[9],
                 (int)addr->s6_addr[10], (int)addr->s6_addr[11],
                 (int)addr->s6_addr[12], (int)addr->s6_addr[13],
                 (int)addr->s6_addr[14], (int)addr->s6_addr[15]);
}

IP_VERSION ip_version = IPV6;

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
      //ipv6_to_str_unexpanded(ip6, &((sockaddr_in6*)&from)->sin6_addr);
      char* sender_ip = network->printableIpOfSender(sender);
      cout << "Received " << length << " bytes: " << data << " from " << sender_ip << ":" << port << endl;
    }
  }

  return 0;
}