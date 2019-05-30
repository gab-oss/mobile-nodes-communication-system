#include "mobile_node.h"

MobileNode::MobileNode(IP_VERSION ip_version_, char* ip_, char* port_, bool is_serv)
: ip_version(ip_version_), ip(ip_), port(port_), is_serv(is_serv) {
  network = new Network(ip_version);
  network->bindSocket(port);
  message = new Message();
}

MobileNode::~MobileNode() {
  delete network;
  delete message;
}

void  MobileNode::sendData() {

  char* data = new char[BUF_SIZE]();
  strcpy(data, dataSequence.c_str());
  // data[0] = dataSequence;
  if(network->sendTo(ip, port, data, BUF_SIZE) == 0)
    cout << "SEND: " << message->getMessageText() << ", UUID " << message->getUuid()
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

    //uuid saved - discard message
    if (std::find(recent_uuids.begin(), recent_uuids.end(), s_uuid) != recent_uuids.end()) {

      cout << "DISCARDED: UUID " << s_uuid
            << " from " << sender_ip << " on port " << port << endl;

      return;
    }

    recent_uuids.push_front(s_uuid);
    if (recent_uuids.size() > MAX_RECENT_UUIDS) {
      recent_uuids.pop_back();
    }

    message->setUuid(s_uuid);
    message->setMessageText(s_m_text);

    if (is_serv) {
      cout << "RECV: " << m_text << " UUID " << uuid
            << " from " << sender_ip << " on port " << port << endl;

            cout << "MESSAGE IS: " << message->getMessageText() << " UUID " << message->getUuid()
                  << " from " << sender_ip << " on port " << port << endl;
    }
  }
}

void MobileNode::mainLoop() {

  getNewData();

  unsigned int time_counter = 0;
  // double time_counter = 0;
  //
  // clock_t this_time = clock();
  // clock_t last_time = this_time;

  while(true) {

    // get new data every RESEARCH_TIME seconds
    // this_time = clock();
    // time_counter += (double)(this_time - last_time);
    // last_time = this_time;
    //
    // if(time_counter > (double)(RESEARCH_TIME * CLOCKS_PER_SEC)){
    //    time_counter -= (double)(RESEARCH_TIME * CLOCKS_PER_SEC);
    //    getNewData();
    // }

    if (time_counter > RESEARCH_TIME) {
      getNewData();
      time_counter = 0;
    }

    receiveData();
    sendData();
    ++time_counter;
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

  recent_uuids.push_front(message->getUuid());
  if (recent_uuids.size() > MAX_RECENT_UUIDS) {
    recent_uuids.pop_back();
  }

}
