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
    void initializeDashboard(UserSessionHandler*);
private slots:

signals:
    void logoutRequested();
    void themeChangeRequested();
private:
    QLabel *dashTitleLabel;
    QLabel *userImgLabel;
    QPushButton *settingBtn;
    QPushButton *notificationBtn;
    QPushButton *logoutBtn;
    QLabel* creditChipLabel;
    QLabel* creditCircles;

    // User informations

    QLabel* userGreetFullNameLabel;
    QLabel* usernameLabel;
    QLabel* userEmail;
    QLabel* userMobileNO;
    QLabel* userBalance;

    QLabel* cardHolderLabel;
    QLabel* cardExpiryLabel;
    QLabel* cardNumber;

    //Action Buttons
    QPushButton* depositBtn;
    QPushButton* transferBtn;
    QPushButton* withdrawBtn;
};

#endif // DASHBOARD_H
