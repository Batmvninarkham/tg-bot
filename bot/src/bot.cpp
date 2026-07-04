#include "tgbot/types/InputFile.h"
#include "tgbot/types/Message.h"
#include <ostream>
#include<stdlib.h>
#include<tgbot/net/TgLongPoll.h>
#include<tgbot/Bot.h>
#include<iostream>
using namespace TgBot;
#include <chrono>
int main (){
  std:: string token(getenv("TOKEN"));
Bot bot(token);


 bot.getEvents().onCommand("start",[&bot](Message::Ptr message){
     std::cerr <<"callback entered..\n"<< std::flush;
     
auto start = std::chrono::steady_clock::now();
bot.getApi().sendMessage(message -> chat->id,"Hi am four");
auto end = std::chrono::steady_clock::now();
std::cerr
    << "sendMessage took "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << " ms\n";
});


const std::string filePath="/home/hades/tgbot/bot/reze.png";
const std::string fileType="image/jpeg";
bot.getEvents().onCommand("photo",[&bot,&filePath,&fileType](Message::Ptr message ){
bot.getApi().sendPhoto(message->chat->id,InputFile::fromFile( filePath, fileType));
    });
TgLongPoll longpoll(bot);
while(true){
  std::cerr << "waiting for updates\n";
longpoll.start();
std::cerr<<"longpoll start returned\n";
}
return 0;
}
