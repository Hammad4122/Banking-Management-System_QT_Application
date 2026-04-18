#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include <qdialog.h>
#include <qlabel.h>
#include <qlineedit.h>

enum TransactionType {DEPOSIT,TRANSFER,WITHDRAW};
class TransactionDialog: public QDialog
{
    Q_OBJECT
public:
    explicit TransactionDialog(TransactionType,QWidget* parent = nullptr);
private:
    TransactionType m_type;
    QLabel* dialogTitle;
    QLabel* amountFieldLabel;
    QLabel* accountNoFieldLabel;
    QLineEdit* accountNoInputField;
    QLineEdit* amountInputField;
    QPushButton* actionBtn;

    void setupUI();

};

#endif // TRANSACTIONDIALOG_H
