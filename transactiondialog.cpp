#include "transactiondialog.h"
#include <qboxlayout.h>
#include <qpushbutton.h>

TransactionDialog::TransactionDialog(TransactionType type, QWidget* parent ):QDialog(parent),m_type(type){
    this->setFixedSize(400,250);
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
    mainLayout->setSpacing(15);
    mainLayout->addWidget(dialogTitle);
    mainLayout->addWidget(amountFieldLabel);
    mainLayout->addWidget(amountInputField);
    mainLayout->addWidget(accountNoFieldLabel);
    mainLayout->addWidget(accountNoInputField);
    mainLayout->addWidget(actionBtn);
    mainLayout->addStretch();

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
