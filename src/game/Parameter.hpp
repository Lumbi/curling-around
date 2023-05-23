#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>
#include <unordered_map>

#define PARAMETER_KEYS \
    X(Actor_CurlingStone_Mass) \
    X(Actor_CurlingStone_Bounciness) \
    X(Player_CurlingStone_SpawnDistance) \
    X(Player_Camera_Speed) \
    X(Player_Aim_Speed) \
    X(Player_Charge_Speed) \
    X(Player_Swing_Distance) \
    X(Player_Shot_Speed_Min) \
    X(Player_Shot_Speed_Max) \
    X(Player_EndTurn_WaitDelay) \

/// @brief Singleton class providing parameter values that can be changed at runtime.
class Parameter {
    public:
        /// @brief The key to the parameter.
        enum class Key {
            #define X(parameterKeyName) parameterKeyName,
            PARAMETER_KEYS
            #undef X
        };

        /// @brief The type of the parameter value.
        ///        Currently only floats are supported but there could be different types.
        using Value = float;

    public:
        /// @brief Get the singleton instance.
        static Parameter& shared();

        /// @brief Update the parameter list for a single frame.
        ///        The parameters are not reloaded every frame but periodically after a time interval.
        void update();

        /// @brief Load the parameter list from disk.
        void load();

        /// @brief Get the value of the parameter specified by the key.
        /// @param key The key to get the parameter value for.
        /// @param fallback The fallback to use if the key was not found.
        /// @return The value of the parameter or the provided fallback valye if the parameter was not found.
        Parameter::Value get(Parameter::Key key, Parameter::Value fallback = 0.f);

    private:
        const char* parameterFile = "asset/parameters.txt";
        std::unordered_map<Parameter::Key, Parameter::Value> parameters;
        float reloadTimer = 0.f;
        const float reloadDelay = 1.f; // seconds

        Parameter();

        void parseLine(const std::string &);
};

#endif
