#ifndef FORMATTING_HPP
#define FORMATTING_HPP

#include <string>

std::string formatLapTime(float seconds);

std::string formatSectorMS(uint32_t milliseconds);

std::string formatLapTimeMS(uint32_t milliseconds);

std::string formatFloatTo2DP(float value);

float convertKPHtoMPH(float kph);

uint16_t convertKPHtoMPH(uint16_t kph);

std::string formatElapsedTime(float seconds);

std::string formatIntervalTime(uint32_t intervalMS, uint8_t leadDriverLap, uint8_t behindDriverLap);

std::string formatDelta(uint32_t target, uint32_t actual);

#endif  // FORMATTING_HPP
