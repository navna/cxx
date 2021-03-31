#pragma once

#include <list>
#include <random>
#include <vector>

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QPixmap>
#include <QSize>

#include "settings.h"

class AquariumWindow : public QMainWindow {
    Q_OBJECT

private:
    const int _timerInterval = 50;
    const QSize _maxFishSize;
    Settings _settings;
    QGraphicsScene* _scene;                       // Сцена с фоном и рыбками
    QSize _sceneSize;                             // Размеры фона
    std::vector<QPixmap> _fishes;                 // Предварительно загруженные изображения рыб
    std::list<QGraphicsPixmapItem*> _sceneFishes; // Рыбки на сцене
    std::mt19937 _random;                         // ГПСЧ


private slots:
    void showSettings();
    void updateScene();

public:
    AquariumWindow(const QSize& maxBackgroundSize, const QSize& maxFishSize);

    AquariumWindow(const AquariumWindow&) = delete;

    AquariumWindow& operator=(const AquariumWindow&) = delete;
};
