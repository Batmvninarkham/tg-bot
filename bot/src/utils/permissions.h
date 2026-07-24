#pragma once
#include "tgbot/Api.h"
#include <cstdint>
bool isMod(const TgBot::Api& api, TgBot::Message::Ptr message);
bool isAdmin(const TgBot::Api& api, TgBot::Message::Ptr message);
bool isOwner(const TgBot::Api& api, TgBot::Message::Ptr message);
