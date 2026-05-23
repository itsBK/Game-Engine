#pragma once

#include <array>
#include <atomic>

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386)   || defined(_M_IX86)
    #include <immintrin.h>
    #define CPU_PAUSE() _mm_pause()
#elif defined(__aarch64__) || defined(__arm__) || defined(_M_ARM)
    #if defined(_MSC_VER)
        #include <intrin.h>
        #define CPU_PAUSE() __yield()
    #else
        #define CPU_PAUSE() __asm__ volatile("yield")
    #endif
#else
    // Fallback for unknown architectures
    #define CPU_PAUSE() ((void)0)
#endif

/// Multiple-Producer-Single-Consumer RingBuffer with N = 2^x
template<typename T, size_t N>
class RingBuffer
{
    static_assert((N & (N - 1)) == 0, "N must be power of 2");
    static constexpr size_t MASK = N - 1;

    alignas(64) std::array<T, N> _buffer;
    alignas(64) std::array<std::atomic_flag, N> _dataStored;
    alignas(64) std::atomic<size_t> _head = { 0 };   // head is where the latest producer (writer) is
    alignas(64) std::atomic<size_t> _tail = { 0 };   // tail is where the consumer (reader) is
    alignas(64) std::atomic<size_t> _count = { 0 };  // count of ready-to-read data

public:

    void push(const T& item)
    {
        // we first secure a space to write data into and increment head for other writers
        size_t pos = _head.fetch_add(1, std::memory_order_seq_cst);

        // if the buffer is already full, we risk overwriting old data before it is written, we account for that by waiting
        while (_dataStored[pos & MASK].test(std::memory_order_seq_cst))
        {
            // delaying the producers from looping endlessly when buffer is full, improves the performance by quite a bit (in stress testing at least)
            for (int i = 0; i < 10000; i++)
                CPU_PAUSE();    // wait for one CPU cycle
        }
        _buffer[pos & MASK] = item;

        // only after writing data, we set the flag for this spot as saved
        _dataStored[pos & MASK].test_and_set(std::memory_order_seq_cst);
        _count.fetch_add(1, std::memory_order_seq_cst);
    }

    bool empty() const
    {
        return _count.load(std::memory_order_seq_cst) == 0;
    }

    /// pop assumes there is new data to pop, or it blocks until new data is available (unrecommended)
    T pop()
    {
        // only one producer so no extra checks are needed
        size_t pos = _tail.fetch_add(1, std::memory_order_seq_cst);

        // we may be reading the data before it is ready to read
        // e.g. A and B try to push, A gets stuck (descheduled) and B finishes and increments count,
        // --> we stop at A to read, but it is not ready yet)
        // we wait for the next most data slot to be done
        while (!_dataStored[pos & MASK].test(std::memory_order_seq_cst))
        {
            // we rarely enter this domain so waiting only a bit is enough
            for (int i = 0; i < 100; i++)
                CPU_PAUSE();
        }
        T result = _buffer[pos & MASK];

        _dataStored[pos & MASK].clear(std::memory_order_seq_cst);
        _count.fetch_sub(1, std::memory_order_seq_cst);

        return result;
    }

    size_t size() const
    {
        return _count.load(std::memory_order_seq_cst);
    }
};
