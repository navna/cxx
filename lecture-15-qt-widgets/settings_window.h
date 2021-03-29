#pragma once

#include <QWidget>

#include "settings.h"

class SettingsWindow : public QWidget {
    Q_OBJECT

private:
    Settings& _settings;

private slots:
    void onFishCountChanged(int value);

    void onSpeedChanged(int value);

public:
    explicit SettingsWindow(Settings& settings);

    SettingsWindow(const SettingsWindow&) = delete;

    SettingsWindow& operator=(const SettingsWindow&) = delete;
};
