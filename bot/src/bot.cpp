#include "tgbot/EventBroadcaster.h"
#include "tgbot/TgException.h"
#include "tgbot/tools/StringTools.h"
#include "tgbot/types/CallbackQuery.h"
#include "tgbot/types/Chat.h"
#include "tgbot/types/ChatPermissions.h"
#include "tgbot/types/InlineKeyboardButton.h"
#include "tgbot/types/InlineKeyboardMarkup.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/WebAppInfo.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <memory>
#include <ostream>
#include <sstream>
#include <sys/types.h>
#include<tgbot/Bot.h>
#include<tgbot/Api.h>
#include<string>
#include<stdio.h>
#include <iostream>
#include<tgbot/net/TgLongPoll.h>
#include <unordered_map>
#include <vector>
using namespace TgBot;

enum class state{
WAITING_FOR_PHOTO,
WAITING_FOR_MESSAGE_ID,
IDLE
};

bool isNumber(const std::string& s)
{
      return !s.empty() &&
                   std::all_of(s.begin(), s.end(), ::isdigit);
}
Message::Ptr get_reply(Message::Ptr message){
  if(message->replyToMessage){
  return message->replyToMessage;
  }
  return nullptr;
}
ChatPermissions::Ptr createPermissions(bool globalSetter){
auto p = std::make_shared<ChatPermissions>();
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

int main(){
  std::string token (getenv("TOKEN"));
  TgBot::Bot bot (token);
 const  Api& api=bot.getApi();
 EventBroadcaster& event=bot.getEvents();
// const std::string admin(getenv("chat"));

const std:: string question ="you good? ";
std:: int64_t poll_id=0;
std::unordered_map<int64_t, state>userstates;

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

//start
bot.getEvents().onCommand("start",[&api](Message::Ptr message){
 auto me =api.getMe();
 api.sendMessage(message->chat->id,"hi am "+me->username );
 });
/*
//grab all messages to the bot 
bot .getEvents().onAnyMessage([&api](Message::Ptr message){

   std::cout<<"chat-id "<<message->chat->id<<std::endl;
    std::  cout<<"user-id "<<message->from->id<<std::endl;
 api.forwardMessage(getenv("chat"),message->chat->id,message->messageId,true,true);
 
    });
*/





//stop most recent poll
event.onCommand("stop_poll",[&api,&poll_id](Message::Ptr message){
api.stopPoll(message->chat->id,poll_id);
    });
/*
//sendphoto
event.onCommand("sendphoto",[&api,admin](Message::Ptr message){
   auto pic = InputFile::fromFile("/home/hades/tgbot/bot/reze.png","image/png");
   Message::Ptr  sentmessage=api.sendPhoto(admin, "AgACAgQAAxkDAAMrakZXo2IfINP7rAR-dB7EzsCQSygAAuYOaxvhyjFSLA99TY1TF_MBAAMCAAN3AAM8BA" ); 
   api.sendChatAction(message->chat->id,"upload_photo");
    });*/
//roll a dice
event.onCommand("dice",[&api](Message::Ptr message){
    std:: string emoji;
    std:: string command;
    std::istringstream iss(message->text);
   const  std::vector<std::string>emojis={"🎲","🎯", "🏀", "⚽", "🎳", "🎰"};
    if(iss>>command>>emoji){
if(emoji=="dice"){ emoji= emojis[0];
}else if(emoji =="dart") emoji=emojis[1];
else if(emoji =="basketball") emoji=emojis[2];
else if(emoji =="football") emoji=emojis[3];
else if(emoji =="bowlball")  emoji=emojis[4];
else if(emoji =="slotmachine") emoji=emojis[5];
auto result=api.sendDice(message->chat->id,false,nullptr,nullptr, emoji);
//api.sendMessage(message->chat->id,std::to_string( result->dice->value));
return;
}
emoji=emojis[0];
api.sendDice(message->chat->id,false, nullptr, nullptr,emoji);
return;
});

//get userprofile
event.onCommand("profile",[&api](Message::Ptr message){
auto pic=api.getUserProfilePhotos(message->from->id);
auto id=pic->photos[0].back();
api.sendPhoto(message->chat->id,id->fileId);
api.sendChatAction(message->chat->id,"upload_photo");
    });
  event.onUnknownCommand([&api](Message::Ptr message){
      auto reply = std::make_shared<TgBot::ReplyParameters>();

    reply->messageId = message->messageId;

    if(reply == nullptr) return;
   // api.sendMessage(message->chat->id,"invalid command twin!",nullptr,reply);
   api.sendMessage(message->chat->id, "invalid command bro ",nullptr,reply);
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
auto app=std::make_shared<WebAppInfo>();
app->url="https://hades-ashy.vercel.app";
auto button= std::make_shared<InlineKeyboardButton>();
button->text="streamctl";
button->webApp=app;
auto markup= std::make_shared<InlineKeyboardMarkup>();
markup->inlineKeyboard.push_back({button});

event.onCommand("streamctl",[&api,&markup](Message::Ptr message){
api.sendMessage(message->chat->id, "launch the streamctl webapp to watch your games <author batmvn>",nullptr,nullptr,markup,"Markdown");
return;   
});



try{
TgLongPoll longpoll(bot);
while(true){
longpoll.start();
}
}catch(TgException& e){
  std::cerr<<e.what()<<std::endl;
}
}

