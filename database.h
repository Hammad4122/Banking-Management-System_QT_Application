#ifndef DATABASE_H
#define DATABASE_H

#include "usersessionhandler.h"
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
    bool initializeSchema();

    // --- User & Authentication ---
    // Matches 'Users' table
    bool registerUser(const QString& firstName,const QString& lastName,const QString& userName,
                      const QString& email,const QString& password, QString& mobile,const QString &tpin);
    int loginUser(const QString userName,const QString password);
    bool userExist(const QString &userName);
    bool emailExist(const QString &email);
    bool mobileNoExist(const QString &mobileNo);
    bool accountExist(const QString &accountNo);

    // --- Account Operations ---
    // Matches 'Accounts' table
    bool createAccount(int userId,const QString& currency = "PKR");
    double getBalance(int accountId);
    int getUserid(const QString &username);

    // --- Financial Transactions ---
    // Matches 'Transactions' table
    bool executeDeposit(int accountId, double amount,const QString& remarks = "");
    bool executeWithdraw(int accountId, double amount,const QString& remarks = "");
    bool transfer(int senderAccountId, int receiverAccountId, double amount,const  QString& remarks = "");

    // --- Data Retrieval ---
    // To fetch the list of transactions for a user's statement
    void getTransactionHistory(int accountId);

    // --- User Information ---
    UserSessionHandler* setUserInfo(int id);

    // -- Auth Transaction --
    bool authTransaction(int id, const QString& tpin);
};

#endif // DATABASE_H
