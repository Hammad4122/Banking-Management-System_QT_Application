#include "admindashboardwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QLocale>
#include <QDebug>
#include <QFrame>
#include <QMessageBox>

// ─── Helper: styled stat card ─────────────────────────────────────────────────
static QWidget *makeStatCard(const QString &title, QLabel *&valueLabel,
                             const QString &accentColor)
{
    QWidget *card = new QWidget();
    card->setObjectName("adminStatCard");
    card->setMinimumSize(240, 110);
    card->setStyleSheet(
        "QWidget#adminStatCard {"
        "    background: white;"
        "    border-radius: 16px;"
        "    border-left: 5px solid " + accentColor + ";"
                        "}");

    QVBoxLayout *l = new QVBoxLayout(card);
    l->setContentsMargins(18, 14, 18, 14);

    QLabel *titleLbl = new QLabel(title);
    titleLbl->setStyleSheet(
        "color:#718096; font-weight:600; font-size:13px; border:none;");

    valueLabel = new QLabel("—");
    valueLabel->setStyleSheet(
        "color:#1A202C; font-size:26px; font-weight:bold; border:none;");

    l->addWidget(titleLbl);
    l->addWidget(valueLabel);
    return card;
}

// ─── Constructor ──────────────────────────────────────────────────────────────

AdminDashboardWindow::AdminDashboardWindow(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("adminDashContent");

    QVBoxLayout *root = new QVBoxLayout(this);
    root->setContentsMargins(0, 0, 0, 0);

    // ── Tab Widget ─────────────────────────────────────────────────
    tabWidget = new QTabWidget(this);
    tabWidget->setObjectName("adminTabWidget");
    tabWidget->setStyleSheet(
        "QTabWidget::pane {"
        "    border: none;"
        "    background: #F5F7FA;"
        "}"
        "QTabBar::tab {"
        "    background: #E8ECF4;"
        "    color: #4A5568;"
        "    padding: 10px 22px;"
        "    font-weight: bold;"
        "    font-size: 13px;"
        "    border-top-left-radius: 8px;"
        "    border-top-right-radius: 8px;"
        "    margin-right: 4px;"
        "}"
        "QTabBar::tab:selected {"
        "    background: #2D60FF;"
        "    color: white;"
        "}"
        "QTabBar::tab:hover:!selected {"
        "    background: #D0D8F0;"
        "}"
        );

    tabWidget->addTab(buildOverviewTab(),    "📊  Overview");
    tabWidget->addTab(buildUsersTab(),       "👥  Users");
    tabWidget->addTab(buildAccountsTab(),    "🏦  Accounts");
    tabWidget->addTab(buildCredentialsTab(), "🔐  Credentials");

    // Refresh tables when switching to Users / Accounts tabs
    connect(tabWidget, &QTabWidget::currentChanged, [this](int idx) {
        if (idx == 1) refreshUsersTable();
        if (idx == 2) refreshAccountsTable();
    });

    root->addWidget(tabWidget);
}

// ─── Tab builders ─────────────────────────────────────────────────────────────

QWidget *AdminDashboardWindow::buildOverviewTab()
{
    QWidget *tab = new QWidget();
    tab->setStyleSheet("background: #F5F7FA;");

    QVBoxLayout *vl = new QVBoxLayout(tab);
    vl->setContentsMargins(25, 25, 25, 10);
    vl->setSpacing(20);

    QLabel *heading = new QLabel("System Overview");
    heading->setStyleSheet(
        "font-size:22px; font-weight:bold; color:#273671;");

    // 2x2 grid of stat cards
    QGridLayout *grid = new QGridLayout();
    grid->setSpacing(16);

    QWidget *usersCard    = makeStatCard("Total Users",          totalUsersLabel,     "#2D60FF");
    QWidget *balanceCard  = makeStatCard("Total System Balance", totalBalanceLabel,   "#50C878");
    QWidget *depositCard  = makeStatCard("Total Deposits (All)", totalDepositsLabel,  "#F6AD55");
    QWidget *withdrawCard = makeStatCard("Total Withdrawals",    totalWithdrawalsLabel,"#FC8181");

    grid->addWidget(usersCard,    0, 0);
    grid->addWidget(balanceCard,  0, 1);
    grid->addWidget(depositCard,  1, 0);
    grid->addWidget(withdrawCard, 1, 1);

    QPushButton *refreshBtn = new QPushButton("⟳  Refresh Stats");
    refreshBtn->setFixedWidth(160);
    refreshBtn->setCursor(Qt::PointingHandCursor);
    refreshBtn->setStyleSheet(
        "QPushButton { background:#2D60FF; color:white; border-radius:8px;"
        "              font-weight:bold; font-size:13px; padding:8px; }"
        "QPushButton:hover { background:#1A4DDF; }");

    connect(refreshBtn, &QPushButton::clicked, this, &AdminDashboardWindow::refreshOverview);

    vl->addWidget(heading);
    vl->addLayout(grid);
    vl->addWidget(refreshBtn, 0, Qt::AlignLeft);
    vl->addStretch();

    return tab;
}

QWidget *AdminDashboardWindow::buildUsersTab()
{
    QWidget *tab = new QWidget();
    tab->setStyleSheet("background:#F5F7FA;");

    QVBoxLayout *vl = new QVBoxLayout(tab);
    vl->setContentsMargins(20, 15, 20, 10);
    vl->setSpacing(12);

    QLabel *heading = new QLabel("Registered Users");
    heading->setStyleSheet(
        "font-size:20px; font-weight:bold; color:#273671;");

    // Search bar
    QHBoxLayout *searchRow = new QHBoxLayout();
    searchRow->setSpacing(10);

    searchField = new QLineEdit();
    searchField->setPlaceholderText("Search by name, username or email…");
    searchField->setFixedHeight(38);
    searchField->setStyleSheet(
        "QLineEdit { border:1px solid #E6E9F4; border-radius:8px;"
        "            padding-left:10px; background:white; color:#1A202C; }"
        "QLineEdit:focus { border:1.5px solid #2D60FF; }");

    QPushButton *clearBtn = new QPushButton("✕  Clear");
    clearBtn->setFixedSize(80, 38);
    clearBtn->setCursor(Qt::PointingHandCursor);
    clearBtn->setStyleSheet(
        "QPushButton { background:#E8ECF4; color:#4A5568; border-radius:8px;"
        "              font-weight:bold; font-size:12px; }"
        "QPushButton:hover { background:#D0D8F0; }");

    searchRow->addWidget(searchField, 1);
    searchRow->addWidget(clearBtn);

    // Users table
    usersTable = new QTableView();
    usersTable->setObjectName("transactionTable");
    usersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    usersTable->setSelectionMode(QAbstractItemView::SingleSelection);
    usersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    usersTable->setShowGrid(false);
    usersTable->setAlternatingRowColors(true);
    usersTable->setFocusPolicy(Qt::NoFocus);
    usersTable->verticalHeader()->setVisible(false);
    usersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    vl->addWidget(heading);
    vl->addLayout(searchRow);
    vl->addWidget(usersTable, 1);

    // Connections
    connect(searchField, &QLineEdit::textChanged,
            this,        &AdminDashboardWindow::onSearchUsers);
    connect(clearBtn,    &QPushButton::clicked, [this]() {
        searchField->clear();
        refreshUsersTable();
    });

    return tab;
}

QWidget *AdminDashboardWindow::buildAccountsTab()
{
    QWidget *tab = new QWidget();
    tab->setStyleSheet("background:#F5F7FA;");

    QVBoxLayout *vl = new QVBoxLayout(tab);
    vl->setContentsMargins(20, 15, 20, 10);
    vl->setSpacing(12);

    QLabel *heading = new QLabel("All Accounts");
    heading->setStyleSheet(
        "font-size:20px; font-weight:bold; color:#273671;");

    QPushButton *refreshBtn = new QPushButton("⟳  Refresh");
    refreshBtn->setFixedWidth(120);
    refreshBtn->setCursor(Qt::PointingHandCursor);
    refreshBtn->setStyleSheet(
        "QPushButton { background:#2D60FF; color:white; border-radius:8px;"
        "              font-weight:bold; font-size:13px; padding:6px; }"
        "QPushButton:hover { background:#1A4DDF; }");
    connect(refreshBtn, &QPushButton::clicked,
            this, &AdminDashboardWindow::refreshAccountsTable);

    QHBoxLayout *headerRow = new QHBoxLayout();
    headerRow->addWidget(heading);
    headerRow->addStretch();
    headerRow->addWidget(refreshBtn);

    accountsTable = new QTableView();
    accountsTable->setObjectName("transactionTable");
    accountsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    accountsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    accountsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    accountsTable->setShowGrid(false);
    accountsTable->setAlternatingRowColors(true);
    accountsTable->setFocusPolicy(Qt::NoFocus);
    accountsTable->verticalHeader()->setVisible(false);
    accountsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    vl->addLayout(headerRow);
    vl->addWidget(accountsTable, 1);

    return tab;
}

QWidget *AdminDashboardWindow::buildCredentialsTab()
{
    QWidget *tab = new QWidget();
    tab->setStyleSheet("background:#F5F7FA;");

    QVBoxLayout *vl = new QVBoxLayout(tab);
    vl->setContentsMargins(30, 15, 30, 20);
    vl->setSpacing(20);

    QLabel *heading = new QLabel("Change Admin Credentials");
    heading->setStyleSheet(
        "font-size:20px; font-weight:bold; color:#273671;");

    QLabel *hint = new QLabel(
        "To update the admin username or password, enter your current password to verify your identity. "
        "Leave the new username or password blank to keep the existing value.");
    hint->setWordWrap(true);
    hint->setStyleSheet(
        "color:#718096; font-size:12px; font-weight:normal;");

    // ── Credential form card ───────────────────────────────────────
    QWidget *formCard = new QWidget();
    formCard->setStyleSheet(
        "QWidget { background:white; border-radius:16px; }"
        "QLabel { color:#273671; font-size:13px; font-weight:bold; background:transparent; }"
        "QLineEdit { background:white; color:#1A202C; border:1px solid #E6E9F4;"
        "            border-radius:8px; padding:8px 10px; font-size:13px; }"
        "QLineEdit:focus { border:1.5px solid #2D60FF; }"
        "QPushButton { background:#2D60FF; color:white; border-radius:8px;"
        "              font-weight:bold; font-size:14px; padding:10px; }"
        "QPushButton:hover { background:#1A4DDF; }"
        "QPushButton:pressed { background:#1235B5; margin-top:2px; }");
    formCard->setFixedWidth(480);

    QVBoxLayout *formLayout = new QVBoxLayout(formCard);
    formLayout->setContentsMargins(30, 15, 30, 30);
    formLayout->setSpacing(14);

    // Current password (always required)
    QLabel *currPassLbl = new QLabel("Current Password *");
    currentPassField = new QLineEdit();
    currentPassField->setPlaceholderText("Required to make any change");
    currentPassField->setEchoMode(QLineEdit::Password);
    currentPassField->setFixedHeight(42);

    // Separator
    QFrame *sep = new QFrame();
    sep->setFrameShape(QFrame::HLine);
    sep->setStyleSheet("color:#E6E9F4;");

    // New username
    QLabel *newUserLbl = new QLabel("New Username  (leave blank to keep current)");
    newUsernameField = new QLineEdit();
    newUsernameField->setPlaceholderText("e.g. superadmin");
    newUsernameField->setFixedHeight(42);

    // New password
    QLabel *newPassLbl = new QLabel("New Password  (leave blank to keep current)");
    newPassField = new QLineEdit();
    newPassField->setPlaceholderText("min. 6 characters");
    newPassField->setEchoMode(QLineEdit::Password);
    newPassField->setFixedHeight(42);

    // Confirm new password
    QLabel *confirmPassLbl = new QLabel("Confirm New Password");
    confirmPassField = new QLineEdit();
    confirmPassField->setPlaceholderText("repeat new password");
    confirmPassField->setEchoMode(QLineEdit::Password);
    confirmPassField->setFixedHeight(42);

    // Status label
    credStatusLabel = new QLabel("");
    credStatusLabel->setStyleSheet(
        "font-weight:normal; font-size:12px; color:#FF4D4D; background:transparent;");
    credStatusLabel->setWordWrap(true);
    credStatusLabel->hide();

    // Submit button
    changeCredBtn = new QPushButton("Update Credentials");
    changeCredBtn->setFixedHeight(46);
    changeCredBtn->setCursor(Qt::PointingHandCursor);

    formLayout->addWidget(currPassLbl);
    formLayout->addWidget(currentPassField);
    formLayout->addWidget(sep);
    formLayout->addWidget(newUserLbl);
    formLayout->addWidget(newUsernameField);
    formLayout->addWidget(newPassLbl);
    formLayout->addWidget(newPassField);
    formLayout->addWidget(confirmPassLbl);
    formLayout->addWidget(confirmPassField);
    formLayout->addWidget(credStatusLabel);
    formLayout->addWidget(changeCredBtn);

    // Clear error on any field change
    auto clearStatus = [this]() {
        credStatusLabel->hide();
        credStatusLabel->clear();
    };
    connect(currentPassField, &QLineEdit::textChanged, clearStatus);
    connect(newUsernameField, &QLineEdit::textChanged, clearStatus);
    connect(newPassField,     &QLineEdit::textChanged, clearStatus);
    connect(confirmPassField, &QLineEdit::textChanged, clearStatus);

    connect(changeCredBtn, &QPushButton::clicked,
            this, &AdminDashboardWindow::onChangeCredentials);

    vl->addWidget(heading);
    vl->addWidget(hint);
    vl->addWidget(formCard);
    vl->addStretch();

    return tab;
}

// ─── Data loading ─────────────────────────────────────────────────────────────

void AdminDashboardWindow::loadData()
{
    refreshOverview();
    // Tables are lazily loaded on tab switch via tabWidget::currentChanged
    // but pre-load users table (first content tab)
    refreshUsersTable();
}

void AdminDashboardWindow::refreshOverview()
{
    QLocale locale(QLocale::English);

    totalUsersLabel->setText(QString::number(db.getTotalUserCount()));
    totalBalanceLabel->setText(
        "$" + locale.toString(db.getSystemTotalBalance(), 'f', 2));
    totalDepositsLabel->setText(
        "$" + locale.toString(db.getSystemTotalDeposits(), 'f', 2));
    totalWithdrawalsLabel->setText(
        "$" + locale.toString(db.getSystemTotalWithdrawals(), 'f', 2));
}

void AdminDashboardWindow::refreshUsersTable(const QString &filter)
{
    usersTable->setModel(db.getAllUsers(filter));
}

void AdminDashboardWindow::refreshAccountsTable()
{
    accountsTable->setModel(db.getAllAccounts());
}

// ─── Slots ────────────────────────────────────────────────────────────────────

void AdminDashboardWindow::onSearchUsers(const QString &text)
{
    refreshUsersTable(text.trimmed());
}

void AdminDashboardWindow::onChangeCredentials()
{
    // 1. Gather inputs
    QString currentPass  = currentPassField->text();
    QString newUsername  = newUsernameField->text().trimmed();
    QString newPass      = newPassField->text();
    QString confirmPass  = confirmPassField->text();

    // 2. Validation
    if (currentPass.isEmpty()) {
        credStatusLabel->setText("Current password is required.");
        credStatusLabel->setStyleSheet(
            "font-weight:normal; font-size:12px; color:#FF4D4D; background:transparent;");
        credStatusLabel->show();
        return;
    }

    // If the admin typed a new password, both fields must match and meet length
    if (!newPass.isEmpty()) {
        if (newPass.length() < 6) {
            credStatusLabel->setText("New password must be at least 6 characters.");
            credStatusLabel->setStyleSheet(
                "font-weight:normal; font-size:12px; color:#FF4D4D; background:transparent;");
            credStatusLabel->show();
            return;
        }
        if (newPass != confirmPass) {
            credStatusLabel->setText("New passwords do not match.");
            credStatusLabel->setStyleSheet(
                "font-weight:normal; font-size:12px; color:#FF4D4D; background:transparent;");
            credStatusLabel->show();
            return;
        }
    }

    // 3. Attempt the DB update
    bool ok = db.changeAdminCredentials(currentPass, newUsername, newPass);
    if (ok) {
        QMessageBox::information(this, "Credentials", "✔  Credentials updated successfully!");
        credStatusLabel->setText("✔  Credentials updated successfully!");
        credStatusLabel->setStyleSheet(
            "font-weight:bold; font-size:13px; color:#38A169; background:transparent;");
        credStatusLabel->show();

        // Clear sensitive fields
        currentPassField->clear();
        newPassField->clear();
        confirmPassField->clear();
        newUsernameField->clear();
    } else {
        credStatusLabel->setText(
            "Update failed. Current password is incorrect, or a database error occurred.");
        credStatusLabel->setStyleSheet(
            "font-weight:normal; font-size:12px; color:#FF4D4D; background:transparent;");
        credStatusLabel->show();
    }
}
