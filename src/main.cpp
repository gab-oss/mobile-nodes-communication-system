#include "mobile_node.h"

#include <cstring>

int main(int argc, char *argv[]) {
  if(argc != 4) {
    cout << "Usage: " << argv[0] << " (IPV4 | IPV6) address port" << endl;
    return 0;
  }

  IP_VERSION ip_version;

  if(strcmp(argv[1], "IPV4") == 0)
    ip_version = IPV4;
  else if(strcmp(argv[1], "IPV6") == 0)
    ip_version = IPV6;
  else {
    cout << "Allowed protocols: IPV4, IPV6" << endl;
    return 0;
  }

  MobileNode* node = new MobileNode(ip_version, argv[2], argv[3]);

  node->mainLoop();

  return 0;
}