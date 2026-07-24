#include "message_util.h"
TgBot::Message::Ptr get_reply(TgBot::Message::Ptr message){
  if(message->replyToMessage){
  return message->replyToMessage;
  }
  return nullptr;
}
