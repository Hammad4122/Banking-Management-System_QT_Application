#include "tpindialog.h"
#include <qboxlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qvalidator.h>
#include "basepage.h"
#include <QTimer>

TPinDialog::TPinDialog(QWidget *parent) : QDialog(parent) {
    this->setFixedSize(300, 180);
    this->setWindowTitle("Security Verification");

    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel("Enter your 4-digit TPIN", this);

    tpinStatusLabel = new QLabel("");
    tpinStatusLabel->setStyleSheet("font-weight: normal; font-size: 10px; color: #FF4D4D;");
    tpinStatusLabel->hide();

    tpinField = new QLineEdit(this);
    tpinField->setEchoMode(QLineEdit::Password);
    tpinField->setMaxLength(4);
    tpinField->setAlignment(Qt::AlignCenter);

    // Force numbers only
    tpinField->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{4}$"), this));

    confirmBtn = new QPushButton("Verify", this);
    confirmBtn->setCursor(Qt::PointingHandCursor);
    confirmBtn->setEnabled(false);
    confirmBtn->setStyleSheet("");


    connect (tpinField, &QLineEdit::textChanged,[this]{
        if (!tpinField->text().isEmpty() && 4 == tpinField->text().length()){
            confirmBtn->setEnabled(true);
        }
        else {
            confirmBtn->setEnabled(false);
        }
    });
    connect(confirmBtn, &QPushButton::clicked, this,&QDialog::accept);

    layout->addWidget(label);
    layout->addWidget(tpinField);
    layout->addWidget(tpinStatusLabel);
    layout->addWidget(confirmBtn);

    applyCurrentTheme(); // Pull from BasePage::isDarkMode for that Emerald/Blue look
}

void TPinDialog::applyCurrentTheme() {
    if (BasePage::getIsDarkMode()) {
        // --- DARK EMERALD THEME ---
        this->setStyleSheet(
            "QDialog { background-color: #0B0E11; border: 1px solid #23282E; }"
            "QLabel { color: #50C878; font-weight: bold; font-size: 14px; }"
            "QLineEdit { "
            "   background-color: #1C2229; color: white; border: 1px solid #2C343C; "
            "   border-radius: 8px; padding: 10px; font-size: 18px; font-weight: bold; "
            "}"
            "QLineEdit:focus { border: 1.5px solid #50C878; }"
            "QPushButton { "
            "   background-color: #49B870; color: #0E3A1A; border-radius: 8px; "
            "   font-weight: bold; padding: 10px; font-size: 14px; "
            "}"
            "QPushButton:hover { background-color: #45AF67; }"
            "QPushButton:disabled { "
            "   background-color: #1C2229; "  /* Dark gray/black to fade into the background */
            "   color: #555555; "             /* Dimmed text */
            "   border: 1px solid #2C343C; "  /* Subtle border to show it's still a button */
            "}"
            );
    }
    else {
        // --- LIGHT BLUE THEME ---
        this->setStyleSheet(
            "QDialog { background-color: #F5F7FA; border: 1px solid #E6E9F4; }"
            "QLabel { color: #273671; font-weight: bold; font-size: 14px; }"
            "QLineEdit { "
            "   background-color: white; color: black; border: 1px solid #E6E9F4; "
            "   border-radius: 8px; padding: 10px; font-size: 18px; font-weight: bold; "
            "}"
            "QLineEdit:focus { border: 1.5px solid #2D60FF; }"
            "QPushButton { "
            "   background-color: #2D60FF; color: white; border-radius: 8px; "
            "   font-weight: bold; padding: 10px; font-size: 14px; "
            "}"
            "QPushButton:hover { background-color: #1A4DDF; }"
            "QPushButton:disabled { "
            "   background-color: #E6E9F4; "  /* Light gray to show inactivity */
            "   color: #A0A0A0; "             /* Faded text */
            "   border: none; "
            "}"
            );
    }
}
