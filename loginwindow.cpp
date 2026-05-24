#include "loginwindow.h"
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QStyleOption>

LoginWindow::LoginWindow(QWidget *parent) : BasePage(parent)
{
    this->setObjectName("loginPage");

    // ── Main Layout ────────────────────────────────────────────────
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 20, 50, 50);
    mainLayout->setAlignment(Qt::AlignCenter);

    // ── App Logo ───────────────────────────────────────────────────
    bankLogoLabel = new QLabel(this);
    QPixmap logoPixmap(":/resources/bank_pic.png");
    bankLogoLabel->setPixmap(logoPixmap.scaled(40, 40,
                                               Qt::KeepAspectRatio, Qt::SmoothTransformation));
    bankLogoLabel->setObjectName("logoLabel");

    // ── Header ─────────────────────────────────────────────────────
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(10);

    logoTitleLabel = new QLabel("ApexVault", this);
    logoTitleLabel->setObjectName("logoTitleLabel");

    themeToggleBtn = new QPushButton("🌙");
    themeToggleBtn->setFixedSize(40, 40);
    themeToggleBtn->setObjectName("themeToggleBtn");
    themeToggleBtn->setCursor(Qt::PointingHandCursor);

    headerLayout->addWidget(bankLogoLabel, 0, Qt::AlignLeft);
    headerLayout->addWidget(logoTitleLabel, 0, Qt::AlignLeft);
    headerLayout->addWidget(themeToggleBtn, 1, Qt::AlignRight);

    // ── Login Card ─────────────────────────────────────────────────
    QWidget *card = new QWidget();
    card->setObjectName("loginCard");
    card->setFixedSize(400, 510);   // Slightly taller to accommodate the combo

    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(40, 40, 40, 40);
    cardLayout->setSpacing(15);

    titleLabel = new QLabel("Welcome Back");
    titleLabel->setObjectName("loginTitle");

    // Username field
    userField = new QLineEdit();
    userField->setPlaceholderText("e.g. hammad4122");
    userField->setFixedHeight(45);

    // Password field
    passField = new QLineEdit();
    passField->setPlaceholderText("password");
    passField->setEchoMode(QLineEdit::Password);
    passField->setFixedHeight(45);

    // ── Role Selector ComboBox ─────────────────────────────────────
    // Placed directly below the password field so the admin can pick
    // their role before clicking Login.
    roleCombo = new QComboBox();
    roleCombo->addItem("👤  Login as User",  "user");
    roleCombo->addItem("🛡️  Login as Admin", "admin");
    roleCombo->setFixedHeight(40);
    roleCombo->setCursor(Qt::PointingHandCursor);
    roleCombo->setObjectName("roleCombo");
    // Style the combo to blend with the card theme
    roleCombo->setStyleSheet(
        "QComboBox { "
        "    border: 1px solid #E6E9F4; border-radius: 8px; "
        "    padding-left: 10px; background: #FFFFFF; color: #273671; "
        "    font-size: 13px; font-weight: bold; "
        "} "
        "QComboBox:focus { border: 1.5px solid #2D60FF; } "
        "QComboBox::drop-down { border: none; width: 30px; } "
        "QComboBox QAbstractItemView { "
        "    border: 1px solid #E6E9F4; border-radius: 8px; "
        "    background: #FFFFFF; color: #273671; "
        "    selection-background-color: #EEF2FF; "
        "} "
        );

    // Login button
    loginBtn = new QPushButton("Login");
    loginBtn->setCursor(Qt::PointingHandCursor);
    loginBtn->setFixedHeight(45);

    // Signup link (only relevant for user role)
    signupLink = new QPushButton("Don't have an account? Signup");
    signupLink->setObjectName("linkBtn");
    signupLink->setCursor(Qt::PointingHandCursor);
    signupLink->setFixedHeight(45);

    // Status / error label
    statusLabel = new QLabel("");
    statusLabel->setObjectName("statusLabel");
    statusLabel->hide();

    // ── Assemble Card ──────────────────────────────────────────────
    cardLayout->addWidget(titleLabel);
    cardLayout->addWidget(new QLabel("Username"));
    cardLayout->addWidget(userField);
    cardLayout->addWidget(new QLabel("Password"));
    cardLayout->addWidget(passField);
    cardLayout->addWidget(new QLabel("Login As"));
    cardLayout->addWidget(roleCombo);
    cardLayout->addWidget(statusLabel);
    cardLayout->addSpacing(10);
    cardLayout->addWidget(loginBtn);
    cardLayout->addWidget(signupLink);
    cardLayout->addStretch();

    // Card shadow
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(30);
    shadow->setXOffset(-5);
    shadow->setYOffset(7);
    shadow->setColor(QColor(0, 0, 0, 50));
    card->setGraphicsEffect(shadow);

    // ── Assemble Page ──────────────────────────────────────────────
    mainLayout->addLayout(headerLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(card, 0, Qt::AlignCenter);
    mainLayout->addStretch();

    // ── Connections ────────────────────────────────────────────────
    connect(loginBtn,   &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(signupLink, &QPushButton::clicked, this, &LoginWindow::openSignup);

    connect(userField, &QLineEdit::textChanged, [this]() {
        statusLabel->clear(); statusLabel->hide();
    });
    connect(passField, &QLineEdit::textChanged, [this]() {
        statusLabel->clear(); statusLabel->hide();
    });

    // Hide the signup link when Admin role is selected (admins don't self-register)
    connect(roleCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int /*index*/) {
                bool isAdmin = (roleCombo->currentData().toString() == "admin");
                signupLink->setVisible(!isAdmin);
                statusLabel->hide();
            });

    connect(themeToggleBtn, &QPushButton::clicked, [this]() {
        emit themeChangeRequested();
    });
}

// ─── Login handler ────────────────────────────────────────────────────────────

void LoginWindow::handleLogin() {
    QString user = userField->text().trimmed();
    QString pass = passField->text();
    QString role = roleCombo->currentData().toString(); // "user" or "admin"

    // Mandatory fields
    if (user.isEmpty() || pass.isEmpty()) {
        statusLabel->setText("Fields cannot be empty.");
        statusLabel->setStyleSheet("color: #E67E22;");
        statusLabel->show();
        return;
    }

    // ── Admin path ────────────────────────────────────────────────
    if (role == "admin") {
        if (db.authenticateAdmin(user, pass)) {
            QMessageBox::information(this, "Login", "Admin login successful.");
            emit adminLoginSuccessful();
        } else {
            statusLabel->setText("Invalid admin credentials.");
            statusLabel->setStyleSheet("color: #FF4D4D;");
            statusLabel->show();
        }
        return;
    }

    // ── User path ─────────────────────────────────────────────────
    if (db.userExist(user)) {
        int id = db.loginUser(user, pass);
        if (id != -1) {
            int accountID = db.getAccountID(id);
            QMessageBox::information(this, "Login", "Login Successful");
            UserSessionHandler *session = db.setUserInfo(id, accountID);
            emit loginSuccessful(session);
        } else {
            statusLabel->setText("Incorrect Password. Please try again.");
            statusLabel->setStyleSheet("color: #FF4D4D;");
            statusLabel->show();
        }
    } else {
        statusLabel->setText("User not found. Please Signup first.");
        statusLabel->setStyleSheet("color: #FF4D4D;");
        statusLabel->show();
    }
}

void LoginWindow::openSignup() {
    resetForm();
    emit signupRequested();
}

void LoginWindow::resetForm() {
    for (QLineEdit *f : {userField, passField}) {
        f->clear();
        f->setStyleSheet("");
    }
    roleCombo->setCurrentIndex(0);
    statusLabel->hide();
    signupLink->setVisible(true);
}
