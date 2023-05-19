#ifndef TIME_H
#define TIME_H

#include <chrono>

class Time {
    public:
        static Time & shared();

        /// @brief Total time in seconds since the start of the execution.
        float time = 0.f;

        /// @brief Time elapsed since last frame in seconds.
        float deltaTime = 0.f;

        /// @brief Update the time instance.
        /// @param elapsedTime The time elapsed in seconds since the last update.
        void update(float elapsedTime);

        void beginFrame();

        void endFrame();

        void sleep(float seconds);

    private:
        Time();

        std::chrono::steady_clock::time_point beginFrameTime;
        std::chrono::steady_clock::time_point endFrameTime;
};

#endif
