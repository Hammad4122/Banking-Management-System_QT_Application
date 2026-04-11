#include "dashboardwindow.h"
#include <qboxlayout.h>
#include <QPainter>
#include <QPainterPath>

// Title Color: #343C6A

DashboardWindow::DashboardWindow(QWidget *parent): BasePage(parent) {

    this->setObjectName("dashboardPage");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);


    QWidget *header = new QWidget();
    header->setObjectName("dashHeader");
    header->setFixedSize(1200,65);

    QHBoxLayout *headerLayout = new QHBoxLayout(header);
    headerLayout->addSpacing(5);
    headerLayout->setContentsMargins(0,0,0,0);

    creditLogoLabel = new QLabel(this);
    QPixmap creditPixmap(":/resources/credit-card_blue.png"); // Path from your .qrc
    creditLogoLabel->setPixmap(creditPixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));

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

    // Header Layout
    headerLayout->addWidget(creditLogoLabel,0,Qt::AlignLeft);
    headerLayout->addWidget(dashTitleLabel,0,Qt::AlignLeft);
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

    mainLayout->addWidget(header);
    mainLayout->addStretch();

    // Buttons Connection
    connect(logoutBtn, &QPushButton::clicked, [this](){
        emit logoutRequested();
    });
    connect(themeToggleBtn, &QPushButton::clicked,[this](){
        emit themeChangeRequested();
    });

}
