#include <QApplication>

#include "settings_window.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    Settings settings;
    SettingsWindow window(settings);
    window.show();

    return QApplication::exec();
}
