#pragma once

#include <thread>
#include <fstream>
#include <string>
#include <mutex>
#include <atomic>

#include <core/RingBuffer.hpp>

class Logger
{
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
    char writeBuffer[4096];
    CachedTimestamp cachedTimestamp;


    static Logger _instance;

    std::ofstream outputFile;
    RingBuffer<Message, 64> messageQueue;

    std::mutex consoleMutex;
    std::mutex initMutex;
    std::jthread workerThread;
    std::atomic<bool> running = false;

    bool initialized = false;
    bool isShutdown = false;

    Logger() = default;
    ~Logger();

    static void ProcessQueue();
    static uint32_t GetThreadId();
    void WriteMessage(const Message& msg);
    static std::time_t GetTimestamp();
    char* ToString(const std::time_t& time);

    static const char* LevelToString(Level level);

    static void Log(Level level, const std::string& category, const std::string& text);

public:

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static void Initialize(const std::string& filename);
    static void Shutdown();

    static void Debug   (const std::string& category, const std::string& text);
    static void Info    (const std::string& category, const std::string& text);
    static void Warning (const std::string& category, const std::string& text);
    static void Error   (const std::string& category, const std::string& text);
    static void Critical(const std::string& category, const std::string& text);
};
