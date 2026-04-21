#include "transactiondialog.h"
#include <qboxlayout.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qstyleoption.h>
#include <qtimer.h>
#include "basepage.h"
#include "tpindialog.h"

TransactionDialog::TransactionDialog(TransactionType type,UserSessionHandler *session, QWidget* parent ):QDialog(parent),m_type(type),m_session(session){
    setupUI();
    if (m_type == TRANSFER){
        this->setFixedSize(400,360);
        dialogTitle->setText("Transfer Funds");
        actionBtn->setText("Transfer");
        accountNoFieldLabel->show();
        accountNoInputField->show();
    }
    else {
        this->setFixedSize(400,270);
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
    mainLayout->addWidget(amountStatusLabel);
    mainLayout->addWidget(accountNoFieldLabel);
    mainLayout->addWidget(accountNoInputField);
    mainLayout->addWidget(accountNoStatusLabel);
    mainLayout->addWidget(remarksFieldLabel);
    mainLayout->addWidget(remarks);
    mainLayout->addWidget(remarksStatusLabel);
    mainLayout->addWidget(actionBtn);
    mainLayout->addWidget(transactionStatusLabel);
    mainLayout->addStretch();

    applyCurrentTheme();

    // Btn connections
    connect(actionBtn,&QPushButton::clicked,[this](){
        handleInputs();
    });
    connect(amountInputField,&QLineEdit::textChanged,[this](){
        amountStatusLabel->hide();
        transactionStatusLabel->hide();
        amountInputField->setStyleSheet("");
    });
    connect(accountNoInputField,&QLineEdit::textChanged,[this](){
        accountNoStatusLabel->hide();
        transactionStatusLabel->hide();
        accountNoInputField->setStyleSheet("");
    });
    connect(remarks,&QLineEdit::textChanged,[this](){
        remarksStatusLabel->hide();
        transactionStatusLabel->hide();
        remarks->setStyleSheet("");
    });

};

void TransactionDialog::setupUI(){
    db = new BankDB();

    qDebug() <<"Transaction Dialog: " << db;
    // Labels Memory Allocation
    dialogTitle = new QLabel();
    amountFieldLabel = new QLabel("Enter Amount");
    accountNoFieldLabel = new QLabel("Enter Account Number");
    remarksFieldLabel = new QLabel ("Remarks");

    // Error or Warning Labels
    amountStatusLabel = new QLabel();
    accountNoStatusLabel = new QLabel();
    remarksStatusLabel = new QLabel();
    transactionStatusLabel = new QLabel();

    amountStatusLabel->hide();
    accountNoStatusLabel->hide();
    remarksStatusLabel->hide();
    transactionStatusLabel->hide();


    // Input Field Memory Allocation
    accountNoInputField = new QLineEdit();
    accountNoInputField->setPlaceholderText("e.g 1012");
    amountInputField = new QLineEdit();
    amountInputField->setPlaceholderText("0.00");
    remarks = new QLineEdit();
    remarks->setPlaceholderText("e.g installment payment");

    // Input Validator
    QDoubleValidator* amountValidator = new QDoubleValidator(0.0, 1000000.0, 2, this);
    amountValidator->setNotation(QDoubleValidator::StandardNotation);
    amountInputField->setValidator(amountValidator);

    // Limit to digits only, maximum 4 characters
    QRegularExpression regExp("^[0-9]{4}$");
    QRegularExpressionValidator* accountValidator = new QRegularExpressionValidator(regExp, this);
    accountNoInputField->setValidator(accountValidator);

    // Action Button Memory Allocation
    actionBtn = new QPushButton();
    actionBtn->setCursor(Qt::PointingHandCursor);
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
            "QPushButton:pressed {background-color: #348A4E;}"
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
            "QPushButton:pressed {background-color: #1845C9;}"
            );
    }

    amountStatusLabel->setStyleSheet("font-weight: normal; font-size: 10px; color: #FF4D4D;");
    accountNoStatusLabel->setStyleSheet("font-weight: normal; font-size: 10px; color: #FF4D4D;");
    remarksStatusLabel->setStyleSheet("font-weight: normal; font-size: 10px; color: #FF4D4D;");
    transactionStatusLabel->setStyleSheet("font-weight :normal; color: #FF4D4D;");
    dialogTitle->setStyleSheet("font-size: 18px; margin-bottom: 5px;");
}

// In transactiondialog.cpp
void TransactionDialog::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TransactionDialog::handleInputs() {
    QString amountStr = amountInputField->text();
    QString recieverAccountNo = accountNoInputField->text();
    QString remarksText = remarks->text();

    // 1. Validation: Amount shouldn't be empty
    if (amountStr.isEmpty()) {
        amountStatusLabel->setText("Please enter an amount!");
        amountStatusLabel->show();
        amountInputField->setStyleSheet("border: 1.5px solid #FF4D4D;");
        return;
    }

    // // 2. Convert string to double safely
    // bool ok;
    // double amountValue = amountStr.toDouble(&ok);
    // if (!ok || amountValue <= 0) {
    //     amountStatusLabel->clear();
    //     amountStatusLabel->setText("Invalid amount!");
    //     amountStatusLabel->show();

    //     return;
    // }

    // 3. Validation: Account Number required for Transfers
    if (m_type == TRANSFER && recieverAccountNo.isEmpty()) {
        accountNoStatusLabel->setText("Receiver ID required!");
        accountNoStatusLabel->show();

        accountNoInputField->setStyleSheet("border: 1.5px solid #FF4D4D;");
        return;
    }

    // 4. Remarks
    if (remarksText.isEmpty()){
        remarksStatusLabel->setText("Write some remarks.");
        remarksStatusLabel->show();
        remarks->setStyleSheet("border: 1.5px solid #FF4D4D;");
        return;
    }

    if (m_type == TRANSFER){
        if (!db->accountExist(recieverAccountNo)){
            accountNoStatusLabel->setText("Account does not exist");
            transactionStatusLabel->setText("Transaction Failed");

            accountNoStatusLabel->show();
            transactionStatusLabel->show();

            accountNoInputField->setStyleSheet("border: 1.5px solid #FF4D4D;");
            return;
        }
    }

    if (m_type == TRANSFER){
        if (recieverAccountNo == QString::number(m_session->getAccountID()) ) {
            transactionStatusLabel->setText("Transaction cannot be made to your self");
            transactionStatusLabel->show();

            accountNoInputField->setStyleSheet("border: 1.5px solid #FF4D4D;");
            return;
        }
    }

    // DataType Conversions
    bool isTransactionCompleted = false;
    double doubleAmount = amountStr.toDouble();
    int intRecieverAccountNo = recieverAccountNo.toInt();
    double currentBalance = db->getBalance(m_session->getAccountID());

    TPinDialog tpinPopup(this);
    if (tpinPopup.exec() == QDialog::Accepted) {

        QString rawPin = tpinPopup.getEnteredTPin();


        // Use the static ID from BasePage!
        if (db->authTransaction(m_session->getUserId(), rawPin)){

            if (m_type == DEPOSIT){

                isTransactionCompleted = db->executeDeposit(m_session->getAccountID(),doubleAmount,remarksText);
                handleTransaction(isTransactionCompleted);
            }
            else if (m_type == TRANSFER){
                if (doubleAmount > currentBalance){
                    transactionStatusLabel->setText("Not Enough Balance.");
                    transactionStatusLabel->show();
                }
                else {
                    isTransactionCompleted = db->transfer(m_session->getAccountID(),intRecieverAccountNo,doubleAmount,remarksText);
                    handleTransaction(isTransactionCompleted);
                }
            }
            else if (m_type == WITHDRAW){
                if (doubleAmount > currentBalance){

                    transactionStatusLabel->setText("Not Enough Balance.");
                    transactionStatusLabel->show();
                }
                else {

                    isTransactionCompleted = db->executeWithdraw(m_session->getAccountID(),doubleAmount,remarksText);
                    handleTransaction(isTransactionCompleted);
                }
            }
        }
        else {
            // Handle wrong TPIN
            transactionStatusLabel->setText("Transaction Failed. Wrong TPIN");
            transactionStatusLabel->show();
        }
    }
}

void TransactionDialog::handleTransaction(bool isTransactionCompleted){
    if (isTransactionCompleted){
        startSuccessVideo();
    }
    else {
        transactionStatusLabel->setText("Transaction could not be made. Try again.");
        transactionStatusLabel->show();
    }
}

void TransactionDialog::startSuccessVideo() {
    // 1. Hide the input elements to make room for the video
    dialogTitle->hide();
    amountFieldLabel->hide();
    accountNoFieldLabel->hide();
    remarksFieldLabel->hide();
    accountNoInputField->hide();
    amountInputField->hide();
    actionBtn->hide();
    remarks->hide();
    amountStatusLabel->hide();
    accountNoStatusLabel->hide();
    remarksStatusLabel->hide();
    transactionStatusLabel->hide();

    // 2. Setup the animation label
    animationLabel = new QLabel(this);
    animationLabel->setAlignment(Qt::AlignCenter);

    // 3. Load the video (GIF)
    successMovie = new QMovie(":/resources/Success_Check.gif");

    // Set the label to the size of the movie
    animationLabel->setMovie(successMovie);
    layout()->addWidget(animationLabel); // Add to your existing layout

    // 4. Play the video
    successMovie->start();
    emit updateBalance();

    // 5. Close the dialog automatically after the video finishes
    QTimer::singleShot(2100, this, &QDialog::accept);

}
