#include "profile.hpp"

#include <algorithm>
#include <future>
#include <iostream>
#include <mutex>
#include <vector>

constexpr size_t c_ThreadsNumber = 4;
constexpr size_t c_SearchInterval = 1000;

std::vector<unsigned int> g_Primes;
std::mutex g_Mutex;

bool isPrime(unsigned int value) {
    if (value < 2) {
        return false;
    }

    for (unsigned int i = 2; i <= value / 2; i++) {
        if (value % i == 0) {
            return false;
        }
    }

    return true;
}

void checkInterval(unsigned int from, unsigned int to) {
    for (unsigned int i = from; i <= to; i++) {
        if (isPrime(i)) {
            g_Mutex.lock();
            g_Primes.push_back(i);
            g_Mutex.unlock();
        }
    }
}

int main() {
    LogDuration logger{"Search Time"};

    unsigned int searchTarget = 10000;
    unsigned int startFromInterval = 0;

    g_Primes.reserve(searchTarget);

    while (g_Primes.size() < searchTarget) {
        std::vector<std::future<void>> futures;
        size_t begin = startFromInterval;
        size_t end = startFromInterval + c_ThreadsNumber;

        for (size_t i = begin; i < end; i++) {
            futures.push_back(std::async([i = i]() {
                checkInterval(i * c_SearchInterval,
                              (i + 1) * c_SearchInterval - 1);
            }));
        }

        startFromInterval += c_ThreadsNumber;
    }

    std::sort(g_Primes.begin(), g_Primes.end());

    std::cout << g_Primes[searchTarget - 1] << std::endl;
}