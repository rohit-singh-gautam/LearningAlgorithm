#include "RateLimiter.h"
#include <thread>
#include <iostream>

void testTokenBucket() {
    rohit::RateLimiterTokenBucket tokenbucket {20, std::chrono::milliseconds { 1 } };
    std::cout << "Testing Token Bucket: ";
    for(int i = 0; i < 40; ++i)
    {
        auto allowed = tokenbucket.IsAllowed();
        std::string test = allowed ? "t" : "f";
        std::cout << test;
        if (i == 25) std::this_thread::sleep_for(std::chrono::milliseconds { 5 });
    }
    std::cout << std::endl;
}

void testLeakyBucket() {
    rohit::RateLimiterLeakyBucket leakybucket {20, std::chrono::milliseconds { 1 } };
    std::cout << "Testing Token Bucket: ";
    for(int i = 0; i < 40; ++i)
    {
        if (i == 5 || i == 25) std::this_thread::sleep_for(std::chrono::milliseconds { 10 });
        auto allowed = leakybucket.AddToken();
        std::string test = allowed ? "t" : "f";
        std::cout << test;
    }
    std::cout << std::endl;
}

void testSlidingWindowsLogs() {
    rohit::RateLimiterSlidingWindowLogs slidingwindow {20, std::chrono::milliseconds { 20 } };
    std::cout << "Testing Token Bucket: ";
    for(int i = 0; i < 40; ++i)
    {
        if (i == 5 || i == 25) std::this_thread::sleep_for(std::chrono::milliseconds { 10 });
        auto allowed = slidingwindow.IsAllowed();
        std::string test = allowed ? "t" : "f";
        std::cout << test;
    }
    std::cout << std::endl;
}

void testSlidingWindowsCounter() {
    rohit::RateLimiterSlidingWindowCounter slidingwindow {20, std::chrono::milliseconds { 20 } };
    std::cout << "Testing Token Bucket: ";
    for(int i = 0; i < 40; ++i)
    {
        if (i == 5 || i == 25) std::this_thread::sleep_for(std::chrono::milliseconds { 15 });
        auto allowed = slidingwindow.IsAllowed();
        std::string test = allowed ? "t" : "f";
        std::cout << test;
    }
    std::cout << std::endl;
}

int main(int , char **) {
    testTokenBucket();
    testLeakyBucket();
    testSlidingWindowsLogs();
    testSlidingWindowsCounter();

    return 0;
}
