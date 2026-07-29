#pragma once
#include "tgbot/Api.h"
#include "tgbot/types/Message.h"
#include <cstdint>
bool isMod(const TgBot::Api& api, TgBot::Message::Ptr message);
bool isAdmin(const TgBot::Api& api, TgBot::Message::Ptr message);
bool isOwner(const TgBot::Api& api, TgBot::Message::Ptr message);
std::string chatTyoe(const TgBot::Api& api, TgBot::Message::Ptr message);
