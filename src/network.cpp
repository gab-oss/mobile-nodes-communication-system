#include "network.h"

#include <cstring>

Network::Network(IP_VERSION ip_version_) : ip_version(ip_version_) {
  sock_desc = socket(ip_version == IPV4 ? AF_INET : AF_INET6, SOCK_DGRAM, 0);
  if (sock_desc == -1)
    cout << "ERROR: Could not open socket!" << endl;
}

Network::~Network() {
  close(sock_desc);
}

int Network::bindSocket(string port) {
  addrinfo hints;
  addrinfo* result;
  addrinfo* rp;

  memset(&hints, 0, sizeof(addrinfo));
  hints.ai_family = ip_version == IPV4 ? AF_INET : AF_INET6;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;
  hints.ai_protocol = 0;
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  if (getaddrinfo(NULL, port.c_str(), &hints, &result) != 0) {
    cout << "ERROR: Could not get address info!" << endl;
    return -1;
  }

  for (rp = result; rp != NULL; rp = rp->ai_next)
    if (bind(sock_desc, rp->ai_addr, rp->ai_addrlen) == 0)
      break;

  if (rp == NULL) {
    cout << "ERROR: Could not bind socket!" << endl;
    return -1;
  }

  freeaddrinfo(result);

  return 0;
}

int Network::receive() {
  char buf[255];
  memset(buf, 0, sizeof buf);

  if(recvfrom(sock_desc, buf, 255, 0, nullptr, nullptr) == -1) {
    cout << "ERROR: Could not receive packet!" << endl;
    return -1;
  }
  else
    cout << "recv: " << buf << endl;

  return 0;
}

int Network::sendTo(string ip, string port, string data) {
  addrinfo hints;
  addrinfo* result;
  addrinfo* rp;

  memset(&hints, 0, sizeof(addrinfo));
  hints.ai_family = ip_version == IPV4 ? AF_INET : AF_INET6;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;

  if (getaddrinfo(ip.c_str(), port.c_str(), &hints, &result) != 0) {
    cout << "ERROR: Could not get address info!" << endl;
    return -1;
  }

  for (rp = result; rp != NULL; rp = rp->ai_next)
    break;

  if (rp == NULL) {
    cout << "ERROR: Could not find address!" << endl;
    return -1;
  }

  if(sendto(sock_desc, data.c_str(), data.length(), 0, rp->ai_addr, 
            rp->ai_addrlen) == -1)
    cout << "ERROR: Could not send packet!" << endl;

  freeaddrinfo(result);

  return 0;
}