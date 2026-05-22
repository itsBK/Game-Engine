#pragma once

#include <array>
#include <atomic>

/// Multiple-Producer-Single-Consumer RingBuffer with N = 2^x
template<typename T, size_t N>
class RingBuffer
{
    static_assert((N & (N - 1)) == 0,
                  "N must be power of 2");


    alignas(64) std::array<T, N> buffer;
    alignas(64) std::array<bool, N> sequence;
    alignas(64) std::atomic<size_t> writeHead{ 0 };
    alignas(64) std::atomic<size_t> readHead{ 0 };

public:

    bool push(const T& item)
    {
        // we first secure a space to write data into and increment head for other writers
        auto pos = writeHead.fetch_add(1, std::memory_order_relaxed);
        std::atomic_ref<bool> ref { sequence[pos % N] };
        while (ref.load(std::memory_order_acquire)) {}
        buffer[pos % N] = item;
        ref.store(true, std::memory_order_release);

        return true;
    }

    bool empty()
    {
        auto pos = readHead.load(std::memory_order_acquire);
        std::atomic_ref<bool> ref { sequence[pos % N] };
        return !ref.load(std::memory_order_acquire);
    }

    T pop()
    {
        size_t pos = readHead.fetch_add(1, std::memory_order_relaxed);
        std::atomic_ref<bool> ref { sequence[pos % N] };
        while (!ref.load(std::memory_order_acquire)) {}

        T result = buffer[pos % N];
        ref.store(false, std::memory_order_release);
        return result;
    }

    size_t size() const
    {
        int remaining = writeHead.load(std::memory_order_acquire) - readHead.load(std::memory_order_acquire);
        return remaining;
    }

};
