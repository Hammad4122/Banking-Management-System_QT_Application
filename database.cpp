#include "database.h"
#include "usersessionhandler.h"
#include <QtSql/QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QCryptographicHash>
#include <QSqlQueryModel>

// ─── Admin defaults ─────────────────────────────────────────────────────────
// These are the seed values written into AdminCredentials on first run.
// The password hash below is SHA-256("admin123").
static const QString ADMIN_DEFAULT_USERNAME     = "admin";
static const QString ADMIN_DEFAULT_PASSWORD_HASH =
    "240be518fabd2724ddb6f04eeb1da5967448d7e831c08c8fa822809f74c720a9"; // SHA-256 of "admin123"

// ─── Lifecycle ───────────────────────────────────────────────────────────────

bool BankDB::connectDB() {
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
        if (db.isOpen()) return true;
    }

    db = QSqlDatabase::addDatabase("QODBC");

    QString connStr;
#ifdef Q_OS_WIN
    connStr = "Driver={SQL Server};"
              "Server=Hammad\\SQLEXPRESS;"
              "Database=BankDB;"
              "Trusted_Connection=yes;";
#else
    connStr = "Driver={ODBC Driver 18 for SQL Server};"
              "Server=;"
              "Database=BankDB;"
              "UID=;"
              "PWD=;"
              "Encrypt=yes;"
              "TrustServerCertificate=yes;";
#endif

    db.setDatabaseName(connStr);

    if (db.open()) {
        QSqlQuery query;
        if (!query.exec("USE BankDB;")) {
            qDebug() << "Database Error: Could not switch to BankDB." << query.lastError().text();
            return false;
        }
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
        qDebug() << "Database Disconnected";
    }
}

// ─── Schema ──────────────────────────────────────────────────────────────────

bool BankDB::initializeSchema() {
    QSqlQuery query;
    QStringList schemaQueries;

    // 1. Users
    schemaQueries << R"(
        IF NOT EXISTS (SELECT * FROM sys.tables WHERE name = 'Users')
        BEGIN
            CREATE TABLE Users (
                user_id    INT PRIMARY KEY IDENTITY(1,1),
                first_name NVARCHAR(30)  NOT NULL,
                last_name  NVARCHAR(30)  NOT NULL,
                user_name  NVARCHAR(15)  UNIQUE NOT NULL,
                email      NVARCHAR(100) UNIQUE NOT NULL,
                cnic       NVARCHAR(15)  UNIQUE NOT NULL,
                password   NVARCHAR(64)  NOT NULL,
                mobile_no  NVARCHAR(11)  UNIQUE NOT NULL,
                tpin       NVARCHAR(64)  NOT NULL,
                created_at DATETIME DEFAULT GETDATE()
            );
        END
    )";

    // 2. Accounts
    schemaQueries << R"(
        IF NOT EXISTS (SELECT * FROM sys.tables WHERE name = 'Accounts')
        BEGIN
            CREATE TABLE Accounts (
                account_id INT PRIMARY KEY IDENTITY(1000,1),
                user_id    INT NOT NULL,
                balance    DECIMAL(18, 2) DEFAULT 0.00,
                currency   NVARCHAR(10) DEFAULT 'PKR',
                CONSTRAINT FK_UserAccount FOREIGN KEY (user_id)
                    REFERENCES Users(user_id) ON DELETE CASCADE
            );
        END
    )";

    // 3. Transactions
    schemaQueries << R"(
        IF NOT EXISTS (SELECT * FROM sys.tables WHERE name = 'Transactions')
        BEGIN
            CREATE TABLE Transactions (
                transaction_id   INT PRIMARY KEY IDENTITY(1,1),
                account_id       INT NOT NULL,
                transaction_type NVARCHAR(20) NOT NULL,
                amount           DECIMAL(18, 2) NOT NULL,
                balance_after    DECIMAL(18, 2) NOT NULL,
                remarks          NVARCHAR(255),
                transaction_date DATETIME DEFAULT GETDATE(),
                CONSTRAINT FK_AccountTransaction FOREIGN KEY (account_id)
                    REFERENCES Accounts(account_id) ON DELETE CASCADE
            );
        END
    )";

    // 4. AdminCredentials – single-row table; seeded on first run
    schemaQueries << R"(
        IF NOT EXISTS (SELECT * FROM sys.tables WHERE name = 'AdminCredentials')
        BEGIN
            CREATE TABLE AdminCredentials (
                id            INT PRIMARY KEY DEFAULT 1,
                admin_username NVARCHAR(50) NOT NULL,
                password_hash  NVARCHAR(64) NOT NULL
            );
        END
    )";

    // Execute schema
    for (const QString &q : std::as_const(schemaQueries)) {
        if (!query.exec(q)) {
            qDebug() << "Schema Error:" << query.lastError().text();
            return false;
        }
    }

    // Seed admin credentials if the row doesn't exist yet
    query.prepare("IF NOT EXISTS (SELECT 1 FROM AdminCredentials WHERE id = 1) "
                  "INSERT INTO AdminCredentials (id, admin_username, password_hash) "
                  "VALUES (1, ?, ?)");
    query.addBindValue(ADMIN_DEFAULT_USERNAME);
    query.addBindValue(ADMIN_DEFAULT_PASSWORD_HASH);
    if (!query.exec()) {
        qDebug() << "Admin seed error:" << query.lastError().text();
        return false;
    }

    qDebug() << "Database tables validated/created successfully.";
    return true;
}

// ─── User auth & registration ────────────────────────────────────────────────

bool BankDB::registerUser(const QString &firstName, const QString &lastName,
                          const QString &userName, const QString &email,
                          const QString &cnic, const QString &password,
                          QString &mobile, const QString &tpin)
{
    auto sha256 = [](const QString &plain) {
        return QString(QCryptographicHash::hash(plain.toUtf8(),
                                                QCryptographicHash::Sha256).toHex());
    };

    QSqlQuery query;
    query.prepare("INSERT INTO Users "
                  "(first_name, last_name, user_name, email, cnic, password, mobile_no, tpin) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(firstName);
    query.addBindValue(lastName);
    query.addBindValue(userName);
    query.addBindValue(email);
    query.addBindValue(cnic);
    query.addBindValue(sha256(password));
    query.addBindValue(mobile);
    query.addBindValue(sha256(tpin));

    return query.exec();
}

int BankDB::loginUser(const QString userName, const QString password) {
    QString hash = QString(QCryptographicHash::hash(
                               password.toUtf8(), QCryptographicHash::Sha256).toHex());
    QSqlQuery query;
    query.prepare("SELECT user_id FROM Users WHERE user_name = ? AND password = ?");
    query.addBindValue(userName);
    query.addBindValue(hash);

    if (query.exec() && query.next()) return query.value(0).toInt();
    return -1;
}

bool BankDB::userExist(const QString &userName) {
    QSqlQuery query;
    query.prepare("SELECT user_name FROM Users WHERE user_name = ?");
    query.addBindValue(userName);
    return query.exec() && query.next();
}

bool BankDB::emailExist(const QString &email) {
    QSqlQuery query;
    query.prepare("SELECT email FROM Users WHERE email = ?");
    query.addBindValue(email);
    return query.exec() && query.next();
}

bool BankDB::cnicExist(const QString &cnic) {
    QSqlQuery query;
    query.prepare("SELECT cnic FROM Users WHERE cnic = ?");
    query.addBindValue(cnic);
    return query.exec() && query.next();
}

bool BankDB::mobileNoExist(const QString &mobileNo) {
    QSqlQuery query;
    query.prepare("SELECT mobile_no FROM Users WHERE mobile_no = ?");
    query.addBindValue(mobileNo);
    return query.exec() && query.next();
}

bool BankDB::accountExist(const QString &accountNo) {
    QSqlQuery query;
    query.prepare("SELECT account_id FROM Accounts WHERE account_id = ?");
    query.addBindValue(accountNo);
    return query.exec() && query.next();
}

int BankDB::getUserid(const QString &username) {
    QSqlQuery query;
    query.prepare("SELECT user_id FROM Users WHERE user_name = ?");
    query.addBindValue(username);
    if (query.exec() && query.next()) return query.value(0).toInt();
    return -1;
}

// ─── Account operations ───────────────────────────────────────────────────────

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
    if (query.exec() && query.next()) return query.value(0).toDouble();
    return -1.0;
}

int BankDB::getAccountID(int userId) {
    QSqlQuery query;
    query.prepare("SELECT account_id FROM Accounts WHERE user_id = ?");
    query.addBindValue(userId);
    if (query.exec() && query.next()) return query.value(0).toInt();
    return -1;
}

// ─── Financial transactions ───────────────────────────────────────────────────

bool BankDB::executeDeposit(int accountId, double amount, const QString &remarks) {
    double newBalance = getBalance(accountId) + amount;

    QSqlQuery query;
    query.prepare("UPDATE Accounts SET balance = ? WHERE account_id = ?");
    query.addBindValue(newBalance);
    query.addBindValue(accountId);
    query.exec();

    query.prepare("INSERT INTO Transactions "
                  "(account_id, transaction_type, amount, balance_after, remarks) "
                  "VALUES (?, 'Deposit', ?, ?, ?)");
    query.addBindValue(accountId);
    query.addBindValue(amount);
    query.addBindValue(newBalance);
    query.addBindValue(remarks);
    return query.exec();
}

bool BankDB::executeWithdraw(int accountId, double amount, const QString &remarks) {
    double newBalance = getBalance(accountId) - amount;

    QSqlQuery query;
    query.prepare("UPDATE Accounts SET balance = ? WHERE account_id = ?");
    query.addBindValue(newBalance);
    query.addBindValue(accountId);
    query.exec();

    query.prepare("INSERT INTO Transactions "
                  "(account_id, transaction_type, amount, balance_after, remarks) "
                  "VALUES (?, 'Withdrawal', ?, ?, ?)");
    query.addBindValue(accountId);
    query.addBindValue(amount);
    query.addBindValue(getBalance(accountId));
    query.addBindValue(remarks);
    return query.exec();
}

bool BankDB::transfer(int senderId, int receiverId, double amount, const QString &remarks) {
    if (!executeWithdraw(senderId, amount,
                         "Transfer to " + QString::number(receiverId)))
        return false;
    return executeDeposit(receiverId, amount,
                          "Transfer from " + QString::number(senderId));
}

bool BankDB::authTransaction(int userId, const QString &tpin) {
    QSqlQuery query;
    query.prepare("SELECT tpin FROM Users WHERE user_id = ?");
    query.addBindValue(userId);
    if (!query.exec()) {
        qDebug() << "authTransaction query failed:" << query.lastError().text();
        return false;
    }
    if (query.next()) {
        QString hash = QString(QCryptographicHash::hash(
                                   tpin.toUtf8(), QCryptographicHash::Sha256).toHex());
        return hash == query.value(0).toString();
    }
    return false;
}

// ─── Data retrieval (user) ────────────────────────────────────────────────────

QSqlQueryModel *BankDB::getTransactionHistory(int accountId) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT transaction_date AS \"Date\", "
                  "       transaction_type AS \"Type\", "
                  "       '$' + CAST(amount AS VARCHAR(20)) AS \"Amount\", "
                  "       remarks AS \"Remarks\" "
                  "FROM Transactions "
                  "WHERE account_id = ? "
                  "ORDER BY transaction_date DESC");
    query.addBindValue(accountId);
    query.exec();
    model->setQuery(std::move(query));
    return model;
}

double BankDB::getIncome(int accountId) {
    QSqlQuery query;
    query.prepare("SELECT SUM(amount) FROM Transactions "
                  "WHERE account_id = ? AND transaction_type = ?");
    query.addBindValue(accountId);
    query.addBindValue("Deposit");
    if (query.exec() && query.next()) return query.value(0).toDouble();
    return 0.0;
}

double BankDB::getExpenses(int accountId) {
    QSqlQuery query;
    query.prepare("SELECT SUM(amount) FROM Transactions "
                  "WHERE account_id = ? AND transaction_type = ?");
    query.addBindValue(accountId);
    query.addBindValue("Withdrawal");
    if (query.exec() && query.next()) return query.value(0).toDouble();
    return 0.0;
}

// ─── Session factory ──────────────────────────────────────────────────────────

UserSessionHandler *BankDB::setUserInfo(int id, int accountID) {
    QSqlQuery query, incomeQuery, expenseQuery;

    query.prepare("SELECT u.user_id, u.first_name, u.last_name, u.user_name, "
                  "       u.email, u.mobile_no, a.account_id, a.balance "
                  "FROM Users u JOIN Accounts a ON u.user_id = a.user_id "
                  "WHERE u.user_id = ?");
    query.addBindValue(id);

    incomeQuery.prepare("SELECT SUM(amount) FROM Transactions "
                        "WHERE account_id = ? AND transaction_type = ?");
    incomeQuery.addBindValue(accountID);
    incomeQuery.addBindValue("Deposit");

    expenseQuery.prepare("SELECT SUM(amount) FROM Transactions "
                         "WHERE account_id = ? AND transaction_type = ?");
    expenseQuery.addBindValue(accountID);
    expenseQuery.addBindValue("Withdrawal");

    bool ok1 = query.exec()       && query.next();
    bool ok2 = incomeQuery.exec() && incomeQuery.next();
    bool ok3 = expenseQuery.exec() && expenseQuery.next();

    if (ok1 && ok2 && ok3) {
        return new UserSessionHandler(
            query.value("user_id").toInt(),
            query.value("first_name").toString(),
            query.value("last_name").toString(),
            query.value("user_name").toString(),
            query.value("email").toString(),
            query.value("mobile_no").toString(),
            query.value("account_id").toInt(),
            query.value("balance").toDouble(),
            incomeQuery.value(0).toDouble(),
            expenseQuery.value(0).toDouble()
            );
    }

    qDebug() << "setUserInfo failed for id:" << id;
    return nullptr;
}

// ─── Admin: system-wide queries ───────────────────────────────────────────────

QSqlQueryModel *BankDB::getAllUsers(const QString &filter) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    if (filter.isEmpty()) {
        query.prepare("SELECT u.user_id    AS \"ID\", "
                      "       u.first_name + ' ' + u.last_name AS \"Full Name\", "
                      "       u.user_name  AS \"Username\", "
                      "       u.email      AS \"Email\", "
                      "       u.mobile_no  AS \"Mobile\", "
                      "       CONVERT(NVARCHAR, u.created_at, 103) AS \"Joined\" "
                      "FROM Users u "
                      "ORDER BY u.user_id DESC");
        query.exec();
    } else {
        QString like = "%" + filter + "%";
        query.prepare("SELECT u.user_id    AS \"ID\", "
                      "       u.first_name + ' ' + u.last_name AS \"Full Name\", "
                      "       u.user_name  AS \"Username\", "
                      "       u.email      AS \"Email\", "
                      "       u.mobile_no  AS \"Mobile\", "
                      "       CONVERT(NVARCHAR, u.created_at, 103) AS \"Joined\" "
                      "FROM Users u "
                      "WHERE u.user_name LIKE ? OR u.email LIKE ? "
                      "   OR u.first_name LIKE ? OR u.last_name LIKE ? "
                      "ORDER BY u.user_id DESC");
        query.addBindValue(like);
        query.addBindValue(like);
        query.addBindValue(like);
        query.addBindValue(like);
        query.exec();
    }

    model->setQuery(std::move(query));
    return model;
}

QSqlQueryModel *BankDB::getAllAccounts() {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT a.account_id  AS \"Account No\", "
                  "       u.first_name + ' ' + u.last_name AS \"Owner\", "
                  "       u.user_name   AS \"Username\", "
                  "       a.currency    AS \"Currency\", "
                  "       '$' + CAST(CAST(a.balance AS DECIMAL(18,2)) AS NVARCHAR) AS \"Balance\" "
                  "FROM Accounts a "
                  "JOIN Users u ON a.user_id = u.user_id "
                  "ORDER BY a.account_id DESC");
    query.exec();
    model->setQuery(std::move(query));
    return model;
}

int BankDB::getTotalUserCount() {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Users");
    if (query.exec() && query.next()) return query.value(0).toInt();
    return 0;
}

double BankDB::getSystemTotalBalance() {
    QSqlQuery query;
    query.prepare("SELECT ISNULL(SUM(balance), 0) FROM Accounts");
    if (query.exec() && query.next()) return query.value(0).toDouble();
    return 0.0;
}

double BankDB::getSystemTotalDeposits() {
    QSqlQuery query;
    query.prepare("SELECT ISNULL(SUM(amount), 0) FROM Transactions "
                  "WHERE transaction_type = 'Deposit'");
    if (query.exec() && query.next()) return query.value(0).toDouble();
    return 0.0;
}

double BankDB::getSystemTotalWithdrawals() {
    QSqlQuery query;
    query.prepare("SELECT ISNULL(SUM(amount), 0) FROM Transactions "
                  "WHERE transaction_type = 'Withdrawal'");
    if (query.exec() && query.next()) return query.value(0).toDouble();
    return 0.0;
}

// ─── Admin: credential management ────────────────────────────────────────────

bool BankDB::authenticateAdmin(const QString &username, const QString &password) {
    QString hash = QString(QCryptographicHash::hash(
                               password.toUtf8(), QCryptographicHash::Sha256).toHex());
    QSqlQuery query;
    query.prepare("SELECT 1 FROM AdminCredentials "
                  "WHERE admin_username = ? AND password_hash = ?");
    query.addBindValue(username);
    query.addBindValue(hash);
    return query.exec() && query.next();
}

bool BankDB::changeAdminCredentials(const QString &currentPassword,
                                    const QString &newUsername,
                                    const QString &newPassword)
{
    // 1. Fetch current stored hash to verify currentPassword
    QSqlQuery fetchQuery;
    fetchQuery.prepare("SELECT admin_username, password_hash FROM AdminCredentials WHERE id = 1");
    if (!fetchQuery.exec() || !fetchQuery.next()) {
        qDebug() << "changeAdminCredentials: fetch failed" << fetchQuery.lastError().text();
        return false;
    }
    QString storedUsername = fetchQuery.value("admin_username").toString();
    QString storedHash     = fetchQuery.value("password_hash").toString();

    // 2. Verify current password
    QString currentHash = QString(QCryptographicHash::hash(
                                      currentPassword.toUtf8(),
                                      QCryptographicHash::Sha256).toHex());
    if (currentHash != storedHash) {
        qDebug() << "changeAdminCredentials: wrong current password";
        return false;
    }

    // 3. Resolve new values (keep old if empty)
    QString finalUsername = newUsername.trimmed().isEmpty() ? storedUsername
                                                            : newUsername.trimmed();
    QString finalHash     = newPassword.trimmed().isEmpty() ? storedHash
                                                        : QString(QCryptographicHash::hash(
                                                                      newPassword.toUtf8(),
                                                                      QCryptographicHash::Sha256).toHex());

    // 4. Update
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE AdminCredentials "
                        "SET admin_username = ?, password_hash = ? "
                        "WHERE id = 1");
    updateQuery.addBindValue(finalUsername);
    updateQuery.addBindValue(finalHash);

    if (!updateQuery.exec()) {
        qDebug() << "changeAdminCredentials: update failed" << updateQuery.lastError().text();
        return false;
    }

    qDebug() << "Admin credentials updated successfully.";
    return true;
}
