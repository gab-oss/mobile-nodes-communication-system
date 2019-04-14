#include "network.h"

int main(int argc, char *argv[]) {
  string data;

  Network* network = new Network(IPV4);

  cout << "Write data you wish to send" << endl;
  while(true) {
    cout << "> ";
    cin >> data;

    network->sendTo(argv[1], argv[2], data);
    data.clear();
  }

  return 0;
}