#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

class UserSessionHandler;

/**
 * BankDB
 *
 * Data-access layer for the entire application.
 * All SQL is encapsulated here; the UI never writes raw SQL.
 */
class BankDB
{
public:
    // ── Lifecycle ──────────────────────────────────────────────────
    bool connectDB();
    void disconnectDB();

    // ── User authentication & registration ─────────────────────────
    bool registerUser(const QString &firstName, const QString &lastName,
                      const QString &userName, const QString &email,
                      const QString &cnic, const QString &password,
                      QString &mobile, const QString &tpin);

    int  loginUser(const QString userName, const QString password);
    bool userExist(const QString &userName);
    bool emailExist(const QString &email);
    bool cnicExist(const QString &cnic);
    bool mobileNoExist(const QString &mobileNo);
    bool accountExist(const QString &accountNo);
    int  getUserid(const QString &username);

    // ── Account operations ─────────────────────────────────────────
    bool   createAccount(int userId, const QString &currency);
    double getBalance(int accountId);
    int    getAccountID(int userId);

    // ── Financial transactions ─────────────────────────────────────
    bool executeDeposit(int accountId, double amount, const QString &remarks);
    bool executeWithdraw(int accountId, double amount, const QString &remarks);
    bool transfer(int senderId, int receiverId, double amount, const QString &remarks);
    bool authTransaction(int userId, const QString &tpin);

    // ── Data retrieval (user) ─────────────────────────────────────
    QSqlQueryModel *getTransactionHistory(int accountId);
    double          getIncome(int accountId);
    double          getExpenses(int accountId);

    // ── Session factory ────────────────────────────────────────────
    UserSessionHandler *setUserInfo(int id, int accountID);

    // ── Admin: system-wide queries ─────────────────────────────────
    /** Returns a model of all registered users (user_id, name, username, email, mobile, created_at). */
    QSqlQueryModel *getAllUsers(const QString &filter = "");

    /** Returns a model of all accounts (account_id, user_name, balance, currency). */
    QSqlQueryModel *getAllAccounts();

    /** Total number of registered users. */
    int    getTotalUserCount();

    /** Sum of all account balances in the system. */
    double getSystemTotalBalance();

    /** Sum of all deposits ever made across all accounts. */
    double getSystemTotalDeposits();

    /** Sum of all withdrawals ever made across all accounts. */
    double getSystemTotalWithdrawals();

    // ── Admin: credential management ───────────────────────────────
    /**
     * Verifies the current admin password and, if correct, updates both
     * the stored admin username and password hash.
     *
     * The admin record is stored in the AdminCredentials table that is
     * created by initializeSchema().  The table starts with one row
     * (seeded on first run) whose defaults match ADMIN_DEFAULT_USERNAME /
     * ADMIN_DEFAULT_PASSWORD_HASH defined in database.cpp.
     *
     * @param currentPassword  plain-text password the admin typed as verification
     * @param newUsername      new username (pass empty string to keep current)
     * @param newPassword      new plain-text password (pass empty string to keep current)
     * @return true on success, false if currentPassword is wrong or DB error
     */
    bool changeAdminCredentials(const QString &currentPassword,
                                const QString &newUsername,
                                const QString &newPassword);

    /**
     * Authenticate an admin login attempt.
     * @return true if username + password match the stored admin credentials.
     */
    bool authenticateAdmin(const QString &username, const QString &password);

private:
    QSqlDatabase db;
    bool initializeSchema();
};

#endif // DATABASE_H
