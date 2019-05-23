#include "mobile_node.h"

MobileNode::MobileNode(IP_VERSION ip_version_, char* ip_, char* port_) : ip_version(ip_version_), ip(ip_), port(port_) {
  network = new Network(ip_version);
  network->bindSocket(port);
  message = new Message();
}

MobileNode::~MobileNode() {
  delete network;
  delete message;
}

void  MobileNode::sendData() {
  getNewData();
  char* data = new char[BUF_SIZE]();
  strcpy(data, dataSequence.c_str());
  // data[0] = dataSequence;
  if(network->sendTo(ip, port, data, BUF_SIZE) == 0)
    cout << "SEND: Seq" << message->getMessageText() << ", UUID " << message->getUuid()
     << " to " << ip << ":" << port << endl;
  // dataSequence++;
}

void MobileNode::receiveData() {
  char* data = new char[BUF_SIZE];
  char* uuid = new char[UUID_SIZE];
  char* m_text = new char[BUF_SIZE - UUID_SIZE];
  sockaddr_storage from;


  while((data = network->receive(&from)) != NULL) {
    char* sender_ip = network->printableIpOfSender(from);

    for (int i = 0; i < UUID_SIZE; ++ i) {
      uuid[i] = data[i];
    }

    strcpy (m_text, data + UUID_SIZE);

    std::string s_uuid(uuid);
    std::string s_m_text(m_text);
    message->setUuid(s_uuid);
    message->setMessageText(s_m_text);

    cout << "RECV: " << m_text << " UUID " << uuid
          << " from " << sender_ip << " on port " << port << endl;

          cout << "MESSAGE IS: " << message->getMessageText() << " UUID " << message->getUuid()
                << " from " << sender_ip << " on port " << port << endl;
  }
}

void MobileNode::mainLoop() {
  while(true) {
    receiveData();
    sendData();
    sleep(1);
  }
}

void MobileNode::getNewData(){

  //current time
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);

  std::ostringstream oss;
  oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
  auto _time = oss.str();

  message->generateUuid();
  message->setMessageText(_time);

  std::stringstream ss;
  ss << message->getUuid() << message->getMessageText();
  dataSequence = ss.str();

}
