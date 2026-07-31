#include "register.h"
#include "tgbot/types/BotCommand.h"
#include "tgbot/types/BotCommandScopeChatAdministrators.h"
#include "tgbot/types/BotCommandScopeChatMember.h"
#include "tgbot/types/BotCommandScopeDefault.h"
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>
void registerAllCommands(TgBot::Bot &bot){
  //===========================
  //
//NOTE do not call this function if you have not set the variables found in the comments below in the scope declaration  
//
//=============================

//dafault commands
  std:: vector<TgBot::BotCommand::Ptr>defaultCommands;
  
  auto start=std::make_shared<TgBot::BotCommand>();
start->description="return the username of the bot";
  start->command="start";
  defaultCommands.push_back(start);


auto ids=std::make_shared<TgBot::BotCommand>();
ids->command="ids";
ids->description="return the chatids and userid";
defaultCommands.push_back(ids);

auto dice= std::make_shared<TgBot::BotCommand>();
dice->command="dice";
  dice->description="combinations dart, football,basketball,dice,bowlball,slotmachine defaults to dice";
  defaultCommands.push_back(dice);

  auto streamctl= std::make_shared<TgBot::BotCommand>();
  streamctl->command="streamctl";
  streamctl->description="launch the streamctl webapp to watch games";
  defaultCommands.push_back(streamctl);

  auto profile= std::make_shared<TgBot::BotCommand>();
  profile->command="profile";
  profile->description="reply to a user to get their profile picture";
  defaultCommands.push_back(profile);

  //admin commands
  std::vector<TgBot::BotCommand::Ptr>adminCommands;

  auto pin=std:: make_shared<TgBot::BotCommand>();
  pin->command="pin";
  pin->description="reply to a message or pass a valid messageid";
  adminCommands.push_back(pin);

  auto ban= std::make_shared<TgBot::BotCommand>();
  ban->command="ban";
  ban->description="reply to user optinal pass a time (defaults to forever) optional pass a userid";
  adminCommands.push_back(ban);

  auto unban=std::make_shared<TgBot::BotCommand>();
  unban->command="unban";
  unban->description="reply to one of the  targets message to unban the user";
  adminCommands.push_back(unban);

  auto mute = std::make_shared<TgBot::BotCommand>();
  mute->command="mute";
  mute->description="reply to one of targets message @params optional time defaults to forever";
  adminCommands.push_back(mute);

  auto unmute=std::make_shared<TgBot::BotCommand>();
unmute->command="unmute";
unmute->description="reply to one of the target message @params optional time defaults to forever ";
adminCommands.push_back(unmute);

//creator commands
std::vector<TgBot::BotCommand::Ptr>creatorCommands;

auto leave=std::make_shared<TgBot::BotCommand>();
leave->command="leave";
leave->description="remove bot from the group/channel";
  creatorCommands.push_back(leave);

auto webhookinfo=std::make_shared<TgBot::BotCommand>();
webhookinfo->command="webhookinfo";
webhookinfo->description="get current webhook info ";
creatorCommands.push_back(webhookinfo);

auto deleteWebhook=std::make_shared<TgBot::BotCommand>();
deleteWebhook->command="deleteWebhook";
deleteWebhook->description="delete current webhook intergration @params optional boolean dropped updates";
creatorCommands.push_back(deleteWebhook);

//scope decalration
auto defaultScope=std::make_shared<TgBot::BotCommandScopeDefault>();
auto adminScope=std::make_shared<TgBot::BotCommandScopeChatAdministrators>();
//NOTE add chatid to the admin scope eg adminScope->chatid="xxx";
auto creatorScope =std::make_shared<TgBot::BotCommandScopeChatMember>();
//creatorScope->chatId=std::stoll(std::getenv("chat")); // to  creator scope cant be used in private chats
//creatorScope->userId=std::stoll(std::getenv("chat"));

//NOTE add your  chatid  and userid here if you are the owner of the bot 
                                    
//register 
  const TgBot:: Api& api=bot.getApi();
//api.setMyCommands(adminCommands,adminScope);
//api.setMyCommands(creatorCommands,creatorScope);
api.setMyCommands(defaultCommands,defaultScope);

}
