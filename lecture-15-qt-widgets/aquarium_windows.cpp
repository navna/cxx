#include "aquarium_window.h"

#include <random>

#include <QDir>
#include <QGraphicsView>
#include <QIcon>
#include <QMenuBar>
#include <QTimer>

#include "settings_window.h"

static QPixmap scale(const QPixmap& bitmap, const QSize& desiredSize) {
    auto size = bitmap.size();
    auto result(bitmap);
    while (size.width() > desiredSize.width() || size.height() > desiredSize.height()) {
        size /= 2;
        result = result.scaled(size);
    }
    return result;
}

void AquariumWindow::showSettings() {
    auto settingWindow = new SettingsWindow(_settings);
    settingWindow->setAttribute(Qt::WA_DeleteOnClose);
    settingWindow->setFixedSize(settingWindow->sizeHint());
    settingWindow->setParent(this);
    settingWindow->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    settingWindow->setWindowModality(Qt::WindowModal);
    settingWindow->show();
}

void AquariumWindow::updateScene() {
    if (_fishes.empty())
        return;

    // Обновление координат каждой рыбки на сцене и удаление при необходимости
    auto it = _sceneFishes.begin();
    auto end = _sceneFishes.end();
    while (it != end) {
        auto sceneFish = *it;
        auto p = sceneFish->pos();
        p.setX(p.x() + (qreal)_timerInterval * (qreal)_settings.speed() / 1000);
        if (p.x() > _sceneSize.width()) {
            it = _sceneFishes.erase(it);
            _scene->removeItem(sceneFish);
            delete sceneFish;
        }
        else {
            sceneFish->setPos(p);
            ++it;
        }
    }

    // Добавление новых рыбок при необходимости
    const auto firstUpdate = _sceneFishes.empty();
    std::uniform_int_distribution<size_t> fishDist(0, _fishes.size() - 1);
    std::uniform_int_distribution<int> xDist(-_maxFishSize.width(), _sceneSize.width());
    std::uniform_int_distribution<int> yDist(0, _sceneSize.height() - _maxFishSize.height());

    while (_sceneFishes.size() < _settings.fishCount()) {
        const auto fishPixmap = _fishes[fishDist(_random)];
        const auto sceneFish = new QGraphicsPixmapItem(fishPixmap);
        const auto x = firstUpdate ? xDist(_random) : -_maxFishSize.width();
        const auto y = yDist(_random);
        sceneFish->setPos(x, y);
        _scene->addItem(sceneFish);
        _sceneFishes.push_back(sceneFish);
    }
}

AquariumWindow::AquariumWindow(const QSize& maxBackgroundSize, const QSize& maxFishSize) : _maxFishSize(maxFishSize) {
    // Загрузка фонового изображения
    QPixmap background("resources/background.jpg");
    background = scale(background, maxBackgroundSize);
    _sceneSize = background.size();

    // Загрузка изображений рыбок
    QDir dir("resources/fishes");
    for (const auto& fishFile : dir.entryInfoList(QDir::Files)) {
        QPixmap fish(fishFile.absoluteFilePath());
        if (!fish.isNull()) {
            fish = scale(fish, maxFishSize);
            _fishes.push_back(fish);
        }
    }

    // Настройка заголовка и макета окна
    setWindowIcon(QIcon("resources/icons/aquarium.png"));
    setWindowTitle("Аквариум");
    const auto fileMenu = menuBar()->addMenu("Файл");
    const auto showSettingsAction = fileMenu->addAction(QIcon("resources/icons/settings.png"), "Настройки");
    const auto exitAction = fileMenu->addAction("Выход");
    QObject::connect(showSettingsAction, &QAction::triggered, this, &AquariumWindow::showSettings);
    QObject::connect(exitAction, &QAction::triggered, this, &QWidget::close);

    // Создание и отображение сцены
    _scene = new QGraphicsScene(this);
    _scene->addItem(new QGraphicsPixmapItem(background));
    const auto view = new QGraphicsView;
    view->setFrameShape(QFrame::Shape::NoFrame);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(_scene);
    setCentralWidget(view);

    // Создание таймера для обновления сцены
    const auto timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &AquariumWindow::updateScene);
    timer->start(_timerInterval);
}
