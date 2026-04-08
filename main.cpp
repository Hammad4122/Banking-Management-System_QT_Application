#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mainwindow.h"
#include "database.h"
#include <conio.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;

    BankDB bank;

    bank.connectDB();
    bank.registerUser("Muhammad Hammad", "Ateeq", "hammad4122", "muhammadhammadateeq@gmail.com", "412270poF@#$", "03025823781");
    if (bank.loginUser("hammad4122", "412270poF@#")){
        bank.createAccount(1,"PKR");
        bank.deposit(1,5000,"Sample Amount");
    }
    else{
        qDebug() << "Access Denied! Incorrect Username or Password";
    }

    getch();
    return 0;
}
