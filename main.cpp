#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <conio.h>
#include <QDebug>
#include "loginwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LoginWindow login;

    login.show();

    return app.exec();
}
