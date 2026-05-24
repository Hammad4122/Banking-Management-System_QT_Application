#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "loginwindow.h"
#include "dashboardwindow.h"
#include "signupwindow.h"
#include "usersessionhandler.h"

/**
 * MainWindow
 *
 * Top-level window that owns the QStackedWidget and routes between:
 *   Index 0 – LoginWindow
 *   Index 1 – SignupWindow
 *   Index 2 – DashboardWindow (shared shell for user & admin)
 *
 * On login it asks LoginWindow which role was chosen and calls the
 * appropriate DashboardWindow::initializeXxx() method.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void handleTheme();

private:
    QStackedWidget   *stackedWidget;
    LoginWindow      *loginPage;
    SignupWindow     *signupPage;
    DashboardWindow  *dashboardPage;

    UserSessionHandler *currentSession = nullptr;

    void onUserLoggedIn(UserSessionHandler *session);
    void onAdminLoggedIn();
};

#endif // MAINWINDOW_H
