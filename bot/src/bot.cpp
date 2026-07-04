#include <cstdlib>
#include<tgbot/Bot.h>
#include<tgbot/Api.h>
#include<string>
#include<stdio.h>
#include<tgbot/net/TgLongPoll.h>
using namespace TgBot;
int main(){
  std::string token (getenv("TOKEN"));
  TgBot::Bot bot (token);
 const  Api& api=bot.getApi();
bot.getEvents().onCommand("start",[&api](Message::Ptr message){
 auto me =api.getMe();
 api.sendMessage(message->chat->id,"hi am "+me->username );
 });
bot .getEvents().onAnyMessage([&api](Message::Ptr message){
    api.sendMessage(message->chat->id,"mesage-id "+std::to_string(message->messageId));
    api.sendMessage(message->chat->id,"chat-id "+std::to_string(message->chat->id));
    });
TgLongPoll longpoll(bot);
while(true){
longpoll.start();
}
}


