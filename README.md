# Telegram Bot

A Telegram bot written in C++ using the `tgbot-cpp` library.

The project is built with CMake, containerized with Docker, and can be deployed as a long-polling bot. A lightweight HTTP health server is included for platforms that require an exposed port.

## Features

- Long polling with the Telegram Bot API
- Modular command and handler registration
- Health check endpoint
- Graceful shutdown
- Docker support
- Git submodule for `tgbot-cpp`

## Project Structure

```
.
├── bot/
│   ├── src/
│   │   ├── commands/
│   │   ├── handlers/
│   │   ├── utils/
│   │   └── web/
│   └── CMakeLists.txt
├── extern/
│   ├── tgbot-cpp/
│   └── cpp-httplib/
├── Dockerfile
└── README.md
```

## Building

Clone the repository with its submodules.

```bash
git clone --recursive <repository-url>
```

If the repository has already been cloned:

```bash
git submodule update --init --recursive
```

Build the project.

```bash
cd bot

cmake -S . -B build
cmake --build build
```

## Running

The bot reads its token from the `TOKEN` environment variable.

```bash
export TOKEN=<telegram-bot-token>

./build/bot
```

## Docker

Build the image.

```bash
docker build -t telegram-bot .
```

Run the container.

```bash
docker run \
    -e TOKEN=<telegram-bot-token> \
    -p 8080:8080 \
    telegram-bot
```

## Health Endpoint

The embedded HTTP server exposes:

```
GET /
GET /health
```

The listening port is taken from the `PORT` environment variable when present, otherwise it defaults to `8080`.

## Dependencies

- C++17
- CMake
- Boost
- OpenSSL
- libcurl
- zlib
- `tgbot-cpp`
- `cpp-httplib`

## Notes

This project vendors `tgbot-cpp` as a Git submodule. Local modifications to the library are maintained on a separate branch to simplify synchronizing with upstream changes.
