#include "dashboardwindow.h"
#include <qboxlayout.h>
#include <QPainter>
#include <QPainterPath>
#include <QLocale>
#include "transactiondialog.h"

// Title Color: #343C6A --

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

    // Action Buttons Widget
    QWidget *actionButtonsWidget = new QWidget();
    actionButtonsWidget->setFixedWidth(350);

    // Action Buttons with layout
    QHBoxLayout *actionBtnLayout = new QHBoxLayout(actionButtonsWidget);
    actionBtnLayout->setContentsMargins(0,2,0,2);

    //Action Buttons Initialization
    depositBtn = new QPushButton("Deposit");
    transferBtn = new QPushButton("Transfer");
    withdrawBtn = new QPushButton("Withdraw");

    // Action Buttons and Label Object Names
    depositBtn->setObjectName("depositBtn");
    transferBtn->setObjectName("transferBtn");
    withdrawBtn->setObjectName("withdrawBtn");

    // Action Buttons Setting Cursor
    depositBtn->setCursor(Qt::PointingHandCursor);
    transferBtn->setCursor(Qt::PointingHandCursor);
    withdrawBtn->setCursor(Qt::PointingHandCursor);

    // Adding Action Buttons to the layout
    actionBtnLayout->addWidget(depositBtn);
    actionBtnLayout->addWidget(transferBtn);
    actionBtnLayout->addWidget(withdrawBtn);

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

    // Cards H Layout container
    QHBoxLayout *cardHLayout = new QHBoxLayout();
    cardHLayout->setSpacing(10);

    // -- Credit Card Widget --
    QWidget *debitCard = new QWidget();
    debitCard->setObjectName("dashDebitCard");
    debitCard->setFixedSize(350,220);
    // Credit Card Layout
    QVBoxLayout *mainCardLayout = new QVBoxLayout(debitCard);
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
    QWidget *cardHighlightSection = new QWidget(debitCard); // Important: dashCard is the parent
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

    // Income Card
    QWidget *incomeCard = new QWidget();
    incomeCard->setObjectName("incomeCard");
    incomeCard->setStyleSheet("background-color: #FFFFFF;border-radius: 20px; padding: 10px; ");
    incomeCard->setFixedSize(260,220);
    incomeCard->setContentsMargins(0,0,0,0);
    QVBoxLayout *incomeCardLayout = new QVBoxLayout(incomeCard);

    // Expense Card
    QWidget *expenseCard = new QWidget();
    expenseCard->setObjectName("expenseCard");
    expenseCard->setStyleSheet("background-color: #FFFFFF;border-radius: 20px; border: 1px solid #f0f0f0;");
    expenseCard->setFixedSize(260,220);
    expenseCard->setContentsMargins(0,0,0,0);
    QVBoxLayout *expenseCardLayout = new QVBoxLayout(expenseCard);

    // Saving Card
    QWidget *savingCard = new QWidget();
    savingCard->setObjectName("savingCard");
    savingCard->setStyleSheet("background-color: #FFFFFF;border-radius: 20px; border: 1px solid #f0f0f0;");
    savingCard->setFixedSize(260,220);
    savingCard->setContentsMargins(0,0,0,0);
    QVBoxLayout *savingCardLayout = new QVBoxLayout(savingCard);

    // Income Card Labels
    incomeTitleLabel = new QLabel("Income");
    incomeTitleLabel->setStyleSheet("color: #718096; font-weight: 600; font-size: 14px;");
    incomeAmountLabel = new QLabel();
    incomeAmountLabel->setStyleSheet("color: #1a202c; font-weight: bold; font-size: 24px;");

    // Expense Card Labels
    expenseTitleLabel = new QLabel("Expense");
    expenseTitleLabel->setStyleSheet("color: #718096; font-weight: 600; font-size: 14px;");
    expenseAmountLabel = new QLabel("10000$");
    expenseAmountLabel->setStyleSheet("color: #1a202c; font-weight: bold; font-size: 24px;");

    // Saving Card Labels
    savingsTitleLabel = new QLabel("Savings");
    savingsTitleLabel->setStyleSheet("color: #718096; font-weight: 600; font-size: 14px;");
    savingsAmountLabel = new QLabel("20000$");
    savingsAmountLabel->setStyleSheet("color: #1a202c; font-weight: bold; font-size: 24px;");


    // Add Income Card Widgets
    incomeCardLayout->addWidget(incomeTitleLabel);
    incomeCardLayout->addStretch();
    // incomeCardLayout->addSpacing(5);
    incomeCardLayout->addWidget(incomeAmountLabel);
    incomeCardLayout->addStretch();

    // Add Expense Card Widgets
    expenseCardLayout->addWidget(expenseTitleLabel);
    expenseCardLayout->addStretch();
    expenseCardLayout->addWidget(expenseAmountLabel);

    // Add Income Card Widgets
    savingCardLayout->addWidget(savingsTitleLabel);
    savingCardLayout->addStretch();
    savingCardLayout->addWidget(savingsAmountLabel);


    // Adding Cards to the cardHLayout ptr
    cardHLayout->addWidget(debitCard,0,Qt::AlignLeft);
    cardHLayout->addSpacing(17);
    cardHLayout->addWidget(incomeCard,1,Qt::AlignLeft);
    cardHLayout->addWidget(expenseCard,2,Qt::AlignLeft);
    cardHLayout->addWidget(savingCard,3,Qt::AlignLeft);

    // Added the card in the Container layout
    containerLayout->addLayout(cardHLayout);
    containerLayout->addWidget(actionButtonsWidget);
    containerLayout->addStretch();


    // Added the header and content container widget
    mainLayout->addWidget(header);
    mainLayout->addWidget(contentContainer);
    mainLayout->addStretch();


    // Buttons Connection
    connect(logoutBtn, &QPushButton::clicked, [this](){
        emit logoutRequested();
    });
    connect(themeToggleBtn, &QPushButton::clicked,[this](){
        emit themeChangeRequested();
    });
    connect(depositBtn,&QPushButton::clicked,[this](){
        dialog = new TransactionDialog(DEPOSIT,m_session);
        dialog->setModal(true);
        dialog->show();

        connect(dialog,&TransactionDialog::updateBalance,[this](){
            updateBalance(m_session);
        });

        dialog->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(transferBtn,&QPushButton::clicked,[this](){
        dialog = new TransactionDialog(TRANSFER,m_session);
        dialog->setModal(true);
        dialog->show();

        connect(dialog,&TransactionDialog::updateBalance,[this](){
            updateBalance(m_session);
        });

        dialog->setAttribute(Qt::WA_DeleteOnClose);
    });
    connect(withdrawBtn,&QPushButton::clicked,[this](){
        dialog = new TransactionDialog(WITHDRAW,m_session);
        dialog->setModal(true);
        dialog->show();

        connect(dialog,&TransactionDialog::updateBalance,[this](){
            updateBalance(m_session);
        });

        dialog->setAttribute(Qt::WA_DeleteOnClose);
    });
}

void DashboardWindow::initializeDashboard(UserSessionHandler* session){
    this->m_session = session;
    userGreetFullNameLabel->setText("Welcome, " + session->getFullName());
    usernameLabel->setText(session->getUsername());
    userEmail->setText(session->getEmail());
    userMobileNO->setText(session->getMobileNo());
    incomeAmountLabel->setText("$" + QString::number(session->getIncome(),'f',2));
    // expenseAmountLabel->setText(QString::number(session->getExpense()));

    // 1. Initialize the locale (English format provides the commas you see in banking apps)
    QLocale locale(QLocale::English);
    // 2. Format the balance into a string with commas and 2 decimal places
    QString formattedBalance = locale.toString(session->getBalance(), 'f', 2);
    // 3. Inject the formatted string into the HTML
    userBalance->setText(QString(
                             "<span style='font-size: 13px; font-weight: 600; color: rgba(255, 255, 255, 0.5);'>Balance</span><br>"
                             "<span style='font-size: 20px; font-weight: bold; color: white;'>$%1</span>"
                             ).arg(formattedBalance));

    // 1. Format the Holder Label
    cardHolderLabel->setText(QString(
                                 "<span style='font-size: 10px; color: rgba(255, 255, 255, 0.5);'>CARD HOLDER</span><br>"
                                 "<span style='font-size: 14px; font-weight: bold; color: white;'>%1</span>"
                                 ).arg(session->getFullName().toUpper())); // toUpper() matches the "Banking" aesthetic

    // 2. Format the Expiry Label
    // Assuming you have a getExpiryDate() or similar in your session
    cardExpiryLabel->setText(QString(
                                 "<span style='font-size: 10px; color: rgba(255, 255, 255, 0.5);'>VALID THRU</span><br>"
                                 "<span style='font-size: 14px; font-weight: bold; color: white;'>%1</span>"
                                 ).arg("04/31")); // Replace with session->getExpiryDate() when your DB is ready

    cardNumber->setText("5123  **** **** 8892");
    cardNumber->setStyleSheet("font-weight: 600;font-size: 20px;font: 'roboto';");
}

void DashboardWindow::updateBalance(UserSessionHandler *session){
    double freshBalance = db.getBalance(session->getAccountID());
    session->setBalance(freshBalance); // Updates the session object internal value
    // 1. Initialize the locale (English format provides the commas you see in banking apps)
    QLocale locale(QLocale::English);
    // 2. Format the balance into a string with commas and 2 decimal places
    QString formattedBalance = locale.toString(session->getBalance(), 'f', 2);
    // 3. Inject the formatted string into the HTML
    userBalance->setText(QString(
                             "<span style='font-size: 13px; font-weight: 600; color: rgba(255, 255, 255, 0.5);'>Balance</span><br>"
                             "<span style='font-size: 20px; font-weight: bold; color: white;'>$%1</span>"
                             ).arg(formattedBalance));
    incomeAmountLabel->setText("$" + QString::number(db.getIncome(session->getAccountID()),'f',2));
}
