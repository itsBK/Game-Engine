#include "include/core/Logger.hpp"

#include <chrono>
#include <iomanip>

Logger Logger::_instance = {};

Logger::~Logger()
{
    if (!isShutdown)
        Shutdown();
}

void Logger::ProcessQueue()
{
    Message msgList[MAX_MESSAGE_COUNT];
    auto start = GetTimestamp();
    while (true)
    {
        size_t count = _instance.messageQueue.drain(msgList, MAX_MESSAGE_COUNT);
        if (count == 0)
        {
            if (!_instance.running)
                return;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        for (size_t i = 0; i < count; i++)
            _instance.WriteMessage(msgList[i]);

        auto now = GetTimestamp();
        //only flush once a second
        if (now != start)
        {
            _instance.outputFile.flush();
            start = now;
        }
    }
}

void Logger::WriteMessage(const Message& msg)
{
    snprintf(
        writeBuffer,
        sizeof(writeBuffer),
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
    outputFile << writeBuffer << "\n";
}

std::time_t Logger::GetTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    return time;
}

char* Logger::ToString(const std::time_t& time)
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

const char* Logger::LevelToString(Level level)
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

void Logger::Initialize(const std::string& filename)
{
    std::lock_guard<std::mutex> lock(_instance.initMutex);

    if (_instance.initialized)
        return;

    _instance.outputFile.open(filename, std::ios::out | std::ios::app);

    if (!_instance.outputFile.is_open())
    {
        throw std::runtime_error("Failed to open log file");
    }

    _instance.isShutdown = false;
    _instance.running = true;
    _instance.initialized = true;

    _instance.workerThread = std::jthread(&Logger::ProcessQueue);

}

void Logger::Shutdown()
{
    _instance.running = false;

    if (_instance.workerThread.joinable())
    {
        _instance.workerThread.join();
    }

    if (_instance.outputFile.is_open())
    {
        _instance.outputFile.flush();
        _instance.outputFile.close();
    }

    _instance.initialized = false;
    _instance.isShutdown = true;
}

uint32_t Logger::GetThreadId()
{
    static std::atomic<uint32_t> globalId{0};
    thread_local uint32_t threadId =
        globalId.fetch_add(1, std::memory_order_relaxed);

    return threadId;
}

void Logger::Log(Level level, const std::string& category, const std::string& text)
{
    if (!_instance.initialized)
        return;

    Message msg;
    msg.timestamp = GetTimestamp();
    msg.threadId = GetThreadId();
    msg.level = level;
    msg.category = category;
    msg.text = text;

    _instance.messageQueue.push(msg);
}

void Logger::Debug(const std::string& category, const std::string& text)
{
    Log(Level::Debug, category, text);
}

void Logger::Info(const std::string& category, const std::string& text)
{
    Log(Level::Info, category, text);
}

void Logger::Warning(const std::string& category, const std::string& text)
{
    Log(Level::Warning, category, text);
}

void Logger::Error(const std::string& category, const std::string& text)
{
    Log(Level::Error, category, text);
}

void Logger::Critical(const std::string& category, const std::string& text)
{
    Log(Level::Critical, category, text);
}
