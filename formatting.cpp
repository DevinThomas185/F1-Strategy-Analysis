#include "formatting.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

std::string formatLapTime(float seconds) {
    int minutes = static_cast<int>(seconds) / 60;
    float remainingSeconds = seconds - minutes * 60;

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << minutes << ":";
    ss << std::setw(2) << std::setfill('0') << static_cast<int>(remainingSeconds) << ".";
    ss << std::setw(3) << std::setfill('0') << static_cast<int>((remainingSeconds - static_cast<int>(remainingSeconds)) * 1000);

    return ss.str();
}

std::string formatSectorMS(uint32_t milliseconds) {
    uint32_t seconds = milliseconds / 1000;
    uint32_t ms = milliseconds % 1000;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << seconds << ".";  // Ensure 2-digit seconds
    oss << std::setfill('0') << std::setw(3) << ms;              // Ensure 3-digit milliseconds

    return oss.str();
}

std::string formatLapTimeMS(uint32_t milliseconds) {
    uint32_t minutes = milliseconds / 60000;
    uint32_t seconds = (milliseconds / 1000) % 60;
    uint32_t ms = milliseconds % 1000;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minutes << ":";  // Ensure 2-digit minutes
    oss << std::setfill('0') << std::setw(2) << seconds << ".";  // Ensure 2-digit seconds
    oss << std::setfill('0') << std::setw(3) << ms;              // Ensure 3-digit milliseconds

    return oss.str();
}

std::string formatFloatTo2DP(float value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << value;
    return oss.str();
}

float convertKPHtoMPH(float kph) {
    return kph / 1.60934;
}

uint16_t convertKPHtoMPH(uint16_t kph) {
    return static_cast<uint16_t>(static_cast<float>(kph) / 1.60934);
}

std::string formatElapsedTime(float seconds)
{
    int hours = seconds / 3600;
    int minutes = (seconds / 60) - (hours * 60);
    int secs = static_cast<int>(std::floor(seconds)) % 60;
    int ms = (seconds - std::floor(seconds)) * 1000;

    std::ostringstream oss;
    oss << std::setfill('0');
    oss << std::setw(2) << hours << ":";
    oss << std::setw(2) << minutes << ":";
    oss << std::setw(2) << secs << ".";
    oss << std::setw(3) << ms;

    return oss.str();
}

std::string formatIntervalTime(uint32_t intervalMS, uint8_t leadDriverLap, uint8_t behindDriverLap)
{
    std::ostringstream oss;

    if (leadDriverLap != behindDriverLap) {
        oss << behindDriverLap - leadDriverLap << " Lap(s)";
    } else {
        uint32_t minutes = intervalMS / 60000;
        uint32_t seconds = (intervalMS / 1000) % 60;
        uint32_t milliseconds = intervalMS % 1000;

        oss << "+";
        if (minutes > 0) oss << minutes << ":" << std::setw(2) << std::setfill('0');
        oss << seconds << "." << std::setw(3) << std::setfill('0') << milliseconds;
    }

    return oss.str();
}

std::string formatDelta(uint32_t target, uint32_t actual) {
    double delta = (static_cast<double>(actual) - target) / 1000.0;
    std::ostringstream oss;
    oss << std::showpos << std::fixed << std::setprecision(3) << delta;
    std::string deltaString = oss.str();
    return deltaString;
}

std::string formatTemperature(uint16_t temperature) {
    return std::to_string(temperature) + "°C";
}

std::string formatPressure(float pressure) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << pressure << " PSI";
    return stream.str();
}

