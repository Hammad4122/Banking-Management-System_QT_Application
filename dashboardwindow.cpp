#include "dashboardwindow.h"
#include <qboxlayout.h>
#include <QPainter>
#include <QPainterPath>
#include <QLocale>

// Title Color: #343C6A

DashboardWindow::DashboardWindow(QWidget *parent): BasePage(parent) {

    this->setObjectName("dashboardPage");
    // -- Main Layout --
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    // -- Header --
    QWidget *header = new QWidget();
    header->setObjectName("dashHeader");
    header->setFixedSize(1200,65);
    // Header Layout
    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->addSpacing(10);
    headerLayout->setContentsMargins(0,0,0,0);

    // Dashboard Title Logo
    creditLogoLabel = new QLabel(this);
    QPixmap creditPixmap(":/resources/credit-card_blue.png"); // Path from your .qrc
    creditLogoLabel->setPixmap(creditPixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Dashboard Title Label
    dashTitleLabel = new QLabel("BankDash.");
    dashTitleLabel->setObjectName("dashTitleLabel");

    // Theme Toggle Button
    themeToggleBtn = new QPushButton("🌙");
    themeToggleBtn->setFixedSize(40,40);
    themeToggleBtn->setObjectName("themeToggleBtn");
    themeToggleBtn->setCursor(Qt::PointingHandCursor);

    // -- User Image --
    userImgLabel = new QLabel();
    // 1. Load your pixmap
    QPixmap originalPixmap(":/resources/my_pic.png");
    int size = 50; // Your desired size
    // 2. Prepare a transparent pixmap for the circle
    QPixmap rounded(size, size);
    rounded.fill(Qt::transparent);
    // 3. Use QPainter to draw the circle
    QPainter painter(&rounded);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    // Create the circular path
    QPainterPath path;
    path.addEllipse(0, 0, size, size);
    painter.setClipPath(path);
    // Draw the original image into the circular clip
    painter.drawPixmap(0, 0, size, size, originalPixmap);
    painter.end();
    // 4. Set it to your label
    userImgLabel->setPixmap(rounded);
    userImgLabel->setFixedSize(size, size);

    // Notificatoin Icon
    notificationBtn = new QPushButton("");
    notificationBtn->setFixedSize(35,35);
    notificationBtn->setObjectName("notificationBtn");
    notificationBtn->setCursor(Qt::PointingHandCursor);

    // Settings Icon
    settingBtn = new QPushButton("");
    settingBtn->setFixedSize(35,35);
    settingBtn->setObjectName("settingBtn");
    settingBtn->setCursor(Qt::PointingHandCursor);

    // Logout Btn
    logoutBtn = new QPushButton("Logout");
    logoutBtn->setFixedSize(55,30);
    logoutBtn->setObjectName("logoutBtn");
    logoutBtn->setCursor(Qt::PointingHandCursor);

    // User Full Name Label
    userGreetFullNameLabel = new QLabel();
    userGreetFullNameLabel->setObjectName("userGreetingLabel");

    // Username Label
    usernameLabel = new QLabel();

    // User Email Label
    userEmail = new QLabel();

    // User Mobile Number Label
    userMobileNO = new QLabel();

    // User Balance Label
    userBalance = new QLabel();
    userBalance->setContentsMargins(10,0,0,0);

    // Card Holder Label
    cardHolderLabel = new QLabel();
    cardHolderLabel->setContentsMargins(10,0,0,0);

    // Card Expiry Date Label
    cardExpiryLabel = new QLabel();
    cardExpiryLabel->setContentsMargins(0,0,10,0);

    // Card Number Label
    cardNumber = new QLabel();
    cardNumber->setContentsMargins(10,0,0,0);


    // Header Layout
    headerLayout->addWidget(creditLogoLabel,0,Qt::AlignLeft);
    headerLayout->addWidget(dashTitleLabel,0,Qt::AlignLeft);
    headerLayout->setSpacing(20);
    headerLayout->addWidget(userGreetFullNameLabel,0,Qt::AlignLeft);
    headerLayout->addStretch();
    headerLayout->addWidget(themeToggleBtn,-1,Qt::AlignRight);
    headerLayout->addSpacing(10);
    headerLayout->addWidget(logoutBtn,-1,Qt::AlignRight);
    headerLayout->addSpacing(10);
    headerLayout->addWidget(settingBtn,-1,Qt::AlignRight);
    headerLayout->setSpacing(15);
    headerLayout->addWidget(notificationBtn,-1,Qt::AlignRight);
    headerLayout->addSpacing(25);
    headerLayout->addWidget(userImgLabel,-1,Qt::AlignRight);
    headerLayout->addSpacing(10);


    // The "Content Host"
    // This is the widget that will hold content seperately
    QWidget *contentContainer = new QWidget();
    contentContainer->setFixedSize(1200,470);
    contentContainer->setObjectName("contentContainer");
    QVBoxLayout *containerLayout = new QVBoxLayout(contentContainer);


    // -- Credit Card Widget --
    QWidget *card = new QWidget();
    card->setObjectName("dashCard");
    card->setFixedSize(350,220);
    // Credit Card Layout
    QVBoxLayout *mainCardLayout = new QVBoxLayout(card);
    //Credit Card Chip
    creditChipLabel = new QLabel();
    QPixmap creditChipPixmap(":/resources/chip.png"); // Path from your .qrc
    creditChipLabel->setPixmap(creditChipPixmap.scaled(45, 45, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    creditChipLabel->setContentsMargins(0,10,10,0);
    // Card Header
    QHBoxLayout *cardHeader = new QHBoxLayout();
    cardHeader->addWidget(userBalance,0,Qt::AlignLeft);
    cardHeader->addWidget(creditChipLabel,0,Qt::AlignRight);
    // Card Middle Section
    QHBoxLayout *cardMiddle = new QHBoxLayout();
    cardMiddle->addWidget(cardHolderLabel,0,Qt::AlignLeft);
    cardMiddle->addSpacing(10);
    cardMiddle->addWidget(cardExpiryLabel,0);
    // Added card header and middle section in the card Layout
    mainCardLayout->addLayout(cardHeader);
    mainCardLayout->addSpacing(13);
    mainCardLayout->addLayout(cardMiddle);
    mainCardLayout->addStretch();
    // -- Credit Card Higlight Section (Bottom) --
    QWidget *cardHighlightSection = new QWidget(card); // Important: dashCard is the parent
    cardHighlightSection->setObjectName("cardHighlightSection");
    // Positioning it in the bottom section of the card.
    // For a 220 height card, The bottom 60 pixels is good.
    cardHighlightSection->setGeometry(0, 160, 350, 60);
    // Adding the Card Number and other labels as children of THIS cardHighlightSection
    // Card Higligh Section Layout
    QHBoxLayout *highlightLayout = new QHBoxLayout(cardHighlightSection);
    // Master Card Circles
    creditCircles = new QLabel();
    QPixmap creditCirclePixMap(":/resources/master_card_overlapping-circles.png");
    creditCircles->setPixmap(creditCirclePixMap.scaled(50,50,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    creditCircles->setContentsMargins(0,0,5,0);


    //Added card number and mastercard Circles in the higlight layout
    highlightLayout->addWidget(cardNumber,0,Qt::AlignLeft);
    highlightLayout->addWidget(creditCircles,0,Qt::AlignRight | Qt::AlignVCenter);


    // Added the card in the Container layout
    containerLayout->addWidget(card);
    containerLayout->addStretch();


    // Added the header and content container widget
    mainLayout->addWidget(header);
    mainLayout->addWidget(contentContainer);
    mainLayout->addStretch();
    mainLayout->addWidget(usernameLabel);
    mainLayout->addWidget(userEmail);
    mainLayout->addWidget(userMobileNO);


    // Buttons Connection
    connect(logoutBtn, &QPushButton::clicked, [this](){
        emit logoutRequested();
    });
    connect(themeToggleBtn, &QPushButton::clicked,[this](){
        emit themeChangeRequested();
    });
}

void DashboardWindow::initializeDashboard(UserSessionHandler* session){
    userGreetFullNameLabel->setText("Welcome, " + session->getFullName());
    usernameLabel->setText(session->getUsername());
    userEmail->setText(session->getEmail());
    userMobileNO->setText(session->getMobileNo());

    // 1. Initialize the locale (English format provides the commas you see in banking apps)
    QLocale locale(QLocale::English);
    // 2. Format the balance into a string with commas and 2 decimal places
    QString formattedBalance = locale.toString(54783483.4398, 'f', 2);
    // 3. Inject the formatted string into the HTML
    userBalance->setText(QString(
                             "<span style='font-size: 13px; font-weight: 600; color: rgba(255, 255, 255, 0.8);'>Balance</span><br>"
                             "<span style='font-size: 20px; font-weight: bold; color: white;'>$%1</span>"
                             ).arg(formattedBalance));

    // 1. Format the Holder Label
    cardHolderLabel->setText(QString(
                                 "<span style='font-size: 10px; color: rgba(255, 255, 255, 0.8);'>CARD HOLDER</span><br>"
                                 "<span style='font-size: 14px; font-weight: bold; color: white;'>%1</span>"
                                 ).arg(session->getFullName().toUpper())); // toUpper() matches the "Banking" aesthetic

    // 2. Format the Expiry Label
    // Assuming you have a getExpiryDate() or similar in your session
    cardExpiryLabel->setText(QString(
                                 "<span style='font-size: 10px; color: rgba(255, 255, 255, 0.8);'>VALID THRU</span><br>"
                                 "<span style='font-size: 14px; font-weight: bold; color: white;'>%1</span>"
                                 ).arg("04/31")); // Replace with session->getExpiryDate() when your DB is ready

    cardNumber->setText("5123  **** **** 8892");
    cardNumber->setStyleSheet("font-weight: 600;font-size: 20px;font: 'roboto';");
}
