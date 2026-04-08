#include "loginwindow.h"
#include "database.h"
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(1200, 600); // Keeping it consistent with your MainWindow size
    setWindowTitle("BMS - Secure Login");

    // Login Widget
    QWidget *central = new QWidget();
    central->setObjectName("loginCentral");
    setCentralWidget(central);

    // Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->setObjectName("mainLayout");
    mainLayout->setContentsMargins(30,20,50,50);
    mainLayout->setAlignment(Qt::AlignCenter);

    // Create the label for the logo
    logoLabel = new QLabel();
    QPixmap logoPixmap("C:\\Bahria University\\2nd Semester\\Projects\\OOPs_Lab\\BankingManagementSystem_Project\\bank_pic.png"); // Path from your .qrc
    logoLabel->setPixmap(logoPixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->setContentsMargins(0, 0, 0, 0); // Give it some padding from the window edge
    headerLayout->setSpacing(10); // Space between logo and text

    logoTitleLabel = new QLabel("<b>Banking</b><br>Management System", this);
    logoTitleLabel->setStyleSheet("font-size: 14px; color: #333; line-height: 1.2;");

    // 2. Add widgets to the header layout
    headerLayout->addWidget(logoLabel);
    headerLayout->addWidget(logoTitleLabel);
    headerLayout->addStretch();// Pushes everything to the left

    QWidget *card = new QWidget();
    card->setObjectName("loginCard");
    card->setFixedSize(400,450);

    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(40,40,40,40);
    cardLayout->setSpacing(15);


    // Title Label
    titleLabel = new QLabel("Welcome Back");
    titleLabel->setObjectName("loginTitle");

    // Line Edits (Input Fields)
    userField = new QLineEdit();
    userField->setPlaceholderText("eg. hammad4122");
    userField->setFixedHeight(45);

    passField = new QLineEdit();
    passField->setPlaceholderText("password");
    // This hides the characters as the user types (very important for banking!)
    passField->setEchoMode(QLineEdit::Password);
    passField->setFixedHeight(45);

    // Login Button
    loginBtn = new QPushButton("Login");
    loginBtn->setCursor(Qt::PointingHandCursor);
    loginBtn->setFixedHeight(45);

    // Signup Page Button
    signupLink = new QPushButton("Don't have an account? Signup");
    signupLink->setObjectName("linkBtn");
    signupLink->setCursor(Qt::PointingHandCursor);
    signupLink->setFixedHeight(45);

    statusLabel = new QLabel("");
    statusLabel->setObjectName("statusLabel");
    statusLabel->hide();

    cardLayout->addWidget(titleLabel);
    cardLayout->addWidget(new QLabel("Username"));
    cardLayout->addWidget(userField);
    cardLayout->addWidget(new QLabel("Password"));
    cardLayout->addWidget(passField);
    cardLayout->addWidget(statusLabel);
    cardLayout->addSpacing(10);
    cardLayout->addWidget(loginBtn);
    cardLayout->addWidget(signupLink);
    cardLayout->addStretch();
    mainLayout->addLayout(headerLayout);

    mainLayout->addStretch();
    mainLayout->addWidget(card,0,Qt::AlignCenter);
    mainLayout->addStretch();


    // Card Shadow Effect
    // Create the shadow effect
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    // 15-20 is usually the "sweet spot" for a soft modern look
    shadow->setBlurRadius(30);
    // Setting X to 0 and Y to 5 makes the shadow appear slightly below the card
    shadow->setXOffset(-5);
    shadow->setYOffset(7);
    // Use a light transparent black (Alpha 50-80) so it's not too harsh
    shadow->setColor(QColor(0, 0, 0, 50));
    // Apply it to the card
    card->setGraphicsEffect(shadow);

    // STYLING
    this->setStyleSheet(
        "#loginCentral { background-color: #F5F7FA; }"
        "#loginCard { background-color: #FFFFFF; border-radius: 20px;}"
        "#loginTitle { font-size: 26px; font-weight: bold; color: #273671; }"
        "#statusLabel {font-size: 13px; font-weight: normal;}"
        "QLabel { color: #273671; font-weight: bold; font-size: 13px; }"
        "QLineEdit { color: black; border: 1px solid #E6E9F4; border-radius: 8px; padding-left: 10px; background: #FFFFFF; }"
        "QLineEdit:focus { border: 1.5px solid #2D60FF; }"
        "QPushButton { background-color: #2D60FF; color: white; border-radius: 8px; font-weight: bold; font-size: 15px; }"
        "QPushButton:hover { background-color: #1A4DDF; }"
        "#linkBtn { background: transparent; color: #2D60FF; border: none; font-size: 13px; font-weight: normal; }"
        "#linkBtn:hover { text-decoration: underline; }"
        );

    // Connections
    connect(loginBtn, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(signupLink, &QPushButton::clicked, this, &LoginWindow::openSignup);
    // When the user types in the username box, clear the error message
    connect(userField, &QLineEdit::textChanged, [this]() {
        statusLabel->clear();
        statusLabel->hide();
    });
}

void LoginWindow::handleLogin() {
    // Here is where you use the logic from earlier
    QString user = userField->text();
    QString pass = passField->text();

    BankDB db;



    // db.loginUser(user, pass) logic goes here
    if (user == "admin" && !pass.isEmpty()) { // Temporary check
        if (user == "admin" && pass == "1234"){
            QMessageBox::information(this,"Login","Login Successful");
        }
        else {
            statusLabel->show();
            statusLabel->setText("Incorrect Username or Password");
            statusLabel->setStyleSheet("color: #FF4D4D;");
        }
    } else {
        statusLabel->show();
        statusLabel->setText("User not found. Signup to Create an Account");
        statusLabel->setStyleSheet("color: #FF4D4D;");
    }
}

void LoginWindow::openSignup() {
    // Code to switch to your SignupWindow class
}
