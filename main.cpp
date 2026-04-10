#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <conio.h>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // Q_INIT_RESOURCE(resources);

    QApplication app(argc, argv);

    MainWindow window;

    window.show();

    return app.exec();
}
