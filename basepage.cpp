#include "basepage.h"
#include <QStyleOption>
#include <QPainter>

// BasePage.cpp
#include "basepage.h"

// Initialize the static bool
bool BasePage::isDarkMode = false;

// Initialize the Light Blue Theme
const QString BasePage::lightBlueTheme = R"(
    /* Main Backgrounds */
    #loginPage, #signupPage {
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

    #logoLabel {
        border-image: url(:/resources/bank_pic.png);" // Blue version
        min-width: 40px; min-height: 40px;
        max-width: 40px; max-height: 40px;
    }
)";

// Initialize the Black & Emerald Theme
const QString BasePage::darkEmeraldTheme = R"(
    /* Main Backgrounds */
    #loginPage, #signupPage {
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

)";

BasePage::BasePage(QWidget *parent) : QWidget(parent) {
    if (!db.connectDB()) {
        qDebug() << "BasePage: Failed to connect to Database";
    }
    this->setStyleSheet(lightBlueTheme);
    // themeToggleBtn = new QPushButton("🌙",this);
    // themeToggleBtn->setFixedSize(40,40);
    // themeToggleBtn->move(1100,75);


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
    qDebug() << "Hello";
    if (isDarkMode){
        this->setStyleSheet(darkEmeraldTheme);
    }
    else {
        this->setStyleSheet(lightBlueTheme);
    }
}

void BasePage::updateToggleIcon(){
    if (themeToggleBtn){
        themeToggleBtn->setText(isDarkMode ? "☀️" : "🌙");
    }
    // 2. MANUALLY swap the icon pixmap
    if (logoLabel) {
        QString iconPath = isDarkMode ? ":/resources/bank_pic_green.png"
                                      : ":/resources/bank_pic.png";

        QPixmap pix(iconPath);
        if (!pix.isNull()) {
            logoLabel->setPixmap(pix.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            qDebug() << "Failed to load icon from:" << iconPath;
        }
    }
}

void BasePage::toggleGlobalTheme(){
    isDarkMode = !isDarkMode;
}
