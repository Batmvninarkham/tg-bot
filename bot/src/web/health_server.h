#pragma once
#include <httplib.h>
#include <thread>
#include <atomic>
#include <chrono>
class HealthServer {
  public:
  HealthServer();
~HealthServer();

  void start();
  void stop();

  private:
 httplib::Server server;
 std::thread serverThread;
 std::atomic<bool> running{false};
 std::chrono::steady_clock::time_point startTime;
};
