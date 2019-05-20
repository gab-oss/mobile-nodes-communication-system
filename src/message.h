#ifndef MESSAGE_H
#define MESSAGE_H

#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <unistd.h>
#include <iostream>

class Message {
private:
  std::string uuid;
  std::string mtext;
public:
  Message();
  Message(std::string _mtext);
  std::string generateUuid();
  std::string getMessageText();
  std::string getUuid();
};

#endif MESSAGE_H
