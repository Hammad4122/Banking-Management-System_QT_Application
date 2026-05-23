#ifndef USERDASHBOARDWINDOW_H
#define USERDASHBOARDWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include "database.h"
#include "transactiondialog.h"
#include "usersessionhandler.h"

/**
 * UserDashboardWindow
 *
 * Renders the full user-facing dashboard content:
 *   - Debit card widget (balance, card holder, card number)
 *   - Income / Expense summary cards
 *   - Quick action buttons (Deposit, Transfer, Withdraw)
 *   - Recent transaction table
 *
 * It is parented and displayed inside DashboardWindow's QStackedWidget.
 * All data is loaded via UserSessionHandler (the DTO / session object).
 */
class UserDashboardWindow : public QWidget
{
    Q_OBJECT
public:
    explicit UserDashboardWindow(QWidget *parent = nullptr);

    /**
     * Populate the dashboard with data from the session DTO.
     * Call this every time the user logs in or the balance changes.
     */
    void loadSession(UserSessionHandler *session);

signals:
    void themeChangeRequested();    // Forwarded to shell

private slots:
    void onDepositClicked();
    void onTransferClicked();
    void onWithdrawClicked();

private:
    // ── Card area ──────────────────────────────────────────────────
    QLabel *userBalance;
    QLabel *cardHolderLabel;
    QLabel *cardExpiryLabel;
    QLabel *cardNumber;
    QLabel *creditChipLabel;
    QLabel *creditCircles;

    // ── Summary cards ──────────────────────────────────────────────
    QLabel *incomeTitleLabel;
    QLabel *incomeAmountLabel;
    QLabel *expenseTitleLabel;
    QLabel *expenseAmountLabel;

    // ── Info labels (user details) ─────────────────────────────────
    QLabel *userGreetFullNameLabel;
    QLabel *usernameLabel;
    QLabel *userEmail;
    QLabel *userMobileNO;

    // ── Action buttons ─────────────────────────────────────────────
    QPushButton *depositBtn;
    QPushButton *transferBtn;
    QPushButton *withdrawBtn;

    // ── Transaction table ──────────────────────────────────────────
    QTableView  *transactionTable;

    // ── State ──────────────────────────────────────────────────────
    UserSessionHandler *m_session = nullptr;
    BankDB              db;

    // ── Helpers ────────────────────────────────────────────────────
    void openTransactionDialog(TransactionType type);
    void refreshBalanceAndTable();
};

#endif // USERDASHBOARDWINDOW_H
