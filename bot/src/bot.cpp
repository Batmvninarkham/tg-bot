#include "tgbot/EventBroadcaster.h"
#include "tgbot/TgException.h"
#include "tgbot/types/InputFile.h"
#include "tgbot/types/Message.h"
#include <cstdlib>
#include<tgbot/Bot.h>
#include<tgbot/Api.h>
#include<string>
#include<stdio.h>
#include <iostream>
#include<tgbot/net/TgLongPoll.h>
using namespace TgBot;
int main(){
  std::string token (getenv("TOKEN"));
  TgBot::Bot bot (token);
 const  Api& api=bot.getApi();
 EventBroadcaster& event=bot.getEvents();
 const std::string admin(getenv("chat"));


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
event.onCommand("sendphoto",[&api,admin](Message::Ptr message){
   auto pic = InputFile::fromFile("/home/hades/tgbot/bot/reze.png","image/png");
   Message::Ptr  sentmessage=api.sendPhoto(admin, "AgACAgQAAxkDAAMrakZXo2IfINP7rAR-dB7EzsCQSygAAuYOaxvhyjFSLA99TY1TF_MBAAMCAAN3AAM8BA" ); 
std::cout<<"photo-id: "<<sentmessage->photo.back()->fileId<<std::endl;
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

