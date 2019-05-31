#ifndef MESSAGE_H
#define MESSAGE_H

#define UUID_SIZE 36

#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <boost/lexical_cast.hpp>
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
  void setUuid(std::string _uuid);
  void setMessageText(std::string _mtext);
};

#endif
