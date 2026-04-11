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
    setWindowTitle("Banking Management System");

    // 1. Create the Stacked Widget
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // 2. Create your pages
    loginPage = new LoginWindow();
    signupPage = new SignupWindow();
    dashboardPage = new DashboardWindow();

    // 3. Add them to the stack
    stackedWidget->addWidget(loginPage);    // Index 0
    stackedWidget->addWidget(signupPage);   // Index 1
    stackedWidget->addWidget(dashboardPage); // Index 2

    // // Add this right before or after you add the pages to the stack
    // loginPage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // dashboardPage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 4. Start with Login
    stackedWidget->setCurrentIndex(0);  // Change back to 0

    connect(signupPage, &SignupWindow::loginRequested,[this](){
        stackedWidget->setCurrentIndex(0);
    });
    // Connect the login signal to a lambda that switches the index
    connect(loginPage, &LoginWindow::signupRequested,[this](){
        stackedWidget->setCurrentIndex(1);
    });
    connect(loginPage, &LoginWindow::loginSuccessful, [this]() {
        stackedWidget->setCurrentIndex(2); // Switch to Dashboard
    });
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



//     QWidget *centeral = new QWidget(this);
//     setCentralWidget(centeral);
//     centeral->setObjectName("centeral");


//     QHBoxLayout *mainLayout = new QHBoxLayout(centeral);


//     QWidget *sidebarWidget = new QWidget();
//     QVBoxLayout *sidebar = new QVBoxLayout(sidebarWidget);
//     sidebarWidget->setObjectName("sidebar");


//     dashboard = new QPushButton("  Dashboard");
//     transactions = new QPushButton("  Transactions");
//     accounts = new QPushButton("  Accounts");


//     // Dashboard icon
//     dashboard->setIcon(QIcon("C:/Bahria University/2nd Semester/Projects/OOPs_Lab/BankingManagementSystem_Project/home.png"));
//     dashboard->setIconSize(QSize(20,20));
//     // Transactions icon
//     transactions->setIcon(QIcon("C:/Bahria University/2nd Semester/Projects/OOPs_Lab/BankingManagementSystem_Project/transaction.png")); // Update with your actual path
//     transactions->setIconSize(QSize(20, 20));
//     // Accounts icon
//     accounts->setIcon(QIcon("C:/Bahria University/2nd Semester/Projects/OOPs_Lab/BankingManagementSystem_Project/accounts.png")); // Update with your actual path
//     accounts->setIconSize(QSize(20, 20));


//     sidebar->addWidget(dashboard);
//     sidebar->addWidget(transactions);
//     sidebar->addWidget(accounts);
//     sidebar->addStretch();


//     QWidget *contentContainer = new QWidget();
//     contentLayout = new QVBoxLayout(contentContainer);
//     contentLayout->setContentsMargins(20, 10, 10, 10);


//     sidebarWidget->setLayout(sidebar);
//     mainLayout->addWidget(sidebarWidget, 1);   // Sidebar takes 1 part
//     mainLayout->addWidget(contentContainer, 6);


//     sidebar->setSpacing(15);
//     sidebar->setContentsMargins(5, 5, 5, 5);
//     sidebarWidget->setFixedWidth(150);


//     dashboard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//     transactions->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//     accounts->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

//     // dashboard button
//     connect(dashboard,&QPushButton::clicked,this,[&](){
//         updateButtonStyles(dashboard);
//         showDashboard();
//     });
//     // transaction button
//     connect(transactions,&QPushButton::clicked,this,[&](){
//         updateButtonStyles(transactions);
//         showTransactions();
//     });
//     // accounts button
//     connect(accounts,&QPushButton::clicked,this,[&](){
//         updateButtonStyles(accounts);
//         showAccounts();
//     });


//     /* style.qss */
//     this->setStyleSheet(
//         "#sidebar { background-color: #FFFFFF; }"
//         "QPushButton {"
//         "background-color: #FFFFFF;"
//         "border: none;"
//         "padding: 0px;"
//         "text-align: left;"
//         "font-family: sans-serif;"
//         "color: #B1B1B1;"
//         "font-size: 15px;"
//         "}"

//         /* This rule applies when we set the 'active' property to true */
//         "QPushButton[active=\"true\"] {"
//         "color: #2D60FF;"
//         "font-weight: bold;"
//         "}"

//         /* Hover and pressed */
//         "QPushButton:hover { color: #2D60FF; }"
//         "QPushButton:pressed { color: #0039CB; }"

//         "#centeral { background-color: #F5F7FA; }"

//         );

//     //Sets Default
//     updateButtonStyles(dashboard);
//     showDashboard();
// }


// void MainWindow::updateButtonStyles(QPushButton* activeBtn) {
//     QList<QPushButton*> buttons = {dashboard, transactions, accounts};

//     for (QPushButton* btn : buttons) {
//         bool isActive = (btn == activeBtn);
//         btn->setProperty("active", isActive);


//         // Update Icons based on state
//         if (btn == dashboard) {
//             dashboard->setIcon(isActive ? QIcon("C:/Bahria University/2nd Semester/Projects/OOPs_Lab/BankingManagementSystem_Project/home_blue.png") : QIcon("C:/Bahria University/2nd Semester/Projects/OOPs_Lab/BankingManagementSystem_Project/home.png"));
//         } else if (btn == transactions) {
//             transactions->setIcon(isActive ? QIcon("C:/Bahria University/2nd Semester/Projects/OOPs_Lab/BankingManagementSystem_Project/transaction_blue.png") : QIcon("C:/Bahria University/2nd Semester/Projects/OOPs_Lab/BankingManagementSystem_Project/transaction.png"));
//         } else if (btn == accounts) {
//             accounts->setIcon(isActive ? QIcon("C:/Bahria University/2nd Semester/Projects/OOPs_Lab/BankingManagementSystem_Project/accounts_blue.png") : QIcon("C:/Bahria University/2nd Semester/Projects/OOPs_Lab/BankingManagementSystem_Project/accounts.png"));
//         }


//         btn->style()->unpolish(btn);
//         btn->style()->polish(btn);
//     }
// }


// void MainWindow::clearLayout(QLayout *layout) {
//     if (!layout) return;

//     while (QLayoutItem *item = layout->takeAt(0)) {
//         // 1. If it's a widget, delete it
//         if (QWidget *widget = item->widget()) {
//             widget->deleteLater();
//         }
//         // 2. If it's a sub-layout
//         else if (QLayout *childLayout = item->layout()) {
//             clearLayout(childLayout);
//         }

//         // 3. Delete the item itself (the "container" in the layout)
//         delete item;
//     }
// }


// void MainWindow::showDashboard() {
//     clearLayout(contentLayout);
// }
// void MainWindow::showTransactions(){
//     clearLayout(contentLayout);
// }
// void MainWindow::showAccounts(){
//     clearLayout(contentLayout);
// }

MainWindow::~MainWindow(){};
