#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include "database.h"
#include "usersessionhandler.h"
#include <qdialog.h>
#include <qlabel.h>
#include <qlineedit.h>

enum TransactionType {DEPOSIT,TRANSFER,WITHDRAW};
class TransactionDialog: public QDialog
{
    Q_OBJECT
public:
    explicit TransactionDialog(TransactionType, UserSessionHandler*, QWidget* parent = nullptr);
private:
    UserSessionHandler *m_session;
    TransactionType m_type;
    QLabel* dialogTitle;
    QLabel* amountFieldLabel;
    QLabel* accountNoFieldLabel;
    QLabel* remarksFieldLabel;
    QLineEdit* accountNoInputField;
    QLineEdit* amountInputField;
    QPushButton* actionBtn;
    QLineEdit* remarks;

    // Error or Warnings Labels
    QLabel* amountStatusLabel;
    QLabel* accountNoStatusLabel;
    QLabel* remarksStatusLabel;
    QLabel* transactionStatusLabel;

    void setupUI();
    void applyCurrentTheme();
    void paintEvent(QPaintEvent*);
    void handleInputs();

    QLabel* animationLabel;
    QMovie* successMovie;
    void startSuccessVideo();

    void handleTransaction(bool);

    BankDB *db;

signals:
    void updateBalance();

};

#endif // TRANSACTIONDIALOG_H
