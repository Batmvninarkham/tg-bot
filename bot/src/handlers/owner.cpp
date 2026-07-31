#include "owner.h"
#include "tgbot/Api.h"
#include "tgbot/EventBroadcaster.h"
#include "tgbot/types/Message.h"
#include <sstream>
#include "../utils/permissions.h"
void registerOwnerHandlers(TgBot::Bot &bot){
TgBot::EventBroadcaster& event= bot.getEvents();
const TgBot::Api& api=bot.getApi();

//remove the bot from the chat
event.onCommand("leave",[&api](TgBot::Message::Ptr message){
    if(!isOwner(api, message)){
return;
    }
api.leaveChat(message->chat->id);
    });
//get the webhook info
event.onCommand("webhookinfo",[&api](TgBot::Message::Ptr message){
    if(!isOwner(api, message)){
return;
    }
auto info=api.getWebhookInfo();
if(info==nullptr){
api.sendMessage(message->chat->id, "using getUpdates");
}else{
api.sendMessage(message->chat->id, info->url);
}
        });
//delete webhook intergration if you would like to go back to Api::getUpdates
event.onCommand("deleteWebhook",[&api](TgBot::Message::Ptr message){
    if(!isOwner(api, message)){
return;
    }
        std:: istringstream iss(message->text);
        std:: string command;
        bool dropUpdates;
        if(iss>>command>>dropUpdates){
      auto result =  api.deleteWebhook(dropUpdates);
        if(result != true){
            api.sendMessage(message->chat->id, "failed in deleting webhook");
            return;
        } 
        api.sendMessage(message->chat->id, "deleted webhook and dropped updates");
        return ;
        }else {
        auto result = api.deleteWebhook();
        if(result!=true){
            api.sendMessage(message->chat->id, "failed to delete webhook");
            return;
        }
       api.sendMessage(message->chat->id, "deleted webhook dropped updates false");
       return;
       }
        });
// NOTE:to switch your bot to a local server you must implement the logout and close api method in the Api.h in tgcpp :I have no plan of ever implementing these 
}
