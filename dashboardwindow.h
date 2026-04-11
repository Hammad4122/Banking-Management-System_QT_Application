#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include "basepage.h"
#include <qmainwindow.h>
#include <QLabel>
class DashboardWindow: public BasePage
{
    Q_OBJECT
public:
    explicit DashboardWindow(QWidget *parent = nullptr);
private slots:

signals:
    void logoutRequested();
    void themeChangeRequested();
private:
    QLabel *dashTitleLabel;
    QLabel *userImgLabel;
    QLabel *greetUser;
    QPushButton *settingBtn;
    QPushButton *notificationBtn;
    QPushButton *logoutBtn;
};

#endif // DASHBOARD_H
