#include "general.h"
#include "tgbot/EventBroadcaster.h"
#include "tgbot/Api.h"
void registerGeneralHandlers(TgBot::Bot& bot){

const  TgBot::Api& api =bot.getApi();
TgBot::EventBroadcaster& event=bot.getEvents();


event.onCommand("dice",[&api](TgBot::Message::Ptr message){
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


event.onCommand("profile",[&api](TgBot::Message::Ptr message){
auto pic=api.getUserProfilePhotos(message->from->id);
auto id=pic->photos[0].back();
api.sendPhoto(message->chat->id,id->fileId);
api.sendChatAction(message->chat->id,"upload_photo");
    });



  event.onUnknownCommand([&api](TgBot::Message::Ptr message){
      auto reply = std::make_shared<TgBot::ReplyParameters>();

    reply->messageId = message->messageId;

    if(reply == nullptr) return;
   // api.sendMessage(message->chat->id,"invalid command twin!",nullptr,reply);
   api.sendMessage(message->chat->id, "invalid command bro ",nullptr,reply);
    });



bot.getEvents().onCommand("start",[&api](TgBot::Message::Ptr message){
 auto me =api.getMe();
 api.sendMessage(message->chat->id,"hi am "+me->username );
 });

}
