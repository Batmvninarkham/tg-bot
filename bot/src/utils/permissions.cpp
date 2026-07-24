#include "permissions.h"
#include <cstdint>
#include <cstdlib>
#include <unordered_set>
#include "tgbot/Api.h"
#include "tgbot/types/Message.h"
bool isAdmin(const TgBot::Api& api,TgBot::Message::Ptr message){
auto admin= getenv("chat");
std::unordered_set<int64_t>admins={std::stoll(admin)};
if(admins.find(message->from->id)!= admins.end()){

return true;
}else{
  api.sendMessage(message->chat->id, "Admins only!");
  return false;
}

}
