#include "signupwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>
#include <QRegularExpression>
#include <QMessageBox>
#include <qvalidator.h>

SignupWindow::SignupWindow(QWidget *parent): BasePage(parent) {
    this->setObjectName("signupPage");

    // Main Layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout");
    mainLayout->setContentsMargins(30,20,50,50);
    mainLayout->setAlignment(Qt::AlignCenter);

    // Create the label for the logo
    bankLogoLabel = new QLabel(this);
    QPixmap logoPixmap(":/resources/bank_pic.png"); // Path from your .qrc
    bankLogoLabel->setPixmap(logoPixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    bankLogoLabel->setObjectName("logoLabel");

    // Header Layout
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->setContentsMargins(0, 0, 0, 0); // Give it some padding from the window edge
    headerLayout->setSpacing(10); // Space between logo and text

    // Logo Title Label
    logoTitleLabel = new QLabel("ApexVault", this);
    logoTitleLabel->setObjectName("logoTitleLabel");

    // Theme Toggle Button
    themeToggleBtn = new QPushButton("🌙");
    themeToggleBtn->setFixedSize(40,40);
    themeToggleBtn->setObjectName("themeToggleBtn");
    themeToggleBtn->setCursor(Qt::PointingHandCursor);

    // 2. Add widgets to the header layout
    headerLayout->addWidget(bankLogoLabel,0,Qt::AlignLeft);       //Goes to left
    headerLayout->addWidget(logoTitleLabel,0,Qt::AlignLeft); // Goes to left
    headerLayout->addWidget(themeToggleBtn,1,Qt::AlignRight);// Goes to right

    // Card Widget
    QWidget *card = new QWidget();
    card->setObjectName("signupCard");
    card->setFixedSize(550,500);

    // Signup Card Layout
    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setObjectName("cardLayout");
    cardLayout->setContentsMargins(40,20,40,20);
    cardLayout->setSpacing(15);

    signupTitle = new QLabel("Signup");
    signupTitle->setObjectName("signupLabel");

    // First Name Input Field
    firstNameField = new QLineEdit();
    firstNameField->setPlaceholderText("First Name");
    firstNameField->setFixedHeight(45);

    // Second Name Input Field
    lastNameField = new QLineEdit();
    lastNameField->setPlaceholderText("Second Name");
    lastNameField->setFixedHeight(45);

    // Horizontal Layout for Name Fields
    QHBoxLayout *nameHLayout = new QHBoxLayout();
    nameHLayout->addWidget(firstNameField);
    nameHLayout->addWidget(lastNameField);

    // Username Input Field
    userNameField = new QLineEdit();
    userNameField->setPlaceholderText("Username");
    userNameField->setFixedHeight(45);

    // User CNIC Field
    cnicField = new QLineEdit();
    cnicField->setPlaceholderText("CNIC eg. xxxxx-xxxxxxx-x");
    cnicField->setFixedHeight(45);
    cnicField->setMaxLength(15);

    // Email Input Field
    emailField = new QLineEdit();
    emailField->setPlaceholderText("eg. example@address.com");
    emailField->setFixedHeight(45);

    // Mobile Number Input Field
    mobileNoField = new QLineEdit();
    mobileNoField->setFixedHeight(45);
    mobileNoField->setMaxLength(11);
    mobileNoField->setPlaceholderText("Phone# eg. 03xxxxxxxxx");

    // Password Input Field
    passField = new QLineEdit();
    passField->setPlaceholderText("Create a Strong Password");
    passField->setFixedHeight(45);

    // Confirm Password Input Field
    passConfirmField = new QLineEdit();
    passConfirmField->setPlaceholderText("Re-type your password");
    passConfirmField->setFixedHeight(45);

    // Tpin Input Field
    tpinField = new QLineEdit();
    tpinField->setPlaceholderText("Four digit Transaction PIN");
    tpinField->setFixedHeight(45);
    tpinField->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{4}$"), this));

    // Horizontal Layout for Password fields
    QHBoxLayout *passHLayout = new QHBoxLayout();
    passHLayout->addWidget(passField);
    passHLayout->addWidget(passConfirmField);
    passHLayout->addWidget(tpinField);
    passHLayout->setSpacing(3);

    // Signup Button
    signupBtn = new QPushButton("Create Account");
    signupBtn->setCursor(Qt::PointingHandCursor);
    signupBtn->setFixedHeight(45);

    // Login Link Button
    loginLinkBtn = new QPushButton("Already have an account? Login");
    loginLinkBtn->setCursor(Qt::PointingHandCursor);
    loginLinkBtn->setObjectName("loginLinkBtn");

    // Status Labels

    // Warnings
    statusLabel = new QLabel("");
    statusLabel->setObjectName("statusLabel");
    statusLabel->setFixedHeight(15);
    statusLabel->hide();

    // Name Status Label
    nameStatusLabel = new QLabel("Names must be 2-30 letters. Avoid numbers or symbols at the start/end.");
    nameStatusLabel->setObjectName("nameStatusLabel");
    nameStatusLabel->setFixedHeight(15);
    nameStatusLabel->hide();

    // Username Status Label
    usernameStatusLabel = new  QLabel("");
    usernameStatusLabel->setObjectName("usernameStatusLabel");
    usernameStatusLabel->setFixedHeight(15);
    usernameStatusLabel->hide();

    // Email Status Label
    emailStatusLabel = new QLabel("");
    emailStatusLabel->setObjectName("emailStatusLabel");
    emailStatusLabel->setFixedHeight(15);
    emailStatusLabel->hide();

    // CNIC Status Label
    cnicStatusLabel = new QLabel("");
    cnicStatusLabel->setObjectName("cnicStatusLabel");
    cnicStatusLabel->setFixedHeight(15);
    cnicStatusLabel->hide();

    // Mobile Number Status Label
    mobileNoStatusLabel = new QLabel("");
    mobileNoStatusLabel->setObjectName("mobileNoStatusLabel");
    mobileNoStatusLabel->setFixedHeight(30);
    mobileNoStatusLabel->hide();

    // Add Widgets to the card
    cardLayout->addWidget(signupTitle);
    cardLayout->addLayout(nameHLayout);
    cardLayout->addWidget(nameStatusLabel);
    cardLayout->addWidget(userNameField);
    cardLayout->addWidget(usernameStatusLabel);
    cardLayout->addWidget(emailField);
    cardLayout->addWidget(emailStatusLabel);
    cardLayout->addWidget(cnicField);
    cardLayout->addWidget(cnicStatusLabel);
    cardLayout->addWidget(mobileNoField);
    cardLayout->addWidget(mobileNoStatusLabel);
    cardLayout->addLayout(passHLayout);

    cardLayout->addSpacing(10);

    cardLayout->addWidget(statusLabel);
    cardLayout->addWidget(signupBtn);
    cardLayout->addWidget(loginLinkBtn);
    // cardLayout->addStretch();

    mainLayout->addLayout(headerLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(card,0,Qt::AlignCenter);
    mainLayout->addStretch();

    // --Card Shadow Effect--
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

    // Connections
    connect(signupBtn, &QPushButton::clicked, this, &SignupWindow::handleSignup);
    connect(loginLinkBtn, &QPushButton::clicked,[this](){
        resetForm();
        emit loginRequested();
    });
    connect(themeToggleBtn, &QPushButton::clicked,[this](){
        emit themeChangeRequested();
    });

    //-------------------------------------------------------------------------------------
    // 1. Create a map of Field -> Label
    QMap<QLineEdit*, QLabel*> fieldToLabel;
    fieldToLabel.insert(firstNameField, nameStatusLabel);
    fieldToLabel.insert(lastNameField, nameStatusLabel); // Both name fields use one label
    fieldToLabel.insert(userNameField, usernameStatusLabel);
    fieldToLabel.insert(emailField, emailStatusLabel);
    fieldToLabel.insert(cnicField,cnicStatusLabel);
    fieldToLabel.insert(mobileNoField, mobileNoStatusLabel);

    // 2. Loop through the map to connect them all
    for (auto it = fieldToLabel.begin(); it != fieldToLabel.end(); ++it) {
        QLineEdit* field = it.key();
        QLabel* label = it.value();

        connect(field, &QLineEdit::textChanged, [this, field, label]() {
            // Hide the specific label linked to this field
            label->hide();

            // Hide the general status label (the one at the bottom)
            statusLabel->hide();

            // Reset the red border of this specific field back to normal
            field->setStyleSheet("");
        });
    }

    // 3. Special case for passwords and tpin field (since they share one statusLabel)
    auto passAndPinReset = [this]() {
        statusLabel->hide();
        passField->setStyleSheet("");
        passConfirmField->setStyleSheet("");
        tpinField->setStyleSheet("");
    };
    connect(passField, &QLineEdit::textChanged, passAndPinReset);
    connect(passConfirmField, &QLineEdit::textChanged, passAndPinReset);
    connect(tpinField, &QLineEdit::textChanged, passAndPinReset);

    //-------------------------------------------------------------------------------------
    // connect(mobileNoField,&QLineEdit::,[this](){
    // });
};

void SignupWindow::handleSignup(){
    // 1. Reset the labels to hide
    statusLabel->hide();
    nameStatusLabel->hide();
    usernameStatusLabel->hide();
    emailStatusLabel->hide();
    cnicStatusLabel->hide();
    mobileNoStatusLabel->hide();

    QString firstName = firstNameField->text().trimmed();
    QString lastName = lastNameField->text().trimmed();
    QString userName = userNameField->text().trimmed();
    QString email = emailField->text().trimmed();
    QString cnic = cnicField->text().trimmed();
    QString mobileNo = mobileNoField->text().trimmed();
    QString password = passField->text().trimmed();
    QString confirmPass = passConfirmField->text().trimmed();
    QString tpin = tpinField->text();

    // Regex Expressions
    // This forces 2-30 characters while allowing spaces, hyphens, and apostrophes
    QRegularExpression nameRegex("^(?=.{2,30}$)[A-Za-z]+(?:[ '-][A-Za-z]+)*$");
    QRegularExpression usernameRegex("^[a-zA-Z0-9_]{5,15}$");
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    QRegularExpression cnicRegex("^\\d{5}-\\d{7}-\\d{1}$");
    QRegularExpression phoneRegex("^03[0-9]{9}$");
    QRegularExpression passRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d\\W_]{7,20}$");

    // Check for empty QString
    if (firstName.isEmpty() || lastName.isEmpty() || email.isEmpty() || cnic.isEmpty() ||
        mobileNo.isEmpty()  || password.isEmpty() || confirmPass.isEmpty())
    {
        statusLabel->setText("Fields cannot be empty.");
        statusLabel->setStyleSheet("color: #E67E22;"); // Soft Warning Orange
        statusLabel->show();
        return;
    }

    // Check for valid firstname and lastname
    if (!nameRegex.match(firstName).hasMatch())
    {
        nameStatusLabel->setStyleSheet("color: #FF4D4D;");

        firstNameField->setStyleSheet("border: 1.5px solid #FF4D4D;");

        nameStatusLabel->show();
        return;
    }

    if (!nameRegex.match(lastName).hasMatch()){
        nameStatusLabel->setStyleSheet("color: #FF4D4D;");

        lastNameField->setStyleSheet("border: 1.5px solid #FF4D4D;");

        nameStatusLabel->show();
        return;
    }

    // --Username--
    // Check for valid username
    if (!usernameRegex.match(userName).hasMatch())
    {
        usernameStatusLabel->setText("Username must be 5-15 characters. Use only letters, numbers, or underscores.");
        usernameStatusLabel->setStyleSheet("color: #FF4D4D;");

        userNameField->setStyleSheet("border: 1.5px solid #FF4D4D;");

        usernameStatusLabel->show();
        return;
    }

    // Check for username exists
    if (db.userExist(userName)){
        usernameStatusLabel->setText("Username already taken. Try another one.");
        usernameStatusLabel->setStyleSheet("color: #E74C3C;");

        userNameField->setStyleSheet("border: 1.5px solid #FF4D4D;");

        usernameStatusLabel->show();
        return;
    }

    // --Email--
    // Check for valid email
    if (!emailRegex.match(email).hasMatch()){
        emailStatusLabel->setText("Invalid email format.");
        emailStatusLabel->setStyleSheet("color: #FF4D4D;");

        emailField->setStyleSheet("border: 1.5px solid #FF4D4D;");

        emailStatusLabel->show();
        return;
    }

    // Check for email exists
    if (db.emailExist(email)){
        emailStatusLabel->setText("Email already exist.Please login or use a different email.");
        emailStatusLabel->setStyleSheet("color: #FF4D4D;");

        emailField->setStyleSheet("border: 1.5px solid #FF4D4D;");

        emailStatusLabel->show();
        return;
    }

    if (!cnicRegex.match(cnic).hasMatch()){
        cnicStatusLabel->setText("Invalid cnic format.");
        cnicStatusLabel->setStyleSheet("color: #FF4D4D;");

        cnicField->setStyleSheet("border: 1.5px solid #FF4D4D;");

        cnicStatusLabel->show();
        return;
    }

    if (db.cnicExist(cnic)){
        cnicStatusLabel->setText("This CNIC is already registered. Please login.");
        cnicStatusLabel->setStyleSheet("color: #FF4D4D;");

        cnicField->setStyleSheet("border: 1.5px solid #FF4D4D;");

        emailStatusLabel->show();
        return;
    }

    // --Mobile Number--
    if (!phoneRegex.match(mobileNo).hasMatch()){
        mobileNoStatusLabel->setStyleSheet("color: #FF4D4D;");
        mobileNoStatusLabel->setText("Invalid Mobile Number.");
        mobileNoField->setStyleSheet("border: 1.5px solid #FF4D4D;");

        mobileNoStatusLabel->show();
        return;
    }
    // Check for Mobile Number exist
    if (db.mobileNoExist(mobileNo)){
        mobileNoStatusLabel->setStyleSheet("color: #FF4D4D;");
        mobileNoStatusLabel->setText("This mobile number is already registered. Please login or use a different\n number.");
        mobileNoField->setStyleSheet("border: 1.5px solid #FF4D4D;");

        mobileNoStatusLabel->show();
        return;
    }

    // --Password--
    // 1. Check Format
    if (!passRegex.match(password).hasMatch()) {
        statusLabel->setText("Password must be 8-20 characters with Uppercase,Lowercase,and Number.");
        statusLabel->setStyleSheet("color: #FF4D4D;");

        passField->setStyleSheet("border: 1.5px solid #FF4D4D;");

        statusLabel->show();
        return;
    }

    // 2. Check Match
    if (password != confirmPass) {
        statusLabel->setText("Passwords do not match.");
        statusLabel->setStyleSheet("color: #FF4D4D;");

        passConfirmField->setStyleSheet("border: 1.5px solid #FF4D4D;");

        statusLabel->show();
        return;
    }

    if (tpin.isEmpty() || tpin.length() < 4){
        statusLabel->setText("Please enter a valid PIN");
        statusLabel->setStyleSheet("color: #FF4D4D;");

        tpinField->setStyleSheet("border: 1.5px solid #FF4D4D;");

        statusLabel->show();
        return;
    }

    if(db.registerUser(firstName,lastName,userName,email,cnic,password,mobileNo,tpin)){
        int id = db.getUserid(userName);
        if (id != -1){
            db.createAccount(id,"USD");

            QMessageBox::information(this, "Signup", "Account Created Successfully");
            qDebug() << "User Registered Successfully";

            resetForm();
            emit loginRequested();
        }
        else {
            qDebug() << "Critical Error: Could not create Account for UserID:" << id;
        }
    }
    else {
        qDebug() << "User couldn't be registered";
    }
};

void SignupWindow::resetForm(){

    // 1. Group all fields
    QList<QLineEdit*> fields = {
      firstNameField, lastNameField, userNameField,
      emailField, cnicField, mobileNoField, passField, passConfirmField,tpinField
    };

    // 2. Clear text and reset styles
    for(QLineEdit* f : fields) {
        f->clear();
        f->setStyleSheet(""); // Clears red borders and restores :focus blue
    }

    // 3. Hide all potential error messages
    statusLabel->hide();
    nameStatusLabel->hide();
    usernameStatusLabel->hide();
    emailStatusLabel->hide();
    cnicStatusLabel->hide();
    mobileNoStatusLabel->hide();

};
