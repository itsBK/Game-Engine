#include <core/Logger.hpp>

#include <vector>
#include <iostream>

void WorkerFunction(int id)
{
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < 1000; ++i)
    {
        Logger::Info("Gameplay", "Worker " + std::to_string(id) +
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
    for (int k = 0 ; k < 100; ++k)
    {
        std::cout << "\nrun number: " << k << std::endl;
        auto start = std::chrono::system_clock::now();
        Logger::Initialize("engine.log");
        Logger::Info("Engine", "Game engine started");

        std::vector<std::jthread> workers;

        for (int i = 0; i < 4; ++i)
        {
            workers.emplace_back(WorkerFunction, i);
        }

        for (auto& thread : workers)
        {
            thread.join();
        }

        Logger::Warning("Renderer", "Texture streaming nearing limit");
        Logger::Critical("Audio", "Failed to load sound bank");

        Logger::Shutdown();

        auto endShutdown = std::chrono::system_clock::now();
        auto total =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                endShutdown - start
            );
        std::cout
            << "Total runtime ms: "
            << total.count()
            << '\n';
    }
    return 0;
}
