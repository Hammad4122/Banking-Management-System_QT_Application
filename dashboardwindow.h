#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include "basepage.h"
#include <QLabel>
#include <QStackedWidget>
#include <qboxlayout.h>

// Forward declarations
class UserSessionHandler;
class UserDashboardWindow;
class AdminDashboardWindow;

/**
 * DashboardWindow
 *
 * Acts as the top-level "shell" that contains:
 *  - The shared header bar (logo, title, theme toggle, logout, settings)
 *  - A content area that switches between UserDashboardWindow and AdminDashboardWindow
 *
 * This follows the composite pattern: header is defined once here;
 * each sub-dashboard fills the content pane below it.
 */
class DashboardWindow : public BasePage
{
    Q_OBJECT
public:
    explicit DashboardWindow(QWidget *parent = nullptr);

    // Called by MainWindow after a successful user login
    void initializeUserDashboard(UserSessionHandler* session);

    // Called by MainWindow after a successful admin login
    void initializeAdminDashboard();

signals:
    void logoutRequested();
    void themeChangeRequested();

private:
    // Header widgets
    QLabel          *dashTitleLabel;
    QLabel          *userAccountNo;
    QLabel          *userImgLabel;
    QPushButton     *settingBtn;
    QPushButton     *notificationBtn;
    QPushButton     *logoutBtn;

    // Content switcher
    QStackedWidget      *contentStack;
    UserDashboardWindow *userDashboard;
    AdminDashboardWindow *adminDashboard;

    void buildHeader(QVBoxLayout *mainLayout);
};

#endif // DASHBOARDWINDOW_H
