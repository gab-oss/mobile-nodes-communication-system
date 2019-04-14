#include "network.h"

int main(int argc, char *argv[]) {
  string data;

  Network* network = new Network(IPV4);
  network->bindSocket(argv[1]);

  cout << "Waiting for packets..." << endl;
  while(true) {
    network->receive();
  }

  return 0;
}