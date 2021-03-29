#pragma once

class Settings final {
    int _fishCount;
    int _speed;

public:
    static const int FISH_COUNT_MIN = 2;
    static const int FISH_COUNT_MAX = 100;
    static const int SPEED_MIN = 50;
    static const int SPEED_MAX = 300;

    Settings();
    Settings(const Settings&) = delete;

    Settings& operator=(const Settings&) = delete;

    int fishCount() const;
    int speed() const;
    void setFishCount(int fishCount);
    void setSpeed(int speed);
};
