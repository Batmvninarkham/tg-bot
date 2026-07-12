cmake_minimum_required(VERSION 3.10)

project(bot)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)

add_subdirectory(../tgbot-cpp-master tgbot-build)

add_executable(bot
        src/bot.cpp
    )

    target_include_directories(bot PRIVATE
            ${Boost_INCLUDE_DIRS}
        )

        target_link_libraries(bot
                TgBot
            )
