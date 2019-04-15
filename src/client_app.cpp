#include "network.h"

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

  char* ip = argv[2];
  char* port = argv[3];

  Network* network = new Network(ip_version);
  string str;

  cout << "Write data you wish to send" << endl;
  while(true) {
    cout << "> ";
    cin >> str;

    network->sendTo(ip, port, str.c_str(), str.length());
    str.clear();
  }

  return 0;
}