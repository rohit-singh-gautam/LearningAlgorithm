#include <chrono>
#include <atomic>
#include <algorithm>
#include <deque>
#include <iostream>

namespace rohit {

class RateLimiterTokenBucket {
    const size_t max_token;
    size_t token_count;
    const std::chrono::nanoseconds token_add_duration;
    std::chrono::steady_clock::time_point last_refill;

public:
    RateLimiterTokenBucket(size_t max_token, const std::chrono::nanoseconds token_add_duration) : 
        max_token { max_token }, token_count { max_token },
        token_add_duration { token_add_duration },
        last_refill { std::chrono::steady_clock::now() } { }

    bool IsAllowed() {
        auto current_time = std::chrono::steady_clock::now();
        auto last_duration = current_time - last_refill;
        size_t tokens_to_add = last_duration / token_add_duration;
        if (tokens_to_add) {
            size_t new_token_count = token_count + tokens_to_add;
            token_count = std::min(new_token_count, max_token);
            last_refill += tokens_to_add * token_add_duration;
        }
        if (token_count) {
            --token_count;
            return true;
        }
        return false;
    }
};

class RateLimiterLeakyBucket {
    const size_t max_token;
    size_t token_count;
    const std::chrono::nanoseconds token_leak_duration;
    std::chrono::steady_clock::time_point last_leak;

public:
    RateLimiterLeakyBucket(const size_t max_token, const std::chrono::nanoseconds token_leak_duration) : 
        max_token { max_token }, token_count { max_token },
        token_leak_duration { token_leak_duration },
        last_leak { std::chrono::steady_clock::now() } { }

    void leak() {
        auto current_time = std::chrono::steady_clock::now();
        auto last_duration = current_time - last_leak;
        size_t token_to_leak = last_duration / token_leak_duration;
        if (token_count < token_to_leak) token_count = 0;
        else token_count -= token_to_leak;
        last_leak += token_leak_duration * token_to_leak;
    }

    bool AddToken() {
        leak();
        if (token_count + 1 <= max_token) {
            ++token_count;
            return true;
        } else {
            return false;
        }
    }

};

class RateLimiterSlidingWindowLogs {
    const size_t max_count;
    const std::chrono::nanoseconds window_duration;

    std::deque<std::chrono::steady_clock::time_point> TimestampLogs { };

public:
    RateLimiterSlidingWindowLogs(const size_t max_count, const std::chrono::nanoseconds window_duration) :
        max_count { max_count }, window_duration { window_duration } { }

    bool IsAllowed() {
        auto now = std::chrono::steady_clock::now();
        if (TimestampLogs.size() != 0) {
            if (TimestampLogs.back() + window_duration <= now) {
                TimestampLogs.clear();
            } else {
                // At this point TimestampLogs.back() + window_duration is greater than now
                // Hence in 100% case loop will break before or at TimestampLogs.back()
                // This is the rease we are not checking for TimestampLogs.size()
                while(TimestampLogs.front() + window_duration <= now) {
                    TimestampLogs.pop_front();
                }
            }
        }
        if (TimestampLogs.size() < max_count) {
            TimestampLogs.push_back(now);
            return true;
        }
        return false;
    }
};

class RateLimiterSlidingWindowCounter {
    const size_t max_count;
    const std::chrono::nanoseconds window_duration;
    size_t last_count { 0 };
    size_t current_count { 0 };
    std::chrono::steady_clock::time_point current_windows_start;
    std::chrono::steady_clock::time_point last_windows_start;

public:
    RateLimiterSlidingWindowCounter(const size_t max_count, const std::chrono::nanoseconds window_duration) :
        max_count { max_count }, window_duration { window_duration }, current_windows_start { std::chrono::steady_clock::now() },
        last_windows_start { current_windows_start - window_duration } { }

    // Cases to handle
    // current_windows_start is more than 2 * windows duration from now; always return true and use current time - window_duration as last_windows_start
    //                      use current time as current_windows_start
    // current_windows_start is more than windows duration from now; current_windows_start + window_duration is new current current_windows_start and
    //                      last_windows_start = current_windows_start

    bool IsAllowed() {
        auto now = std::chrono::steady_clock::now();
        auto current_duration = now - current_windows_start;
        if (current_duration > window_duration) {
            if (current_duration >= 2*window_duration) {
                last_count = 0;
                current_count = 1;
                current_windows_start = now;
                return true;
            }
            last_count = current_count;
            last_windows_start = current_windows_start;
            current_windows_start += window_duration;
            current_count = 0;
        }
        auto carry_over = last_count - ( (last_count * current_duration) / window_duration);
        if (carry_over + current_count + 1 > max_count) return false;
        ++current_count;
        return true;
    }

};

} //namespace rohit
