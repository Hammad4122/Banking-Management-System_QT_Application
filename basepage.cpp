#include "basepage.h"
#include <QStyleOption>
#include <QPainter>
#include "basepage.h"

// BasePage.cpp

// Initialized the static bool
bool BasePage::isDarkMode = false;

// The Light Blue Theme
const QString BasePage::lightBlueTheme = R"(
    /* Main Backgrounds */
    #loginPage, #signupPage, #dashboardPage {
        background-color: #F5F7FA;
    }

    /* Central Cards */
    #loginCard, #signupCard {
        background-color: #FFFFFF;
        border-radius: 20px;
    }

    /* Titles */
    #loginTitle, #signupLabel {
        font-size: 26px;
        font-weight: bold;
        color: #273671;
    }
    /* Dashboard */

    /* Dashboard Header */
    #dashHeader {background-color: #FFFFFF;}

    /* Dashboard Labels */
    #dashTitleLabel {font-size: 16px; color: #343C6A;}

    /* Styling for the circular settings button */
    #settingBtn{
        background-color: #F5F7FA;
        border: none;
        border-radius: 17px;       /* Half of the 40px width/height to make it a circle */

        /* Path to icon in resources */
        qproperty-icon: url(":/resources/setting_icon.png");
        qproperty-iconSize: 22px 22px; /* Size of the gear inside the circle */
    }
    #notificationBtn{
        background-color: #F5F7FA;
        border: none;
        border-radius: 17px;       /* Half of the 40px width/height to make it a circle */

        /* Path to icon in resources */
        qproperty-icon: url(":/resources/notification.png");
        qproperty-iconSize: 22px 22px; /* Size of the notification icon inside the circle */
    }
    /* Add a hover effect for a professional feel */
    #settingBtn:hover ,#notificationBtn:hover {
        background-color: #F2F2F2;
    }
    #settingBtn:pressed, #notificationBtn:pressed {
        background-color: #C2C2C2;
        margin-top: 0px;
    }

    /* Login Button */
    #logoutBtn {
        background-color: #2D60FF;
        color: white;
        border-radius: 8px;
        font-weight: bold;
        font-size: 13px;
        padding: 2px;
    }

    #logoutBtn:pressed {background-color: #1a3ddf; margin-top: 0px;}

    /* Global Label Styles */
    QLabel {
        color: #273671;
        font-weight: bold;
        font-size: 13px;
    }

    /* Status/Error Labels (Specific & Generic) */
    #statusLabel, #nameStatusLabel, #usernameStatusLabel,
    #emailStatusLabel, #mobileNoStatusLabel {
        font-size: 13px;
        font-weight: normal;
        color: #FF4D4D; /* Red for errors */
    }

    /* Input Fields */
    QLineEdit {
        color: black;
        border: 1px solid #E6E9F4;
        border-radius: 8px;
        padding-left: 10px;
        background: #FFFFFF;
        height: 35px;
    }

    QLineEdit:focus {
        border: 1.5px solid #2D60FF;
    }

    /* Primary Action Buttons */
    QPushButton {
        background-color: #2D60FF;
        color: white;
        border-radius: 8px;
        font-weight: bold;
        font-size: 15px;
        padding: 8px;
    }

    QPushButton:hover {
        background-color: #1A4DDF;
    }

    QPushButton:pressed {
        background-color: #1a3ddf;
        margin-top: 2px;
    }

    /* Navigation Link Buttons */
    #linkBtn, #loginLinkBtn {
        background: transparent;
        color: #2D60FF;
        border: none;
        font-size: 13px;
        font-weight: normal;
    }

    #linkBtn:hover, #loginLinkBtn:hover {
        text-decoration: underline;
    }

    #logoTitleLabel {font-size: 14px; color: #333; line-height: 1.2;}

    #userGreetingLabel {font-size: 18px;}

)";

// The Black & Emerald Theme
const QString BasePage::darkEmeraldTheme = R"(
    /* Main Backgrounds */
    #loginPage, #signupPage, #dashboardPage {
        background-color: #0B0E11;
    }

    /* Central Cards */
    #loginCard, #signupCard {
        background-color: #161A1E;
        border: 1px solid #23282E;
        border-radius: 20px;
    }

    /* Titles */
    #loginTitle, #signupLabel {
        font-size: 26px;
        font-weight: bold;
        color: #50C878;
    }

    /* Global Label Styles */
    QLabel {
        color: #E0E0E0;
        font-weight: bold;
        font-size: 13px;
    }

    /* Status/Error Labels */
    #statusLabel, #nameStatusLabel, #usernameStatusLabel,
    #emailStatusLabel, #mobileNoStatusLabel {
        font-size: 12px;
        font-weight: normal;
        color: #FF5555;
    }

    /* Input Fields */
    QLineEdit {
        color: #FFFFFF;
        border: 1px solid #2C343C;
        border-radius: 8px;
        padding-left: 10px;
        background: #1C2229;
        height: 35px;
    }

    QLineEdit:focus {
        border: 1.5px solid #50C878;
    }

    /* Primary Action Buttons */
    QPushButton {
        background-color: #50C878;
        color: #0B0E11;
        border-radius: 8px;
        font-weight: bold;
        font-size: 15px;
        padding: 8px;
    }

    QPushButton:hover {
        background-color: #45AF67;
    }

    QPushButton:pressed {
        background-color: #3B9658;
        margin-top: 2px;
    }

    /* Navigation Link Buttons */
    #linkBtn, #loginLinkBtn {
        background: transparent;
        color: #50C878;
        border: none;
        font-size: 13px;
        font-weight: normal;
    }

    #linkBtn:hover, #loginLinkBtn:hover {
        text-decoration: underline;
        color: #70DB93;
    }
    #logoTitleLabel {font-size: 14px; color: #caccca; line-height: 1.2;}

    #dashHeader {background-color: #161A1E;}


)";

BasePage::BasePage(QWidget *parent) : QWidget(parent) {
    if (!db.connectDB()) {
        qDebug() << "BasePage: Failed to connect to Database";
    }

    this->setStyleSheet(lightBlueTheme);    // Default Theme

}

BasePage::~BasePage() {
    db.disconnectDB();
}

void BasePage::paintEvent(QPaintEvent *event) {

        QStyleOption opt;
        opt.initFrom(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}

void BasePage::applyCurrentTheme(){

    if (isDarkMode){
        this->setStyleSheet(darkEmeraldTheme); // Apply the Dark Emerald Theme
    }
    else {
        this->setStyleSheet(lightBlueTheme);   // Apply the Light Blue Theme
    }
    updateIcons();
}

void BasePage::updateIcons(){
    // 1. Swap Toggle Button Icon
    if (themeToggleBtn){
        themeToggleBtn->setText(isDarkMode ? "☀️" : "🌙"); // On: ☀️ Off: 🌙
    }
    // 2. MANUALLY swap the icon pixmap
    if (bankLogoLabel) {
        QString bankIconPath = isDarkMode ? ":/resources/bank_pic_green.png"
                                          : ":/resources/bank_pic.png";

        QPixmap bankIconPix(bankIconPath);
        if (!bankIconPix.isNull()) {
            bankLogoLabel->setPixmap(bankIconPix.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            qDebug() << "Failed to load icon from:" << bankIconPath;
        }
    }

    if (creditLogoLabel){
        QString creditIconPath = isDarkMode ? ":/resources/credit-card_green.png"
                                            : ":/resources/credit-card_blue.png";
        QPixmap creditIconPix(creditIconPath);
        if (!creditIconPix.isNull()) {
            creditLogoLabel->setPixmap(creditIconPix.scaled(40,40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            qDebug() << "Failed to load icon from:" << creditIconPath;
        }
    }
}

void BasePage::toggleGlobalTheme(){
    isDarkMode = !isDarkMode;
}
