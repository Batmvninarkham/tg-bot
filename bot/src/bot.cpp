#include "tgbot/types/Message.h"
#include<stdlib.h>
#include<tgbot/net/TgLongPoll.h>
#include<tgbot/Bot.h>
using namespace TgBot;
int main (){
  std:: string token(getenv("TOKEN"));
Bot bot(token);
 bot.getEvents().onCommand("start",[&bot](Message::Ptr message){
bot.getApi().sendMessage(message -> chat->id,"Hi am four");
});
TgLongPoll longpoll(bot);
while(true){
longpoll.start();
}
return 0;
}
