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
    boost::uuids::uuid uuid = boost::uuids::random_generator()();

    const string s_uuid = boost::lexical_cast<string>(uuid);
    const char * c_uuid = s_uuid.c_str();
    size_t seq_size = sizeof(dataSequence);
    size_t uuid_size = sizeof(c_uuid);

    memcpy(data, &seq_size, sizeof(size_t));
    memcpy(data + sizeof(size_t), &uuid_size, sizeof(size_t));
    memcpy(data + 2 * sizeof(size_t), &dataSequence, seq_size);
    memcpy(data + 2 * sizeof(size_t) + seq_size, c_uuid, uuid_size);

    for(int i = 0 ; i < 2 *sizeof(size_t) + seq_size + uuid_size; ++i)
    {
      cout << data[i];
    }
    cout << endl;
    
    if(network->sendTo(ip, port, data, BUF_SIZE) == 0)
      cout << "SEND: Seq" << (int)dataSequence << " uuid: " << s_uuid << " to " << ip << ":" << port << endl;
    dataSequence++;
  }

  void MobileNode::receiveData() {
    char* data = new char[BUF_SIZE]();

    size_t seq_size;
    size_t uuid_size;

    sockaddr_storage from;

    while((data = network->receive(&from)) != NULL) {
      char* sender_ip = network->printableIpOfSender(from);

      memcpy(&seq_size, (char*)data, sizeof(size_t));
      memcpy(&uuid_size, (char*)data + sizeof(size_t), sizeof(size_t));

      char* seqbuf = new char[seq_size]();
      char* uuidbuf = new char[uuid_size]();

      memcpy(seqbuf, (char*)data + 2 * sizeof(size_t), seq_size);
      memcpy(uuidbuf, (char*)data + 2 * sizeof(size_t) + seq_size, uuid_size);

      string s_uuid(uuidbuf);
      string seq(seqbuf);

      cout << "RECV: Seq" << seq
      << ", UUID " << s_uuid
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