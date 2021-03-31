#include <QApplication>

#include "aquarium_window.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    AquariumWindow window(QSize(1024, 768), QSize(50, 50));
    window.setFixedSize(window.sizeHint());
    window.show();

    return QApplication::exec();
}
