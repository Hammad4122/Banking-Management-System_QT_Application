#ifndef TPINDIALOG_H
#define TPINDIALOG_H

#include <qdialog.h>
#include <QLineEdit>
#include <qlabel.h>
#include <QMovie>

class TPinDialog : public QDialog {
    Q_OBJECT
public:
    explicit TPinDialog(QWidget *parent = nullptr);
    QString getEnteredTPin() const { return tpinField->text(); }

private:
    QLineEdit *tpinField;
    QPushButton *confirmBtn;
    QLabel *tpinStatusLabel;
    void applyCurrentTheme();

};

#endif // TPINDIALOG_H
