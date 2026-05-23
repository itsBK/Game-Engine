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

/// Multi-Producer-Single-Consumer RingBuffer with N = 2^x
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
        size_t pos = _head++;

        // if the buffer is already full, we risk overwriting old data before it is written, we account for that by waiting
        while (_dataStored[pos & MASK].test())
        {
            // delaying the producers from looping endlessly when buffer is full,
            // this improves the performance by quite a lot, when reading data one by one using pop()
            // but does little to no effect when draining data by chunks at a time
            for (int i = 0; i < 10000; i++)
                CPU_PAUSE();    // wait for one CPU cycle
        }
        _buffer[pos & MASK] = item;

        // only after writing data, we set the flag for this spot as saved
        _dataStored[pos & MASK].test_and_set();
        ++_count;
    }

    bool empty() const
    {
        return _count == 0;
    }

    /// pop assumes there is new data to pop, or it blocks until new data is available (unrecommended)
    T pop()
    {
        // only one producer so no extra checks are needed
        size_t pos = _tail++;

        // we may be reading the data before it is ready to read
        // e.g. A and B try to push, A gets stuck (descheduled) and B finishes and increments count,
        // --> we stop at A to read, but it is not ready yet)
        // we wait for the next most data slot to be done
        while (!_dataStored[pos & MASK].test())
        {
            // we rarely enter this domain so waiting only a bit is enough
            for (int i = 0; i < 100; i++)
                CPU_PAUSE();
        }
        T result = _buffer[pos & MASK];

        _dataStored[pos & MASK].clear();
        --_count;

        return result;
    }

    /// this method improve the performance a lot if the consumer is popping data slower than the producers are pushing it.
    /// It still does all the safety checks to ensure the data read, is complete.
    /// @param array fixed-size list in which the data will be saved in
    /// @param max the maximum size of chunk to read, ideally half the size of the ring buffer or less
    /// @return the number of items drained from the ring buffer, 0 if the buffer is empty
    size_t drain(T* array, const size_t max)
    {
        size_t countToDrain = std::min(max, _count.load());
        if (countToDrain == 0)
            return 0;

        for (size_t i = 0; i < countToDrain; ++i)
        {
            size_t pos = _tail++;
            while (!_dataStored[pos & MASK].test())
            {
                // we rarely enter this domain so waiting only a bit is enough
                for (int j = 0; j < 100; j++)
                    CPU_PAUSE();
            }
            array[i] = _buffer[pos & MASK];
            _dataStored[pos & MASK].clear();
        }

        _count -= countToDrain;
        return countToDrain;
    }

    size_t size() const
    {
        return _count;
    }
};
