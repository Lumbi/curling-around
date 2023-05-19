#include "Time.hpp"

#include <thread>

Time & Time::shared()
{
    static Time instance;
    return instance;
}

void Time::update(float elapsedTime)
{
    time += elapsedTime;
    deltaTime = elapsedTime;
}

void Time::beginFrame()
{
    beginFrameTime = std::chrono::steady_clock::now();
}

void Time::endFrame()
{
    endFrameTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> frameExecutionDuration = endFrameTime - beginFrameTime;
    const float frameExecutionSeconds = frameExecutionDuration.count();
    time += frameExecutionSeconds;
    deltaTime = frameExecutionSeconds;
}

void Time::sleep(float seconds)
{
    using namespace std::chrono;
    std::this_thread::sleep_for(duration_cast<milliseconds>(duration<float>(seconds)));
    time += seconds;
    deltaTime += seconds;
}

Time::Time()
{}
