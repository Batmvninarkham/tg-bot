#include "tgbot/EventBroadcaster.h"
#include "tgbot/TgException.h"
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


int main(){
  std::string token (getenv("TOKEN"));
  TgBot::Bot bot (token);
  //****rewrite
 const  Api& api=bot.getApi();
 EventBroadcaster& event=bot.getEvents();
// const std::string admin(getenv("chat"));



/*
//grab all messages to the bot 
bot .getEvents().onAnyMessage([&api](Message::Ptr message){

   std::cout<<"chat-id "<<message->chat->id<<std::endl;
    std::  cout<<"user-id "<<message->from->id<<std::endl;
 api.forwardMessage(getenv("chat"),message->chat->id,message->messageId,true,true);
 
    });
*/





//stop most recent poll
/*
//sendphoto
event.onCommand("sendphoto",[&api,admin](Message::Ptr message){
   auto pic = InputFile::fromFile("/home/hades/tgbot/bot/reze.png","image/png");
   Message::Ptr  sentmessage=api.sendPhoto(admin, "AgACAgQAAxkDAAMrakZXo2IfINP7rAR-dB7EzsCQSygAAuYOaxvhyjFSLA99TY1TF_MBAAMCAAN3AAM8BA" ); 
   api.sendChatAction(message->chat->id,"upload_photo");
    });*/


event.onCommand("leave",[&api](Message::Ptr message){
api.leaveChat(message->chat->id);
    });



//***********webapp intergration checkpoint********************

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

