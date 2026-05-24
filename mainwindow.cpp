#include "mainwindow.h"
#include "signupwindow.h"
#include <QMessageBox>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(1200, 650);
    setWindowTitle("ApexVault – BMS");

    // ── Stacked widget ─────────────────────────────────────────────
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // ── Pages ──────────────────────────────────────────────────────
    loginPage     = new LoginWindow();
    signupPage    = new SignupWindow();
    dashboardPage = new DashboardWindow();

    stackedWidget->addWidget(loginPage);      // 0
    stackedWidget->addWidget(signupPage);     // 1
    stackedWidget->addWidget(dashboardPage);  // 2

    stackedWidget->setCurrentIndex(0);

    // ── Navigation signals ─────────────────────────────────────────
    connect(signupPage, &SignupWindow::loginRequested, [this]() {
        stackedWidget->setCurrentIndex(0);
    });

    connect(loginPage, &LoginWindow::signupRequested, [this]() {
        stackedWidget->setCurrentIndex(1);
    });

    // ── User login ─────────────────────────────────────────────────
    connect(loginPage, &LoginWindow::loginSuccessful,
            this,      &MainWindow::onUserLoggedIn);

    // ── Admin login ────────────────────────────────────────────────
    connect(loginPage, &LoginWindow::adminLoginSuccessful,
            this,      &MainWindow::onAdminLoggedIn);

    // ── Logout ─────────────────────────────────────────────────────
    connect(dashboardPage, &DashboardWindow::logoutRequested, [this]() {
        loginPage->resetForm();
        stackedWidget->setCurrentIndex(0);
        QMessageBox::information(this, "Logout", "Logged out successfully.");
    });

    // ── Theme ──────────────────────────────────────────────────────
    connect(loginPage,     &LoginWindow::themeChangeRequested,
            this, &MainWindow::handleTheme);
    connect(signupPage,    &SignupWindow::themeChangeRequested,
            this, &MainWindow::handleTheme);
    connect(dashboardPage, &DashboardWindow::themeChangeRequested,
            this, &MainWindow::handleTheme);
}

// ─── Theme ────────────────────────────────────────────────────────────────────

void MainWindow::handleTheme()
{
    BasePage::toggleGlobalTheme();
    loginPage->applyCurrentTheme();
    signupPage->applyCurrentTheme();
    dashboardPage->applyCurrentTheme();
}

// ─── User login ───────────────────────────────────────────────────────────────

void MainWindow::onUserLoggedIn(UserSessionHandler *session)
{
    if (currentSession) {
        delete currentSession;
        currentSession = nullptr;
    }
    currentSession = session;

    if (currentSession) {
        dashboardPage->initializeUserDashboard(currentSession);
        stackedWidget->setCurrentIndex(2);
    }
}

// ─── Admin login ──────────────────────────────────────────────────────────────

void MainWindow::onAdminLoggedIn()
{
    // No user session needed for admin
    if (currentSession) {
        delete currentSession;
        currentSession = nullptr;
    }

    dashboardPage->initializeAdminDashboard();
    stackedWidget->setCurrentIndex(2);
}

MainWindow::~MainWindow()
{
    delete currentSession;
}
