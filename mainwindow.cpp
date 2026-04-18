#include "mainwindow.h"
#include "signupwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QAction>
#include <QFontDatabase>
#include <QPushButton>
#include <QObject>
#include <QStyle>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setFixedSize(1200,600);
    // resize(1200,600);
    // setMinimumSize(400,300);
    // setMaximumSize(1500,800);
    setWindowTitle("Banking Management System");

    // 1. Create the Stacked Widget
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // 2. Create your pages
    loginPage = new LoginWindow();
    signupPage = new SignupWindow();
    dashboardPage = new DashboardWindow();

    // 3. Adding pages to the stack
    stackedWidget->addWidget(loginPage);    // Index 0
    stackedWidget->addWidget(signupPage);   // Index 1
    stackedWidget->addWidget(dashboardPage); // Index 2

    // 4. Start with Login
    stackedWidget->setCurrentIndex(0);  // Change back to 0

    connect(signupPage, &SignupWindow::loginRequested,[this](){
        stackedWidget->setCurrentIndex(0);
    });

    connect(loginPage, &LoginWindow::signupRequested,[this](){
        stackedWidget->setCurrentIndex(1);
    });

    // Connecting the login signal to a lambda that switches the index
    connect(loginPage, &LoginWindow::loginSuccessful, this, &MainWindow::onUserLoggedIn);

    connect(dashboardPage, &DashboardWindow::logoutRequested,[this](){
        loginPage->resetForm();
        stackedWidget->setCurrentIndex(0);
        QMessageBox::information(this,"Logout","Logged out successfully");
    });

    // Theme Connections
    connect(loginPage, &LoginWindow::themeChangeRequested, [this](){
        handleTheme();
    });
    connect(signupPage, &SignupWindow::themeChangeRequested, [this](){
        handleTheme();
    });
    connect(dashboardPage, &DashboardWindow::themeChangeRequested,[this](){
        handleTheme();
    });
};

void MainWindow::handleTheme(){
    // Call the static setter for isDarkMode
    BasePage::toggleGlobalTheme();

    loginPage->applyCurrentTheme();
    signupPage->applyCurrentTheme();
    dashboardPage->applyCurrentTheme();
};

// The slot implementation:
void MainWindow::onUserLoggedIn(UserSessionHandler* session) {
    // 1. Clean up the OLD session if it exists (Prevent Memory Leak)
    if (currentSession != nullptr) {
        delete currentSession;
        currentSession = nullptr;
    }

    currentSession = session;
    if (currentSession) {
        // 1. Pass the session to the Dashboard
        dashboardPage->initializeDashboard(currentSession);

        // 2. Switch the view
        stackedWidget->setCurrentIndex(2);
    }
}

MainWindow::~MainWindow(){delete currentSession;};
