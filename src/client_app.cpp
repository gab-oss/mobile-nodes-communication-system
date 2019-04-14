#include "network.h"

int main(int argc, char *argv[]) {
  string str;

  Network* network = new Network(IPV4);

  cout << "Write data you wish to send" << endl;
  while(true) {
    cout << "> ";
    cin >> str;

    network->sendTo(argv[1], argv[2], str.c_str(), str.length());
    str.clear();
  }

  return 0;
}