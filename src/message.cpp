#include <message.h>

Message::Message() {

  generateUuid();

  //deafult message is "default"
  mtext = "default";
}

Message::Message(std::string _mtext) {

  generateUuid();
  mtext = _mtext;
}

std::string Message::generateUuid() {

  boost::uuids::uuid gen_uuid = boost::uuids::random_generator()();
  uuid = boost::lexical_cast<std::string>(gen_uuid);

  std::cout << "Generated UUID is "<< uuid << ", size is " << sizeof(uuid) << std::endl;
  return uuid;
}

std::string Message::getMessageText() {

  return mtext;
}

std::string Message::getUuid() {

  return uuid;
}
