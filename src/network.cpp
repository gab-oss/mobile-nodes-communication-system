#include "network.h"

#include <cstring>
#include <unistd.h>
#include <fcntl.h>

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

  // sets file descriptor flag for recvfrom() to be non-blocking
  int flags = fcntl(sock_desc, F_GETFL);
  // TODO: change '04000' to 'O_NONBLOCK' from <fcntl.h>
  flags |= O_NONBLOCK;
  fcntl(sock_desc, F_SETFL, flags);

  // enable sending packets to broadcast addresses
  const int opt = 1;
  setsockopt(sock_desc, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));

  return 0;
}

char* Network::receive(sockaddr_storage* from, size_t* length) {
  char* buf = new char[BUF_SIZE]();
  size_t len;
  socklen_t soc_len = sizeof(*from);

  // receive packet, save its data in BUF and save datas size in LEN
  len = recvfrom(sock_desc, buf, BUF_SIZE, 0, (sockaddr*)from, &soc_len);
  // if there was no packets received
  if(len == 0 || len == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
    return NULL;
  }
  else {
    if(len == -1) {
      cout << "ERROR: Could not receive packet!" << endl;
      return NULL;
    }
    // if LENGTH was passed as argument, saves LEN in it
    if(length != NULL)
      *length = len;
  }

  return buf;
}

int Network::sendTo(string ip, string port, const char* data, size_t size) {
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

  if(sendto(sock_desc, data, size, 0, rp->ai_addr, 
            rp->ai_addrlen) == -1)
    cout << "ERROR: Could not send packet!" << endl;

  freeaddrinfo(result);

  return 0;
}

char* Network::printableIpOfSender(sockaddr_storage &sender) {
  if(sender.ss_family == AF_INET)
    return inet_ntoa(((sockaddr_in*)&sender)->sin_addr);
  else if(sender.ss_family == AF_INET6) {
    char* printableIp = new char[INET6_ADDRSTRLEN]();
    inet_ntop(AF_INET6, &((sockaddr_in6*)&sender)->sin6_addr, printableIp, sizeof(printableIp));
    return printableIp;
  }
  
  return NULL;
}