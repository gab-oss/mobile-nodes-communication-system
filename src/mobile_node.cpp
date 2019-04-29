#include "mobile_node.h"

  MobileNode::MobileNode(IP_VERSION ip_version_, char* ip_, char* port_) : ip_version(ip_version_), ip(ip_), port(port_) {
    network = new Network(ip_version);
    network->bindSocket(port);
  }

  MobileNode::~MobileNode() {
    delete network;
  }

  void  MobileNode::sendData() {
    char* data = new char[BUF_SIZE]();
    data[0] = dataSequence;
    if(network->sendTo(ip, port, data, BUF_SIZE) == 0)
      cout << "SEND: Seq" << (int)dataSequence << " to " << ip << ":" << port << endl;
    dataSequence++;
  }

  void MobileNode::receiveData() {
    char* data;
    sockaddr_storage from;


    while((data = network->receive(&from)) != NULL) {
      char* sender_ip = network->printableIpOfSender(from);
      cout << "RECV: Seq" << (int)(unsigned char)data[0] << " from " << sender_ip << " on port " << port << endl;
    }
  }

  void MobileNode::mainLoop() {
    while(true) {
      receiveData();
      sendData();
      sleep(1);
    }
  }