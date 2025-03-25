#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Set the application style to Fusion/windows/windowsvista or another available style
    QApplication::setStyle(QStyleFactory::create("windows"));

    MainWindow w;
    w.show();

    return a.exec();
}
