#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QString>
#include <QVariant>
#include <QVector>

class BankDB {
private:
    QSqlDatabase db;

public:
    // --- Database Lifecycle ---
    bool connectDB();
    void disconnectDB();

    // --- User & Authentication ---
    // Matches 'Users' table
    bool registerUser(QString firstName, QString lastName, QString userName,
                      QString email, QString password, QString mobile);
    int loginUser(QString userName, QString password);

    // --- Account Operations ---
    // Matches 'Accounts' table
    bool createAccount(int userId, QString currency = "PKR");
    double getBalance(int accountId);

    // --- Financial Transactions ---
    // Matches 'Transactions' table
    bool deposit(int accountId, double amount, QString remarks = "");
    bool withdraw(int accountId, double amount, QString remarks = "");
    bool transfer(int senderAccountId, int receiverAccountId, double amount, QString remarks = "");

    // --- Data Retrieval ---
    // To fetch the list of transactions for a user's statement
    void getTransactionHistory(int accountId);
};

#endif // DATABASE_H
