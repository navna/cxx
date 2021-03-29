#include "settings.h"

#include <stdexcept>

using namespace std;

Settings::Settings() :
    _fishCount((FISH_COUNT_MIN + FISH_COUNT_MAX) / 2),
    _speed((SPEED_MIN + SPEED_MAX) / 2) { }

int Settings::fishCount() const {
    return _fishCount;
}

int Settings::speed() const {
    return _speed;
}

#include <iostream>

void Settings::setFishCount(int fishCount) {
    if (fishCount < FISH_COUNT_MIN || FISH_COUNT_MAX < fishCount) {
        throw invalid_argument("fishCount");
    }
    _fishCount = fishCount;
    std::cout << "new fish count: " << _fishCount << std::endl;
}

void Settings::setSpeed(int speed) {
    if (speed < SPEED_MIN || SPEED_MAX < speed) {
        throw invalid_argument("speed");
    }
    _speed = speed;
    std::cout << "new speed: " << _speed << std::endl;
}
