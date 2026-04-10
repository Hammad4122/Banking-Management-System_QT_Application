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
private:
    QLabel *dashTitleLabel;
    QLabel *dashTitleLogoLabel;
    QLabel *userImgLabel;
    QPushButton *settingBtn;
    QPushButton *notificationBtn;
    QPushButton *logoutBtn;
};

#endif // DASHBOARD_H
