#include "mainwindow.h"
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
#include "loginwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1200,600);
    setWindowTitle("Banking Management System");

}

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
