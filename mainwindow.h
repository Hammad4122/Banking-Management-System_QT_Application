#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include "loginwindow.h"
#include "dashboardwindow.h"
#include "signupwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void updateButtonStyles(QPushButton*);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton *dashboard;
    QPushButton *transactions;
    QPushButton *accounts;
    QVBoxLayout *contentLayout; // Move this from constructor to class member
    QStackedWidget *stackedWidget;
    LoginWindow *loginPage;
    DashboardWindow *dashboardPage;
    SignupWindow *signupPage;


    void showDashboard();
    void showTransactions();
    void showAccounts();
    void clearLayout(QLayout *layout);

};
#endif // MAINWINDOW_H
