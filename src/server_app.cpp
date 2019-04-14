#include "network.h"

int main(int argc, char *argv[]) {
  Network* network = new Network(IPV4);
  network->bindSocket(argv[1]);

  cout << "Waiting for packets..." << endl;
  while(true) {
    size_t length;
    char* data = network->receive(&length);
    if(data != NULL);
      cout << "Received " << length << " bytes: " << data << endl;
  }

  return 0;
}