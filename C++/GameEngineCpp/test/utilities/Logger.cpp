#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <iomanip>
#include <vector>

#include <core/RingBuffer.hpp>

class Logger
{
public:
    enum class Level
    {
        Debug,
        Info,
        Warning,
        Error,
        Critical
    };

    struct CachedTimestamp
    {
        time_t lastSecond = 0;
        char formatted[32];
    };

    struct Message
    {
        std::time_t timestamp;
        uint32_t threadId;
        Level level;
        std::string category;
        std::string text;
    };
    char buffer[4096];
    CachedTimestamp cachedTimestamp;


private:
    std::ofstream outputFile;

    RingBuffer<Message, 4096> messageQueue;

    std::mutex consoleMutex;
    std::mutex initMutex;

    std::jthread workerThread;
    std::atomic<bool> running = false;

    bool initialized = false;
    bool isShutdown = false;

    Logger() = default;
    ~Logger()
    {
        if (!isShutdown)
            Shutdown();
    }

    void ProcessQueue()
    {
        Message msgList[1024];
        auto start = GetTimestamp();
        while (running)
        {
            size_t count = messageQueue.drain(msgList, 1024);
            if (count == 0)
                std::this_thread::sleep_for(std::chrono::microseconds(1));

            for (size_t i = 0; i < count; i++)
                WriteMessage(msgList[i]);

            auto now = GetTimestamp();
            //only flush once a second
            if (now != start)
            {
                outputFile.flush();
                std::cout << "flushing" << std::endl;
                start = now;
            }
        }
    }

    void WriteMessage(const Message& msg)
    {
        snprintf(
            buffer,
            sizeof(buffer),
            "[%s] [Thread %d] [%s] [%s] %s",
            ToString(msg.timestamp),
            msg.threadId,
            LevelToString(msg.level),
            msg.category.c_str(),
            msg.text.c_str()
        );

        // Console output
        {
            // std::lock_guard<std::mutex> consoleLock(consoleMutex);
            // std::cout << buffer << std::endl;
        }

        // File output
        outputFile << buffer << "\n";
    }

    std::time_t GetTimestamp()
    {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        return time;
    }

    char* ToString(const std::time_t& time)
    {
        if (time == cachedTimestamp.lastSecond)
        {
            return cachedTimestamp.formatted;
        }

        std::tm tm;

#ifdef _WIN32
        localtime_s(&tm, &time);
#else
        localtime_r(&time, &tm);
#endif

        std::stringstream ss;

        ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

        cachedTimestamp.lastSecond = time;

        auto text = ss.str();
        text.copy(cachedTimestamp.formatted, sizeof(cachedTimestamp.formatted) - 1);
        cachedTimestamp.formatted[text.size()] = '\0';

        return cachedTimestamp.formatted;
    }

    const char* LevelToString(Level level)
    {
        switch (level)
        {
            case Level::Debug:    return "DEBUG";
            case Level::Info:     return "INFO";
            case Level::Warning:  return "WARNING";
            case Level::Error:    return "ERROR";
            case Level::Critical: return "CRITICAL";
            default:              return "UNKNOWN";
        }
    }

public:
    static Logger& Instance()
    {
        static Logger instance;
        return instance;
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void Initialize(const std::string& filename)
    {
        std::lock_guard<std::mutex> lock(initMutex);

        if (initialized)
            return;

        outputFile.open(filename, std::ios::out | std::ios::app);

        if (!outputFile.is_open())
        {
            throw std::runtime_error("Failed to open log file");
        }

        running = true;
        workerThread = std::jthread(&Logger::ProcessQueue, this);

        initialized = true;
    }

    void Shutdown()
    {
        auto start = std::chrono::system_clock::now();
        std::cout << "unfinished logs: " << messageQueue.size() << std::endl;
        std::cout << "shutdown started" << std::endl;
        running = false;

        if (workerThread.joinable())
        {
            workerThread.join();
        }

        if (outputFile.is_open())
        {
            outputFile.flush();
            outputFile.close();
        }

        auto end = std::chrono::system_clock::now();
        auto total = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "shutdown finished, took: " << total.count() << std::endl;
        isShutdown = true;
    }

    static uint32_t GetThreadId()
    {
        static std::atomic<uint32_t> globalId{0};
        thread_local uint32_t threadId =
            globalId.fetch_add(1, std::memory_order_relaxed);

        return threadId;
    }

    void Log(Level level, const std::string& category, const std::string& text)
    {
        if (!initialized)
            return;

        Message msg;
        msg.timestamp = GetTimestamp();
        msg.threadId = GetThreadId();
        msg.level = level;
        msg.category = category;
        msg.text = text;

        messageQueue.push(msg);
    }
};

// ------------------------------------------------------------
// Convenience Macros
// ------------------------------------------------------------

#define LOG_DEBUG(category, message)        Logger::Instance().Log(Logger::Level::Debug,    category, message)
#define LOG_INFO(category, message)         Logger::Instance().Log(Logger::Level::Info,     category, message)
#define LOG_WARNING(category, message)      Logger::Instance().Log(Logger::Level::Warning,  category, message)
#define LOG_ERROR(category, message)        Logger::Instance().Log(Logger::Level::Error,    category, message)
#define LOG_CRITICAL(category, message)     Logger::Instance().Log(Logger::Level::Critical, category, message)

// ------------------------------------------------------------
// Example Usage
// ------------------------------------------------------------

void WorkerFunction(int id)
{
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < 1000000; ++i)
    {
        LOG_INFO("Gameplay", "Worker " + std::to_string(id) +
                 " processed frame " + std::to_string(i));

    }

    //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    auto end = std::chrono::system_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout
        << "thread "<< id << " runtime ms: "
        << total.count()
        << '\n';
}

int main()
{
    auto start = std::chrono::system_clock::now();
    Logger::Instance().Initialize("engine.log");
    LOG_INFO("Engine", "Game engine started");

    std::vector<std::jthread> workers;

    for (int i = 0; i < 4; ++i)
    {
        workers.emplace_back(WorkerFunction, i);
    }

    for (auto& thread : workers)
    {
        thread.join();
    }

    LOG_WARNING("Renderer", "Texture streaming nearing limit");
    LOG_ERROR("Audio", "Failed to load sound bank");

    Logger::Instance().Shutdown();

    auto endShutdown = std::chrono::system_clock::now();
    auto total =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            endShutdown - start
        );
    std::cout
        << "Total runtime ms: "
        << total.count()
        << '\n';

    return 0;
}