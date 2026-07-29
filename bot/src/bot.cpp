#include "tgbot/TgException.h"
#include<tgbot/Bot.h>
#include<string>
#include<stdio.h>
#include <iostream>
#include<tgbot/net/TgLongPoll.h>
#include "./handlers/moderation.h"
#include "./handlers/owner.h"
#include "./handlers/general.h"
#include "./commands/register.h"
#include  "./web/health_server.h"
using namespace TgBot;
#include "utils/shutdown.h"

#include <csignal>
void signalHandler(int signal) {
    running = false;
}
int main(){
  std::string token (getenv("TOKEN"));
  TgBot::Bot bot (token);
std::signal(SIGINT, signalHandler);
std::signal(SIGTERM, signalHandler);
registerGeneralHandlers(bot);
registerModerationHandlers(bot);
registerOwnerHandlers(bot);
registerAllCommands(bot);


    HealthServer healthServer;
    healthServer.start();


try{
TgLongPoll longpoll(bot);
while(running){
longpoll.start();
}
}catch(TgException& e){
  std::cerr<<e.what()<<std::endl;
}
    healthServer.stop();
    return 0;
}






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




