#include "health_server.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <sstream>

static std::string formatUptime(std::chrono::seconds uptime) {
  auto total = uptime.count();

  int days = total / 86400;
  total %= 86400;

  int hours = total / 3600;
  total %= 3600;

  int minutes = total / 60;
  int seconds = total % 60;

  std::ostringstream out;

  if (days > 0)
    out << days << "d ";

  if (hours > 0)
    out << hours << "h ";

  if (minutes > 0)
    out << minutes << "m ";

  if (seconds > 0 || out.str().empty())
    out << seconds << "s";

  return out.str();
}

HealthServer::HealthServer() {
  server.Get("/", [](const httplib::Request&, httplib::Response& res) {
    res.status = 200;
    res.set_content("Bot is alive\n", "text/plain");
  });

  server.Get("/health", [this](const httplib::Request&, httplib::Response& res) {
    auto uptime =
      std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::steady_clock::now() - startTime
      );

    std::string body =
      "{"
      "\"status\":\"ok\","
      "\"service\":\"telegram-bot\","
      "\"uptime\":\"" + formatUptime(uptime) + "\""
      "}";

    res.status = 200;
    res.set_content(body, "application/json");
  });
}

HealthServer::~HealthServer() {
  stop();
}

void HealthServer::start() {
  if (running)
    return;

  running = true;
  startTime = std::chrono::steady_clock::now();

  int port = 8080;

  if (const char* env = std::getenv("PORT"))
    port = std::stoi(env);

  serverThread = std::thread([this, port]() {
    std::cout << "[Health] Listening on port "
              << port
              << std::endl;

    server.listen("0.0.0.0", port);
  });
}

void HealthServer::stop() {
  if (!running)
    return;

  running = false;

  server.stop();

  if (serverThread.joinable())
    serverThread.join();
}
