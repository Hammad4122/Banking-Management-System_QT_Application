#include "dashboardwindow.h"
#include "userdashboardwindow.h"
#include "admindashboardwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QStackedWidget>

DashboardWindow::DashboardWindow(QWidget *parent) : BasePage(parent)
{
    this->setObjectName("dashboardPage");

    // ── Root layout ────────────────────────────────────────────────
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    buildHeader(mainLayout);

    // ── Sub-dashboards ─────────────────────────────────────────────
    userDashboard  = new UserDashboardWindow(this);
    adminDashboard = new AdminDashboardWindow(this);

    contentStack = new QStackedWidget(this);
    contentStack->addWidget(userDashboard);   // Index 0 – user
    contentStack->addWidget(adminDashboard);  // Index 1 – admin

    mainLayout->addWidget(contentStack);

    // ── Forward theme-change signals ───────────────────────────────
    connect(userDashboard,  &UserDashboardWindow::themeChangeRequested,
            this,           &DashboardWindow::themeChangeRequested);
    connect(adminDashboard, &AdminDashboardWindow::themeChangeRequested,
            this,           &DashboardWindow::themeChangeRequested);
}

// ─── Header builder ───────────────────────────────────────────────────────────

void DashboardWindow::buildHeader(QVBoxLayout *mainLayout)
{
    QWidget *header = new QWidget();
    header->setObjectName("dashHeader");
    header->setFixedSize(1200, 65);

    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(10, 0, 0, 0);
    headerLayout->setSpacing(15);

    // Logo icon
    creditLogoLabel = new QLabel(this);
    QPixmap creditPixmap(":/resources/credit-card_blue.png");
    creditLogoLabel->setPixmap(creditPixmap.scaled(40, 40,
                                                   Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Title
    dashTitleLabel = new QLabel("BankDash.");
    dashTitleLabel->setObjectName("dashTitleLabel");

    // Account no (shown for user; hidden for admin)
    userAccountNo = new QLabel("");
    userAccountNo->setObjectName("userAccountNoLabel");

    // Theme toggle
    themeToggleBtn = new QPushButton("🌙");
    themeToggleBtn->setFixedSize(40, 40);
    themeToggleBtn->setObjectName("themeToggleBtn");
    themeToggleBtn->setCursor(Qt::PointingHandCursor);

    // User avatar
    userImgLabel = new QLabel();
    {
        QPixmap orig(":/resources/user.png");
        const int sz = 50;
        QPixmap rounded(sz, sz);
        rounded.fill(Qt::transparent);
        QPainter p(&rounded);
        p.setRenderHint(QPainter::Antialiasing);
        p.setRenderHint(QPainter::SmoothPixmapTransform);
        QPainterPath path;
        path.addEllipse(0, 0, sz, sz);
        p.setClipPath(path);
        p.drawPixmap(0, 0, sz, sz, orig);
        p.end();
        userImgLabel->setPixmap(rounded);
        userImgLabel->setFixedSize(sz, sz);
    }

    // Notification button
    notificationBtn = new QPushButton("");
    notificationBtn->setFixedSize(35, 35);
    notificationBtn->setObjectName("notificationBtn");
    notificationBtn->setCursor(Qt::PointingHandCursor);

    // Settings button
    settingBtn = new QPushButton("");
    settingBtn->setFixedSize(35, 35);
    settingBtn->setObjectName("settingBtn");
    settingBtn->setCursor(Qt::PointingHandCursor);

    // Logout button
    logoutBtn = new QPushButton("Logout");
    logoutBtn->setFixedSize(60, 30);
    logoutBtn->setObjectName("logoutBtn");
    logoutBtn->setCursor(Qt::PointingHandCursor);

    // Assemble header
    headerLayout->addWidget(creditLogoLabel, 0, Qt::AlignLeft);
    headerLayout->addWidget(dashTitleLabel,  0, Qt::AlignLeft);
    headerLayout->addWidget(userAccountNo,   0, Qt::AlignLeft);
    headerLayout->addStretch();
    headerLayout->addWidget(themeToggleBtn,  0, Qt::AlignRight);
    headerLayout->addWidget(logoutBtn,       0, Qt::AlignRight);
    headerLayout->addWidget(settingBtn,      0, Qt::AlignRight);
    headerLayout->addWidget(notificationBtn, 0, Qt::AlignRight);
    headerLayout->addSpacing(5);
    headerLayout->addWidget(userImgLabel,    0, Qt::AlignRight);
    headerLayout->addSpacing(10);

    mainLayout->addWidget(header);

    // ── Header connections ─────────────────────────────────────────
    connect(logoutBtn, &QPushButton::clicked, [this]() {
        userAccountNo->setText("");
        emit logoutRequested();
    });

    connect(themeToggleBtn, &QPushButton::clicked, [this]() {
        emit themeChangeRequested();
    });
}

// ─── Public initialization methods ───────────────────────────────────────────

void DashboardWindow::initializeUserDashboard(UserSessionHandler *session)
{
    // Show the account number in the header
    userAccountNo->setText("Account No.: " + QString::number(session->getAccountID()));

    // Switch to user sub-dashboard and populate it
    contentStack->setCurrentIndex(0);
    userDashboard->loadSession(session);
}

void DashboardWindow::initializeAdminDashboard()
{
    // Hide account-specific info in header for admin
    userAccountNo->setText("  Admin Panel");

    // Switch to admin sub-dashboard and refresh all data
    contentStack->setCurrentIndex(1);
    adminDashboard->loadData();
}
