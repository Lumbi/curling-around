#include "Parameter.hpp"

#include "Time.hpp"

#include <fstream>
#include <string>

#define X(parameterKeyName) { #parameterKeyName, Parameter::Key::parameterKeyName },
static std::unordered_map<std::string, Parameter::Key> stringToParameterKey = {
    PARAMETER_KEYS
};
#undef X

Parameter & Parameter::shared()
{
    static Parameter instance;
    return instance;
}

void Parameter::update()
{
    // Ideally, this feature would be removed at compile time from release builds
    // #ifdef DEBUG
    reloadTimer += Time::shared().deltaTime;
    if (reloadTimer > reloadDelay) {
        load();
        reloadTimer = 0.f;
    }
    // #endif
}

Parameter::Value Parameter::get(Parameter::Key key, Parameter::Value fallback)
{
    if (parameters.contains(key)) {
        return parameters[key];
    } else {
        return fallback;
    }
}

Parameter::Parameter()
{}

void Parameter::load()
{
    std::ifstream parametersFileStream(parameterFile);

    if (!parametersFileStream) {
        printf("[WARNING] Could not open the parameters file.\n");
        return;
    }

    std::string keyValueLine;
    while (std::getline(parametersFileStream, keyValueLine)) {
        parseLine(keyValueLine);
    }
}

void Parameter::parseLine(const std::string &keyValueLine)
{
    if (keyValueLine.empty()) { return; }

    size_t separatorIndex = keyValueLine.find('=');
    if (separatorIndex == std::string::npos) {
        printf("[WARNING] '=' separator missing for parameter entry on line '%s'.\n", keyValueLine.c_str());
        return;
    }

    std::string keyString = keyValueLine.substr(0, separatorIndex);
    std::string valueString = keyValueLine.substr(separatorIndex + 1);

    if (!stringToParameterKey.contains(keyString)) {
        printf("[WARNING] Unrecognized parameter key '%s'.\n", keyString.c_str());
        return;
    }

    Parameter::Key key = stringToParameterKey[keyString];

    if (valueString.empty()) {
        printf("[WARNING] Parameter value for key '%s' was empty.\n", keyString.c_str());
        return;
    }

    try {
        Parameter::Value value = stof(valueString);
        parameters[key] = value;
    } catch (const std::invalid_argument & invalidArgumentException) {
        printf(
            "[WARNING] Invalid format for parameter value in line '%s'. %s\n",
            keyValueLine.c_str(),
            invalidArgumentException.what()
        );
    }
}
