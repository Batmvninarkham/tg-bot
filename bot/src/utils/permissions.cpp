#include "permissions.h"
#include <cstdint>
#include <cstdlib>
#include <unordered_set>
#include "tgbot/Api.h"
#include "tgbot/types/Message.h"

bool isMod(const TgBot::Api& api,TgBot::Message::Ptr message){
auto mod= getenv("chat");
auto member=api.getChatMember(message->chat->id, message->from->id);
//possible values #:1 creator ,administrator ,member, restricted,left,kicked

//add mods in unordered set by userid gonna add an endpoint to add dynamically sometime in the future
std::unordered_set<int64_t>mods={std::stoll(mod)};
if(mods.find(message->from->id)!= mods.end() || member->status == "administrator"|| member->status == "creator" ){

return true;
}else{
  api.sendMessage(message->chat->id, " not enough permissions!");
  return false;
}
}
bool isOwner(const TgBot::Api &api, TgBot::Message::Ptr message){
auto member=api.getChatMember(message->chat->id, message->from->id);
//possible values #:1 creator ,administrator ,member, restricted,left,kicked
if(member->status == "creator"){
return true;
}else {
api.sendMessage(message->chat->id, "Creator only!");
return false;
}

}
bool isAdmin(const TgBot::Api &api, TgBot::Message::Ptr message){
auto member=api.getChatMember(message->chat->id, message->from->id);
//possible values #:1 creator ,administrator ,member, restricted,left,kicked
if(member->status == "administrator"  || member->status == "creator"){
return true;
}else {
api.sendMessage(message->chat->id, "Admins  only!");
return false;
}
}
