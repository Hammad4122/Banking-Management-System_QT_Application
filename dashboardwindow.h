#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include "basepage.h"
#include "transactiondialog.h"
#include <qmainwindow.h>
#include <QLabel>
#include <qtableview.h>
class DashboardWindow: public BasePage
{
    Q_OBJECT
public:
    explicit DashboardWindow(QWidget *parent = nullptr);
    void initializeDashboard(UserSessionHandler*);
signals:
    void logoutRequested();
    void themeChangeRequested();
    void depositRequested();
private:
    UserSessionHandler *m_session;
    QLabel *dashTitleLabel;
    QLabel *userImgLabel;
    QPushButton *settingBtn;
    QPushButton *notificationBtn;
    QPushButton *logoutBtn;
    QLabel *creditChipLabel;
    QLabel *creditCircles;

    // Income Card Labels
    QLabel *incomeTitleLabel;
    QLabel *incomeAmountLabel;

    // Expense Card Labels
    QLabel *expenseTitleLabel;
    QLabel *expenseAmountLabel;

    // User informations

    QLabel* userGreetFullNameLabel;
    QLabel* usernameLabel;
    QLabel* userEmail;
    QLabel* userMobileNO;
    QLabel* userBalance;

    QLabel* cardHolderLabel;
    QLabel* cardExpiryLabel;
    QLabel* cardNumber;

    //Action Buttons and Label
    QLabel* quickActionsLabel;
    QPushButton* depositBtn;
    QPushButton* transferBtn;
    QPushButton* withdrawBtn;

    //Transaction Dialog
    TransactionDialog* dialog;

    void updateBalance(UserSessionHandler*);

    // Transaction Table
    QTableView *transactionTable;
};

#endif // DASHBOARD_H
