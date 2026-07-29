cmake_minimum_required(VERSION 3.10)

project(bot)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)

add_subdirectory(../extern/tgbot-cpp tgbot-build)
add_executable(bot
        src/bot.cpp
        src/handlers/general.cpp
        src/handlers/moderation.cpp
        src/handlers/owner.cpp
        src/utils/message_util.cpp
        src/utils/permissions.cpp
        src/commands/register.cpp
        src/web/health_server.cpp
        src/utils/shutdown.cpp
    )
    target_include_directories(bot PRIVATE
            ${Boost_INCLUDE_DIRS}
             ${PROJECT_SOURCE_DIR}/../extern/cpp-httplib
        )

        target_link_libraries(bot
                TgBot
            )
