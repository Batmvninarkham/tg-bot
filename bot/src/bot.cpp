#include "tgbot/EventBroadcaster.h"
#include "tgbot/TgException.h"
#include "tgbot/types/InputFile.h"
#include "tgbot/types/Message.h"
#include "tgbot/types/UserProfilePhotos.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include<tgbot/Bot.h>
#include<tgbot/Api.h>
#include<string>
#include<stdio.h>
#include <iostream>
#include<tgbot/net/TgLongPoll.h>
#include <vector>
using namespace TgBot;
int main(){
  std::string token (getenv("TOKEN"));
  TgBot::Bot bot (token);
 const  Api& api=bot.getApi();
 EventBroadcaster& event=bot.getEvents();
 const std::string admin(getenv("chat"));
const std::vector<std::string>options={"yes","no","idk"};
const std:: string question ="you good? ";
std:: int64_t poll_id=0;
bot.getEvents().onCommand("start",[&api](Message::Ptr message){
 auto me =api.getMe();
 api.sendMessage(message->chat->id,"hi am "+me->username );
 });
bot .getEvents().onAnyMessage([&api](Message::Ptr message){
 /*   api.sendMessage(message->chat->id,"mesage-id "+std::to_string(message->messageId));
    api.sendMessage(message->chat->id,"chat-id "+std::to_string(message->chat->id));
*/
    std::cout<<"chat-id "<<message->chat->id<<std::endl;
    std::  cout<<"user-id "<<message->from->id<<std::endl;
  api.forwardMessage(getenv("chat"),message->chat->id,message->messageId,true,true);
 
    });
event.onCommand("stop_poll",[&api,&poll_id](Message::Ptr message){
api.stopPoll(message->chat->id,poll_id);
    });

event.onCommand("sendphoto",[&api,admin](Message::Ptr message){
   auto pic = InputFile::fromFile("/home/hades/tgbot/bot/reze.png","image/png");
   Message::Ptr  sentmessage=api.sendPhoto(admin, "AgACAgQAAxkDAAMrakZXo2IfINP7rAR-dB7EzsCQSygAAuYOaxvhyjFSLA99TY1TF_MBAAMCAAN3AAM8BA" ); 
   api.sendChatAction(message->chat->id,"upload_photo");
std::cout<<"photo-id: "<<sentmessage->photo.back()->fileId<<std::endl;
    });

event.onCommand("poll",[&api,&poll_id,&question,&options](Message::Ptr message){
auto poll_l=api.sendPoll(message->chat->id,question,options);
poll_id=poll_l->messageId;
});
event.onCommand("rolladice",[&api](Message::Ptr message){
api.sendDice(message->chat->id,false,nullptr,nullptr, "🎳");
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
try{
TgLongPoll longpoll(bot);
while(true){
longpoll.start();
}
}catch(TgException& e){
  std::cerr<<e.what()<<std::endl;
}
}

