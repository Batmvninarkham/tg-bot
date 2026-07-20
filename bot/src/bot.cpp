#include "tgbot/EventBroadcaster.h"
#include "tgbot/TgException.h"
#include "tgbot/types/InputFile.h"
#include "tgbot/types/Message.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
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


int main(){
  std::string token (getenv("TOKEN"));
  TgBot::Bot bot (token);
 const  Api& api=bot.getApi();
 EventBroadcaster& event=bot.getEvents();
// const std::string admin(getenv("chat"));
const std::vector<std::string>options={"yes","no","idk"};
const std:: string question ="you good? ";
std:: int64_t poll_id=0;
std::unordered_map<int64_t, state>userstates;

event.onCommand("pin",[&api,&userstates](Message::Ptr message){
    std:: istringstream iss(message->text);
    std:: string command;
    std::string id_token;
    if(!(iss >>command >> id_token )){
    api.sendMessage(message->chat->id,"from pin cmd  messageid?");
    api.sendMessage(message->chat->id,std::to_string( message->messageId));
    userstates[message->chat->id]= state::WAITING_FOR_MESSAGE_ID;
    return;
    }    
try{

int id =std::stoi(id_token);
bool result=api.pinChatMessage(message->chat->id,id);
if(result!=true){
api.sendMessage(message->chat->id,"failed to pin check if messageid is valid!<exists?> ");
userstates[message->chat->id]=state::WAITING_FOR_MESSAGE_ID;
}else userstates[message->chat->id]=state::IDLE;
}catch(const std::exception&){
api.sendMessage(message->chat->id,"invalid messageid must be a number");
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

event.onAnyMessage([&api,&userstates](Message::Ptr message){
if (!message->text.empty() && message->text[0] == '/') return;
if(userstates[message->chat->id] == state::IDLE){
return ;
}
if(userstates[message->chat->id]==state::WAITING_FOR_MESSAGE_ID){
if(!isNumber(message->text)){
api.sendMessage(message->chat->id, "message id needs to be a number! ");
return;
}

auto ms_id=std::stoi(message->text);
api.pinChatMessage(message->chat->id,ms_id);
userstates[message->chat->id]=state::IDLE;
}
    });




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
//poll
event.onCommand("poll",[&api,&poll_id,&question,&options](Message::Ptr message){
auto poll_l=api.sendPoll(message->chat->id,question,options);
poll_id=poll_l->messageId;
});
//roll a dice
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

