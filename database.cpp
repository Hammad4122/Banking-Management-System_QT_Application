#include "database.h"
#include <QtSql/QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QCryptographicHash>

// --- Database Lifecycle ---

bool BankDB::connectDB() {
    // Add the QODBC driver for SQL Server
    db = QSqlDatabase::addDatabase("QODBC");

    QString connStr = "Driver={ODBC Driver 17 for SQL Server};"
                      "Server=HAMMAD\\SQLEXPRESS;"
                      "Database=BankDB;"
                      "Trusted_Connection=yes;"
                      "Encrypt=yes;"
                      "TrustServerCertificate=yes;";

    db.setDatabaseName(connStr);

    if (db.open()) {
        QSqlQuery query;
        query.exec("USE BankDB;"); // Force the connection to use your specific database
        qDebug() << "Connected and switched to BankDB!";
    }

    if (!db.open()) {
        qDebug() << "Connection Error:" << db.lastError().text();
        return false;
    }
    qDebug() << "Connection Successfull";
    return true;
}

void BankDB::disconnectDB() {
    if (db.isOpen()) {
        db.close();
    }
}

// --- User & Authentication ---

bool BankDB::registerUser(QString firstName, QString lastName, QString userName,
                          QString email, QString password, QString mobile) {
    // Convert plain text password to a SHA-256 Hash
    QByteArray passwordData = password.toUtf8();
    QString hashedPath = QString(QCryptographicHash::hash(passwordData, QCryptographicHash::Sha256).toHex());

    QSqlQuery query;
    query.prepare("INSERT INTO Users (first_name, last_name, user_name, email, password, mobile_no) "
                  "VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(firstName);
    query.addBindValue(lastName);
    query.addBindValue(userName);
    query.addBindValue(email);
    query.addBindValue(hashedPath);
    query.addBindValue(mobile);

    return query.exec();
}

int BankDB::loginUser(QString userName, QString password) {
    // 1. Hash the password (exactly like you had it)
    QByteArray passwordData = password.toUtf8();
    QString hashedPath = QString(QCryptographicHash::hash(passwordData, QCryptographicHash::Sha256).toHex());

    QSqlQuery query;
    query.prepare("SELECT user_id FROM Users WHERE user_name = ? AND password = ?");
    query.addBindValue(userName);
    query.addBindValue(hashedPath);

    // 2. Execute and check results
    if (query.exec() && query.next()) {
        // Return the actual ID from the first column (index 0)
        return query.value(0).toInt();
    }

    // 3. Return -1 if login fails (standard C++ "error" indicator)
    return -1;
}

// --- Account Operations ---

bool BankDB::createAccount(int userId, QString currency) {
    QSqlQuery query;
    query.prepare("INSERT INTO Accounts (user_id, balance, currency) VALUES (?, 0, ?)");
    query.addBindValue(userId);
    query.addBindValue(currency);

    return query.exec();
}

double BankDB::getBalance(int accountId) {
    QSqlQuery query;
    query.prepare("SELECT balance FROM Accounts WHERE account_id = ?");
    query.addBindValue(accountId);

    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return -1.0; // Return -1 if account doesn't exist
}

// --- Financial Transactions ---

bool BankDB::deposit(int accountId, double amount, QString remarks) {
    db.transaction();
    QSqlQuery query;

    // 1. Update Balance
    query.prepare("UPDATE Accounts SET balance = balance + ? WHERE account_id = ?");
    query.addBindValue(amount);
    query.addBindValue(accountId);
    if (!query.exec()) { db.rollback(); return false; }

    // 2. Log Transaction
    double newBalance = getBalance(accountId);
    query.prepare("INSERT INTO Transactions (account_id, transaction_type, amount, balance_after, remarks) "
                  "VALUES (?, 'Deposit', ?, ?, ?)");
    query.addBindValue(accountId);
    query.addBindValue(amount);
    query.addBindValue(newBalance);
    query.addBindValue(remarks);

    if (!query.exec()) { db.rollback(); return false; }
    return db.commit();
}

bool BankDB::withdraw(int accountId, double amount, QString remarks) {
    double currentBalance = getBalance(accountId);
    if (currentBalance < amount) return false; // Insufficient funds

    db.transaction();
    QSqlQuery query;

    // 1. Update Balance
    query.prepare("UPDATE Accounts SET balance = balance - ? WHERE account_id = ?");
    query.addBindValue(amount);
    query.addBindValue(accountId);
    if (!query.exec()) { db.rollback(); return false; }

    // 2. Log Transaction
    double newBalance = currentBalance - amount;
    query.prepare("INSERT INTO Transactions (account_id, transaction_type, amount, balance_after, remarks) "
                  "VALUES (?, 'Withdrawal', ?, ?, ?)");
    query.addBindValue(accountId);
    query.addBindValue(amount);
    query.addBindValue(newBalance);
    query.addBindValue(remarks);

    if (!query.exec()) { db.rollback(); return false; }
    return db.commit();
}

bool BankDB::transfer(int senderId, int receiverId, double amount, QString remarks) {
    double senderBalance = getBalance(senderId);
    if (senderBalance < amount) return false;

    db.transaction();

    // Step 1: Withdraw from Sender
    if (!withdraw(senderId, amount, "Transfer to " + QString::number(receiverId) + ": " + remarks)) {
        db.rollback();
        return false;
    }

    // Step 2: Deposit to Receiver
    if (!deposit(receiverId, amount, "Transfer from " + QString::number(senderId) + ": " + remarks)) {
        db.rollback();
        return false;
    }

    return db.commit();
}

// --- Data Retrieval ---

void BankDB::getTransactionHistory(int accountId) {
    QSqlQuery query;
    query.prepare("SELECT transaction_type, amount, balance_after, transaction_date, remarks "
                  "FROM Transactions WHERE account_id = ? ORDER BY transaction_date DESC");
    query.addBindValue(accountId);

    if (query.exec()) {
        while (query.next()) {
            QString type = query.value(0).toString();
            double amt = query.value(1).toDouble();
            double bal = query.value(2).toDouble();
            QString date = query.value(3).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
            QString rem = query.value(4).toString();

            qDebug() << date << "|" << type << "| Amount:" << amt << "| Balance:" << bal << "| Note:" << rem;
        }
    }
}
