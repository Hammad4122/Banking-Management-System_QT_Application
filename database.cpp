#include "database.h"
#include "usersessionhandler.h"
#include <QtSql/QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QCryptographicHash>

// --- Database Lifecycle ---

bool BankDB::connectDB() {
    // 1. Check if the default connection already exists and is open
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
        if (db.isOpen()) {
            return true; // Use the existing connection
        }
    }

    // 2. If not, set up the QODBC connection for SQL Server
    db = QSqlDatabase::addDatabase("QODBC");

    QString connStr;

    #ifdef Q_OS_WIN
        // Windows Configuration: Local instance using Windows Auth
        connStr = "Driver={SQL Server};"
                  "Server=Hammad\\SQLEXPRESS;"
                  "Database=BankDB;"
                  "Trusted_Connection=yes;";
    #else
        // Linux/Pop!_OS Configuration: Remote connection via IP using SQL Auth
        connStr = "Driver={ODBC Driver 18 for SQL Server};"
                  "Server=192.168.10.8,1433;"
                  "Database=BankDB;"
                  "UID=sa;"
                  "PWD=BMS@2026;" // Use the password you set in SSMS
                  "Encrypt=yes;"
                  "TrustServerCertificate=yes;";
    #endif

    db.setDatabaseName(connStr);

    // 3. Attempt to open
    if (db.open()) {
        QSqlQuery query;

        // 1. First, tell SQL Server to use the specific database
        if (!query.exec("USE BankDB;")) {
            qDebug() << "Database Error: Could not switch to BankDB." << query.lastError().text();
            return false;
        }

        // 2. Now that we are IN the BankDB, create the tables
        if (initializeSchema()) {
            qDebug() << "Successfully connected to SQL Server and verified schema.";
            return true;
        } else {
            qDebug() << "Failed to initialize database schema.";
            return false;
        }
    } else {
        qDebug() << "SQL Server Connection Error:" << db.lastError().text();
        return false;
    }
}

void BankDB::disconnectDB() {
    if (db.isOpen()) {
        db.close();
    }
}

// --- User & Authentication ---

bool BankDB::registerUser(const QString &firstName, const QString &lastName, const QString &userName,
                          const QString &email, const QString &password, QString &mobile, const QString &tpin) {
    // Convert plain text password to a SHA-256 Hash
    QByteArray passwordData = password.toUtf8();
    QString passHashedPath = QString(QCryptographicHash::hash(passwordData, QCryptographicHash::Sha256).toHex());

    // Convert plain tpin to a SHA-256
    QByteArray tpinData = tpin.toUtf8();
    QString tpinHashedPath = QString(QCryptographicHash::hash(tpinData,QCryptographicHash::Sha256).toHex());

    QSqlQuery query;
    query.prepare("INSERT INTO Users (first_name, last_name, user_name, email, password, mobile_no,tpin) "
                  "VALUES (?, ?, ?, ?, ?, ?,?)");
    query.addBindValue(firstName);
    query.addBindValue(lastName);
    query.addBindValue(userName);
    query.addBindValue(email);
    query.addBindValue(passHashedPath);
    query.addBindValue(mobile);
    query.addBindValue(tpinHashedPath);

    return query.exec();
}

int BankDB::loginUser(const QString userName, const QString password) {
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

bool BankDB::userExist(const QString& userName){
    QSqlQuery query;
    query.prepare("Select user_name FROM Users WHERE user_name = ?");
    query.addBindValue(userName);

    if (query.exec() && query.next()){
        return true;
    }

    return false;
}

bool BankDB::emailExist(const QString &email){
    QSqlQuery query;
    query.prepare("SELECT email FROM Users WHERE email = ?");
    query.addBindValue(email);

    if (query.exec() && query.next()){
        return true;
    }

    return false;
}

bool BankDB::mobileNoExist(const QString &mobileNo){
    QSqlQuery query;
    query.prepare("SELECT mobile_no FROM Users WHERE mobile_no = ?");
    query.addBindValue(mobileNo);

    if (query.exec() && query.next()){
        return true;
    }

    return false;
}

bool BankDB::accountExist(const QString &accountNo){
    QSqlQuery query;
    query.prepare("SELECT account_id FROM Accounts WHERE account_id = ?");
    query.addBindValue(accountNo);
    if (query.exec() && query.next()){
        return true;
    }
    else {
        return false;
    }
}

int BankDB::getUserid(const QString& username){
    QSqlQuery query;
    query.prepare("SELECT user_id FROM Users WHERE user_name = ?");
    query.addBindValue(username);

    if (query.exec() && query.next()){
        return query.value(0).toInt();
    }
    return -1;
}

// --- Account Operations ---

bool BankDB::createAccount(int userId, const QString &currency) {
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

bool BankDB::executeDeposit(int accountId, double amount, const QString& remarks) {
    // 1. Get the current balance BEFORE starting the transaction
    double currentBalance = getBalance(accountId);

    QSqlQuery query;
    double newBalance = currentBalance + amount;

    // 2. Update Balance
    query.prepare("UPDATE Accounts SET balance = ? WHERE account_id = ?");
    query.addBindValue(newBalance);
    query.addBindValue(accountId);

    query.exec();

    // 3. Log Transaction
    query.prepare("INSERT INTO Transactions (account_id, transaction_type, amount, balance_after, remarks) "
                  "VALUES (?, 'Deposit', ?, ?, ?)");
    query.addBindValue(accountId);
    query.addBindValue(amount);
    query.addBindValue(newBalance);
    query.addBindValue(remarks);

    return query.exec();
}

// This is a private helper that just does the SQL work
bool BankDB::executeWithdraw(int accountId, double amount, const QString& remarks) {
    QSqlQuery query;
    // 1. Check Balance
    if (getBalance(accountId) < amount) return false;

    // 2. Update Balance
    query.prepare("UPDATE Accounts SET balance = balance - ? WHERE account_id = ?");
    query.addBindValue(amount);
    query.addBindValue(accountId);

    query.exec();

    // 3. Log
    query.prepare("INSERT INTO Transactions (account_id, transaction_type, amount, balance_after, remarks) "
                  "VALUES (?, 'Withdrawal', ?, ?, ?)");
    query.addBindValue(accountId);
    query.addBindValue(amount);
    query.addBindValue(getBalance(accountId));
    query.addBindValue(remarks);

    return query.exec();
}

bool BankDB::transfer(int senderId, int receiverId, double amount, const QString &remarks) {

    // Use the logic-only helpers
    if (!executeWithdraw(senderId, amount, "Transfer to " + QString::number(receiverId))) {
        return false;
    }

    if (!executeDeposit(receiverId, amount, "Transfer from " + QString::number(senderId))) {
        return false;
    }

    return true;
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

bool BankDB::initializeSchema() {
    QSqlQuery query;

    // We use a list of queries to execute them one by one
    QStringList schemaQueries;

    // 1. Users Table
    schemaQueries << R"(
        IF NOT EXISTS (SELECT * FROM sys.tables WHERE name = 'Users')
        BEGIN
            CREATE TABLE Users (
                user_id INT PRIMARY KEY IDENTITY(1,1),
                first_name NVARCHAR(30) NOT NULL,
                last_name NVARCHAR(30) NOT NULL,
                user_name NVARCHAR(15) UNIQUE NOT NULL,
                email NVARCHAR(100) UNIQUE NOT NULL,
                password NVARCHAR(64) NOT NULL,
                mobile_no NVARCHAR(11) UNIQUE NOT NULL,
                created_at DATETIME DEFAULT GETDATE()
            );
        END
    )";

    // 2. Accounts Table
    schemaQueries << R"(
        IF NOT EXISTS (SELECT * FROM sys.tables WHERE name = 'Accounts')
        BEGIN
            CREATE TABLE Accounts (
                account_id INT PRIMARY KEY IDENTITY(1000,1),
                user_id INT NOT NULL,
                balance DECIMAL(18, 2) DEFAULT 0.00,
                currency NVARCHAR(10) DEFAULT 'PKR',
                CONSTRAINT FK_UserAccount FOREIGN KEY (user_id) REFERENCES Users(user_id) ON DELETE CASCADE
            );
        END
    )";

    // 3. Transactions Table
    schemaQueries << R"(
        IF NOT EXISTS (SELECT * FROM sys.tables WHERE name = 'Transactions')
        BEGIN
            CREATE TABLE Transactions (
                transaction_id INT PRIMARY KEY IDENTITY(1,1),
                account_id INT NOT NULL,
                transaction_type NVARCHAR(20) NOT NULL,
                amount DECIMAL(18, 2) NOT NULL,
                balance_after DECIMAL(18, 2) NOT NULL,
                remarks NVARCHAR(255),
                transaction_date DATETIME DEFAULT GETDATE(),
                CONSTRAINT FK_AccountTransaction FOREIGN KEY (account_id) REFERENCES Accounts(account_id) ON DELETE CASCADE
            );
        END
    )";

    // Execute each block
    for (const QString &queryString : std::as_const(schemaQueries)) {
        if (!query.exec(queryString)) {
            qDebug() << "Database Schema Error:" << query.lastError().text();
            qDebug() << "Query Context:" << queryString.left(50) << "...";
            return false;
        }
    }

    qDebug() << "Database tables validated/created successfully.";
    return true;
}

UserSessionHandler* BankDB::setUserInfo(int id){
    QSqlQuery query;

    QString sql = "SELECT "
                  "u.user_id, u.first_name, u.last_name, u.user_name, u.email, u.mobile_no, "
                  "a.account_id, a.balance "
                  "FROM Users u "
                  "JOIN Accounts a ON u.user_id = a.user_id "
                  "WHERE u.user_id = ?";

    query.prepare(sql);
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        UserSessionHandler* userSession = new UserSessionHandler(
            query.value("user_id").toInt(),
            query.value("first_name").toString(),
            query.value("last_name").toString(),
            query.value("user_name").toString(),
            query.value("email").toString(),
            query.value("mobile_no").toString(),
            query.value("account_id").toInt(),
            query.value("balance").toDouble()
            );
        return userSession;
    } else {
        qDebug() << "Error: User or Account details not found for ID:" << id;
    }
    return nullptr;
}

bool BankDB::authTransaction(int id, const QString &tpin) {
    QSqlQuery query;
    // Fix: Removed duplicate "FROM Users" and fixed syntax
    query.prepare("SELECT tpin FROM Users WHERE user_id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return false;
    }

    if (query.next()) { // You MUST call next() to move to the first result
        QByteArray tpinData = tpin.toUtf8();
        QString tpinHashedInput = QString(QCryptographicHash::hash(tpinData, QCryptographicHash::Sha256).toHex());

        QString storedHash = query.value(0).toString();

        return (tpinHashedInput == storedHash);
    }

    return false; // wrong tpin (not matched)
}
