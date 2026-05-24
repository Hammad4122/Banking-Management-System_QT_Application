#ifndef ADMINDASHBOARDWINDOW_H
#define ADMINDASHBOARDWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QTabWidget>
#include "database.h"

/**
 * AdminDashboardWindow
 *
 * The admin control panel.  Displayed inside DashboardWindow's content stack
 * when an admin logs in.
 *
 * Tabs:
 *   1. Overview   – total users, total deposits, total withdrawals, system balance
 *   2. Users      – searchable table of all registered users
 *   3. Accounts   – table of all accounts with balances
 *   4. Credentials – change admin username / password (hardcoded admin)
 */
class AdminDashboardWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AdminDashboardWindow(QWidget *parent = nullptr);

    /** Refresh all data from the database (call after login or any DB change). */
    void loadData();

signals:
    void themeChangeRequested();

private slots:
    void onChangeCredentials();
    void onSearchUsers(const QString &text);

private:
    // ── Tab widget ─────────────────────────────────────────────────
    QTabWidget *tabWidget;

    // ── Overview tab ───────────────────────────────────────────────
    QLabel *totalUsersLabel;
    QLabel *totalBalanceLabel;
    QLabel *totalDepositsLabel;
    QLabel *totalWithdrawalsLabel;

    // ── Users tab ──────────────────────────────────────────────────
    QLineEdit  *searchField;
    QTableView *usersTable;

    // ── Accounts tab ───────────────────────────────────────────────
    QTableView *accountsTable;

    // ── Credentials tab ────────────────────────────────────────────
    QLineEdit *newUsernameField;
    QLineEdit *currentPassField;
    QLineEdit *newPassField;
    QLineEdit *confirmPassField;
    QLabel    *credStatusLabel;
    QPushButton *changeCredBtn;

    // ── DB ─────────────────────────────────────────────────────────
    BankDB db;

    // ── Tab builders ───────────────────────────────────────────────
    QWidget *buildOverviewTab();
    QWidget *buildUsersTab();
    QWidget *buildAccountsTab();
    QWidget *buildCredentialsTab();

    void refreshOverview();
    void refreshUsersTable(const QString &filter = "");
    void refreshAccountsTable();
};

#endif // ADMINDASHBOARDWINDOW_H
