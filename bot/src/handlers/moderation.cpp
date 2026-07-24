#include "moderation.h"
#include "tgbot/Api.h"
#include "tgbot/EventBroadcaster.h"
#include <iostream>
#include "../utils/message_util.h"
#include "tgbot/types/ChatPermissions.h"

TgBot::ChatPermissions::Ptr createPermissions(bool globalSetter){
auto p = std::make_shared<TgBot::ChatPermissions>();
auto boo= globalSetter;
p->canAddWebPagePreviews=boo;
p->canChangeInfo=boo;
p->canInviteUsers=boo;
p->canManageTopics=boo;
p->canPinMessages=boo;
p->canSendMessages=boo;
p->canSendOtherMessages=boo;
p->canSendAudios=boo;
p->canSendPhotos=boo;
p->canSendDocuments=boo;
p->canSendPolls=boo;
p->canSendVideoNotes=boo;
p->canSendVideos=boo;
return p;
}

void registerModerationHandlers(TgBot::Bot& bot){
 TgBot::EventBroadcaster& event= bot.getEvents();
const TgBot::Api& api = bot.getApi();
using namespace TgBot;








event.onCommand("pin",[&api](Message::Ptr message){
    std:: istringstream iss(message->text);
    std:: string command;
    std::cerr<<message->chat->id;
    std::int64_t id_token;
    auto isreply=get_reply(message);
    if (isreply){
     api.pinChatMessage(message->chat->id, isreply->messageId);     
     return;
    } 
      if(!(iss>>command>>id_token)){
      api.sendMessage(message->chat->id, "usage:/pin <messageid>");
      return;
      }
      try{
      api.pinChatMessage(message->chat->id, id_token);
      
       return;
      }catch(const std:: exception& e){  
      std:: cout<< e.what();
      return;
      }
    });

event.onCommand("ban",[&api](Message::Ptr message){
    std::istringstream iss(message->text);
    std::string command;
    std::string userid;
    std::int32_t time;
    std::string reason;
    auto mess=message->chat;
    auto reply= get_reply(message);   
    std::string why="";
    if(reply){
    if(reply->from){
    if(!(iss>>command>>time)){
    api.banChatMember(mess->id, reply->from->id);
    api.sendMessage(mess->id,"user: "+reply->from->username+std::to_string(reply->from->id)+"has been banned forever" );
    return;
    }
    api.banChatMember(mess->id, reply->from->id,time);
    if(iss>>reason){
      why="reason = "+reason;
    }
    api.sendMessage(mess->id,"user: "+reply->from->username+std::to_string(reply->from->id)+"has been banned for <"+std::to_string(time)+">" +why);
    return;
    } 
    if(reply->senderChat){
    api.banChatSenderChat(mess->id, reply->senderChat->id);
    if(iss>>reason){
      why="reason = "+reason;
    }
    api.sendMessage(mess->id,"channel chat: "+reply->senderChat->username+" <"+std::to_string(reply->senderChat->id)+"> banned implicit unban required "+why );
    return;
    
    }
    }
    //*********later support inputing username to ban *************
    api.sendMessage(mess->id, "usage: replytomessage -> /ban");
    return;
    });

event.onCommand("unbanChat",[&api](Message::Ptr message){
auto reply=get_reply(message);
    auto mess=message->chat;
if(reply){
api.unbanChatSenderChat(mess->id, reply->senderChat->id);
api.sendMessage(mess->id, reply->senderChat->username+std::to_string(reply->senderChat->id)+" unbanned");
}
    api.sendMessage(mess->id, "usage: replytomessage -> /unbanChat");
    return;
  
    });
event.onCommand("unbanUser",[&api](Message::Ptr message){
auto reply = get_reply(message);
if(reply){
api.unbanChatMember(message->chat->id, reply->from->id);

api.sendMessage(message->chat->id, reply->from->username+std::to_string(reply->from->id)+" unbanned");
return;
}
    api.sendMessage(message->chat->id, "usage: replytomessage -> /unbanUser");
    return;

    });
event.onCommand("mute",[&api](Message::Ptr message){
  auto reply=get_reply(message);
  std::string command;
  std:: int64_t time;
  std::istringstream iss(message->text);
  if(reply){
  if(reply->from)
  { 
  if(!(iss>>command>>time)){
  api.restrictChatMember(message->chat->id,reply->from->id,createPermissions(false) ,0,true);
api.sendMessage(message->chat->id,"user: "+reply->from->username+" id["+std::to_string(reply->from->id)+"] muted indefinetly");
return;
}
api.restrictChatMember(message->chat->id,reply->from->id ,createPermissions(false),time,true);
return;
}
if(reply->senderChat){
api.sendMessage(message->chat->id, "cannot mute a channel consider banning");
return;
}
}
api.sendMessage(message->chat->id, "usage:replytomessage then /mute");
return;
    });


event.onCommand("unmute",[&api](Message::Ptr message){
auto result= api.getChat(message->chat->id);
auto reply=get_reply(message);
 std::istringstream iss(message->text);
 std:: string command;
 std:: int64_t time;
if(reply->from){
if(!(iss>>command>>time)){
api.restrictChatMember(message->chat->id,reply->from->id, result->permissions);
api.sendMessage(message->chat->id, "user "+std::to_string(reply->from->id)+" "+reply->from->username+" unmuted ");
return;
}
api.restrictChatMember(message->chat->id, reply->from->id, result->permissions,time);
api.sendMessage(message->chat->id, "user: "+std::to_string(reply->from->id)+" "+reply->from->username+" banned for <"+std::to_string(time)+">");
return;
}
//later add a database to do lookups so we can ban by username :)
api.sendMessage(message->chat->id, "usage:reply to user -> /unmute ");
    });
}
