#include "settings_window.h"

#include <QIcon>
#include <QSlider>
#include <QFormLayout>

static QSlider* CreateSlider(const int min, const int max, const int value) {
    auto slider = new QSlider(Qt::Horizontal);
    slider->setFixedWidth(150);
    slider->setMinimum(min);
    slider->setMaximum(max);
    slider->setValue(value);
    return slider;
}

void SettingsWindow::onFishCountChanged(int value) {
    _settings.setFishCount(value);
}

void SettingsWindow::onSpeedChanged(int value) {
    _settings.setSpeed(value);
}

SettingsWindow::SettingsWindow(Settings& settings) : _settings(settings) {
    // Настройка заголовка окна
    setWindowIcon(QIcon("resources/icons/settings.png"));
    setWindowTitle("Настройки");

    // Создание ползунков
    auto fishCountSlider = CreateSlider(Settings::FISH_COUNT_MIN, Settings::FISH_COUNT_MAX, settings.fishCount());
    auto speedSlider = CreateSlider(Settings::SPEED_MIN, Settings::SPEED_MAX, settings.speed());
    QObject::connect(fishCountSlider, &QSlider::valueChanged, this, &SettingsWindow::onFishCountChanged);
    QObject::connect(speedSlider, &QSlider::valueChanged, this, &SettingsWindow::onSpeedChanged);
    
    // Формирование итогового макета
    auto layout = new QFormLayout;
    layout->addRow("Количество рыб:", fishCountSlider);
    layout->addRow("Скорость движения:", speedSlider);

    // Применение макета
    setLayout(layout);
}
