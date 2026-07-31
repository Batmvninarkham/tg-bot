#include "permissions.h"
#include <cstdint>
#include <cstdlib>
#include <string>
#include <unordered_set>
#include "tgbot/Api.h"
#include "tgbot/types/Chat.h"
#include "tgbot/types/Message.h"
std::string chatType( TgBot::Message::Ptr message){
auto type = message->chat->type;
if(type == TgBot::Chat::Type::Private) return "private";
if(type ==TgBot::Chat::Type::Group) return "group";
if(type==TgBot::Chat::Type::Supergroup)return "supergroup";
if(type==TgBot::Chat::Type::Channel)return "channel";
return "";
}

bool isMod(const TgBot::Api& api,TgBot::Message::Ptr message){

  auto owner= getenv("chat");
auto member=api.getChatMember(message->chat->id, message->from->id);
//possible values #:1 creator ,administrator ,member, restricted,left,kicked

//add mods in unordered set by userid gonna add an endpoint to add dynamically sometime in the future
std::unordered_set<int64_t>mods={std::stoll(owner)};
if(mods.find(message->from->id)!= mods.end() || member->status == "administrator"|| member->status == "creator" ){
  if(chatType(message)=="private"){
if(message->from->id != std::stoll(owner)) {return false;}
return true;
  }
  return true;
}else{
  api.sendMessage(message->chat->id, " not enough permissions!");
  return false;
}
}


bool isOwner(const TgBot::Api &api, TgBot::Message::Ptr message){
  auto owner= std::stoll(getenv("chat"));
auto member=api.getChatMember(message->chat->id, message->from->id);
//possible values #:1 creator ,administrator ,member, restricted,left,kicked
if(member->status == "creator"|| message->from->id == owner){
if(chatType(message)=="private"){
if(message->from->id != owner) {return false;}
return true;
  }
return true;
}else {
api.sendMessage(message->chat->id, "Creator only!");
return false;
}
}
bool isAdmin(const TgBot::Api &api, TgBot::Message::Ptr message){
   auto owner= std::stoll(getenv("chat"));
auto member=api.getChatMember(message->chat->id, message->from->id);
//possible values #:1 creator ,administrator ,member, restricted,left,kicked
if(member->status == "administrator" || message->from->id ==owner || member->status == "creator"){
   auto owner= std::stoll(getenv("chat"));
if(chatType(message)=="private"){
if(message->from->id != owner) {return false;}
return true;
  }
return true;
}else {
api.sendMessage(message->chat->id, "Admins  only!");
return false;
}
}
