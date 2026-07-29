#include "health_server.h"

#include <cstdlib>
#include <iostream>

HealthServer::HealthServer() {
      server.Get("/", [](const httplib::Request&, httplib::Response& res) {
                  res.set_content("Bot is alive\n", "text/plain");
                          res.status = 200;
                              });

          server.Get("/health", [](const httplib::Request&, httplib::Response& res) {
                      res.set_content("OK\n", "text/plain");
                              res.status = 200;
                                  });
}

HealthServer::~HealthServer() {
      stop();
}

void HealthServer::start() {
      if (running) {
                return;
                    }

          running = true;

              int port = 8080;

                  if (const char* env = std::getenv("PORT")) {
                            port = std::stoi(env);
                                }

                      serverThread = std::thread([this, port]() {
                                  std::cout << "[Health] Listening on port " << port << std::endl;

                                          server.listen("0.0.0.0", port);
                                              });
}

void HealthServer::stop() {
      if (!running) {
                return;
                    }

          running = false;

              server.stop();

                  if (serverThread.joinable()) {
                            serverThread.join();
                                }
}
