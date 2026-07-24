#include "owner.h"
#include "tgbot/Api.h"
#include "tgbot/EventBroadcaster.h"
void registerOwnerHandlers(TgBot::Bot &bot){
TgBot::EventBroadcaster& event= bot.getEvents();
const TgBot::Api& api=bot.getApi();


event.onCommand("leave",[&api](TgBot::Message::Ptr message){
api.leaveChat(message->chat->id);
    });
}
