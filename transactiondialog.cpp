#include "transactiondialog.h"
#include <qboxlayout.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qstyleoption.h>
#include "basepage.h"

TransactionDialog::TransactionDialog(TransactionType type, QWidget* parent ):QDialog(parent),m_type(type){
    this->setFixedSize(400,270);
    setupUI();
    if (m_type == TRANSFER){
        dialogTitle->setText("Transfer Funds");
        actionBtn->setText("Transfer");
        accountNoFieldLabel->show();
        accountNoInputField->show();
    }
    else {
        accountNoFieldLabel->hide();
        accountNoInputField->hide();
        dialogTitle->setText(m_type == DEPOSIT ? "Deposit Funds":"Withdraw Funds");
        actionBtn->setText(m_type == DEPOSIT ? "Deposit":"Withdraw");
    }


    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(dialogTitle);
    mainLayout->addWidget(amountFieldLabel);
    mainLayout->addWidget(amountInputField);
    mainLayout->addWidget(accountNoFieldLabel);
    mainLayout->addWidget(accountNoInputField);
    mainLayout->addWidget(actionBtn);
    mainLayout->addStretch();

    applyCurrentTheme();

};

void TransactionDialog::setupUI(){
    // Labels Memory Allocation
    dialogTitle = new QLabel();
    amountFieldLabel = new QLabel("Enter Amount");
    accountNoFieldLabel = new QLabel("Enter Account Number");

    // Input Field Memory Allocation
    accountNoInputField = new QLineEdit();
    accountNoInputField->setPlaceholderText("e.g 1012");
    amountInputField = new QLineEdit();
    amountInputField->setPlaceholderText("0.00");

    // Action Button Memory Allocation
    actionBtn = new QPushButton();
};

void TransactionDialog::applyCurrentTheme(){
    if (BasePage::getIsDarkMode()){
        // --- DARK EMERALD THEME ---
        this->setStyleSheet(
            "QDialog { background-color: #0B0E11; }"
            "QLabel { color: #E0E0E0; font-weight: bold; font-size: 13px; }"
            "QLineEdit { "
            "   background-color: #1C2229; color: white; border: 1px solid #2C343C; "
            "   border-radius: 8px; padding: 8px; "
            "}"
            "QLineEdit:focus { border: 1.5px solid #50C878; }"
            "QPushButton { "
            "   background-color: #49B870; color: #0E3A1A; border-radius: 8px; "
            "   font-weight: bold; padding: 10px; font-size: 14px; "
            "}"
            "QPushButton:hover { background-color: #45AF67; }"
            );
    }
    else {
        // --- LIGHT BLUE THEME ---
        this->setStyleSheet(
            "QDialog { background-color: #F5F7FA; }"
            "QLabel { color: #273671; font-weight: bold; font-size: 13px; }"
            "QLineEdit { "
            "   background-color: white; color: black; border: 1px solid #E6E9F4; "
            "   border-radius: 8px; padding: 8px; "
            "}"
            "QLineEdit:focus { border: 1.5px solid #2D60FF; }"
            "QPushButton { "
            "   background-color: #2D60FF; color: white; border-radius: 8px; "
            "   font-weight: bold; padding: 10px; font-size: 14px; "
            "}"
            "QPushButton:hover { background-color: #1A4DDF; }"
            );
    }

    dialogTitle->setStyleSheet("font-size: 18px; margin-bottom: 5px;");
}

// In transactiondialog.cpp
void TransactionDialog::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
