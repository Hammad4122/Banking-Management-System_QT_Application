#include "loginwindow.h"
#include "database.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(1200, 600); // Keeping it consistent with your MainWindow size
    setWindowTitle("BMS - Secure Login");

    // Login Widget
    QWidget *centeral = new QWidget();
    centeral->setObjectName("loginCenteral");
    setCentralWidget(centeral);

    // Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centeral);
    mainLayout->setObjectName("mainLayout");
    mainLayout->setContentsMargins(50,50,50,50);

    // Title Label
    QLabel *titleLabel = new QLabel("Login to Your Account");
    titleLabel->setObjectName("titleLabel");

    // Line Edits (Input Fields)
    QLineEdit *userEntry = new QLineEdit();
    userEntry->setPlaceholderText("Username");

    QLineEdit *passEntry = new QLineEdit();
    passEntry->setPlaceholderText("Password");
    // This hides the characters as the user types (very important for banking!)
    passEntry->setEchoMode(QLineEdit::Password);

    // Login Button
    QPushButton *loginBtn = new QPushButton("Login");


    mainLayout->addStretch();

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(userEntry);
    mainLayout->addWidget(passEntry);
    mainLayout->addWidget(loginBtn);

    mainLayout->addStretch();




    // // STYLING
    // this->setStyleSheet(
    //     "#loginCentral { background-color: #F5F7FA; }"
    //     "#loginCard { background-color: #FFFFFF; border-radius: 20px; }"
    //     "#loginTitle { font-size: 26px; font-weight: bold; color: #273671; }"
    //     "QLabel { color: #273671; font-weight: bold; font-size: 13px; }"
    //     "QLineEdit { color: black; border: 1px solid #E6E9F4; border-radius: 8px; padding-left: 10px; background: #FFFFFF; }"
    //     "QLineEdit:focus { border: 1.5px solid #2D60FF; }"
    //     "QPushButton { background-color: #2D60FF; color: white; border-radius: 8px; font-weight: bold; font-size: 15px; }"
    //     "QPushButton:hover { background-color: #1A4DDF; }"
    //     "#linkBtn { background: transparent; color: #2D60FF; border: none; font-size: 13px; font-weight: normal; }"
    //     "#linkBtn:hover { text-decoration: underline; }"
    //     );

    // // Connections
    // connect(loginBtn, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    // connect(signupLink, &QPushButton::clicked, this, &LoginWindow::openSignup);
}

void LoginWindow::handleLogin() {
    // Here is where you use the logic from earlier
    QString user = userField->text();
    QString pass = passField->text();

    BankDB db;
    // db.loginUser(user, pass) logic goes here
    if (user == "admin" && pass == "1234") { // Temporary check
        QMessageBox::information(this, "Success", "Login Successful!");
        // Open MainWindow and close this
    } else {
        QMessageBox::warning(this, "Failed", "Invalid credentials.");
    }
}

void LoginWindow::openSignup() {
    // Code to switch to your SignupWindow class
}
