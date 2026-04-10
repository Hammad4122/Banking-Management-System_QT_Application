#include "loginwindow.h"
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QStyleOption>

LoginWindow::LoginWindow(QWidget *parent): BasePage(parent)
{
    // Login Widget
    // QWidget *central = new QWidget();
    // central->setObjectName("loginCentral");
    // setCentralWidget(central);

    this->setObjectName("loginPage");

    // Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout");
    mainLayout->setContentsMargins(30,20,50,50);
    mainLayout->setAlignment(Qt::AlignCenter);

    // Create the label for the logo
    logoLabel = new QLabel();
    QPixmap logoPixmap(":/resources/bank_pic.png"); // Path from your .qrc
    logoLabel->setPixmap(logoPixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoLabel->setObjectName("logoLabel");

    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->setContentsMargins(0, 0, 0, 0); // Give it some padding from the window edge
    headerLayout->setSpacing(10); // Space between logo and text

    logoTitleLabel = new QLabel("<b>Banking</b><br>Management System", this);
    logoTitleLabel->setObjectName("logoTitleLabel");

    // Theme Toggle Button
    themeToggleBtn = new QPushButton("🌙");
    themeToggleBtn->setFixedSize(40,40);
    themeToggleBtn->setObjectName("themeToggleBtn");
    // isDarkMode = false;

    // 2. Add widgets to the header layout
    headerLayout->addWidget(logoLabel,0,Qt::AlignLeft);       //Goes to left
    headerLayout->addWidget(logoTitleLabel,0,Qt::AlignLeft); // Goes to left
    headerLayout->addWidget(themeToggleBtn,1,Qt::AlignRight);// Goes to right
    // headerLayout->addStretch();// Pushes everything to the left

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
    // this->setStyleSheet(
    //     "#loginPage { background-color: #F5F7FA; }"
    //     "#loginCard { background-color: #FFFFFF; border-radius: 20px;}"
    //     "#loginTitle { font-size: 26px; font-weight: bold; color: #273671; }"
    //     "#statusLabel {font-size: 13px; font-weight: normal;}"
    //     "QLabel { color: #273671; font-weight: bold; font-size: 13px; }"
    //     "QLineEdit { color: black; border: 1px solid #E6E9F4; border-radius: 8px; padding-left: 10px; background: #FFFFFF; }"
    //     "QLineEdit:focus { border: 1.5px solid #2D60FF; }"
    //     "QPushButton { background-color: #2D60FF; color: white; border-radius: 8px; font-weight: bold; font-size: 15px;}"
    //     "QPushButton:hover { background-color: #1A4DDF; }"
    //     "#linkBtn { background: transparent; color: #2D60FF; border: none; font-size: 13px; font-weight: normal; }"
    //     "#linkBtn:hover { text-decoration: underline; }"
    //     "QPushButton:pressed {background-color: #1a3ddf; margin-top: 2px;}"
    //     );

    // Connections
    connect(loginBtn, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(signupLink, &QPushButton::clicked, this, &LoginWindow::openSignup);
    // When the user types in the username box, clear the error message
    connect(userField, &QLineEdit::textChanged, [this]() {
        statusLabel->clear();
        statusLabel->hide();
    });
    connect(passField, &QLineEdit::textChanged, [this]() {
        statusLabel->clear();
        statusLabel->hide();
    });
    connect(themeToggleBtn, &QPushButton::clicked,[this](){
        // isDarkMode = !isDarkMode;
        emit themeChangeRequested();
    });
}

void LoginWindow::handleLogin() {
    QString user = userField->text().trimmed();
    QString pass = passField->text();

    // 1. Mandatory Fields Check
    if (user.isEmpty() || pass.isEmpty()) {
        statusLabel->setText("Fields cannot be empty.");
        statusLabel->setStyleSheet("color: #E67E22;"); // Soft Warning Orange
        statusLabel->show();
        return;
    }

    // 2. Credential Verification
    // (In the future, 'db.loginUser(user, pass)' will replace this part)
    if (db.userExist(user)) {
        if (db.loginUser(user,pass) != -1) {
            QMessageBox::information(this, "Login", "Login Successful");
            emit loginSuccessful();
        } else {
            statusLabel->setText("Incorrect Password. Please try again.");
            statusLabel->setStyleSheet("color: #FF4D4D;"); // Error Red
            statusLabel->show();
        }
    } else {
        statusLabel->setText("User not found. Please Signup first.");
        statusLabel->setStyleSheet("color: #FF4D4D;");
        statusLabel->show();
    }
}

void LoginWindow::openSignup() {
    // Code to switch to SignupWindow class
    resetForm();
    emit signupRequested();
}

void LoginWindow::resetForm(){

    // 1. Group all fields
    QList<QLineEdit*> fields = { userField, passField};

    // 2. Clear text and reset styles
    for(QLineEdit* f : fields) {
        f->clear();
        f->setStyleSheet("");
    }

    // 3. Hide all potential error messages
    statusLabel->hide();

};
