#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include "basepage.h"
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include "database.h"

class SignupWindow: public BasePage
{
    Q_OBJECT
public:
    explicit SignupWindow(QWidget *parent = nullptr);
private slots:
    void handleSignup();
signals:
    void loginRequested();
private:
    QLabel *logoLabel;
    QLabel *logoTitleLabel;
    QLabel *signupTitle;
    QLineEdit *firstNameField;
    QLineEdit *lastNameField;
    QLineEdit *userNameField;
    QLineEdit *emailField;
    QLineEdit *mobileNoField;
    QLineEdit *passField;
    QLineEdit *passConfirmField;
    QPushButton *signupBtn;
    QPushButton *loginLinkBtn;
    QLabel *statusLabel;
    QLabel *nameStatusLabel;
    QLabel *usernameStatusLabel;
    QLabel *emailStatusLabel;
    QLabel *mobileNoStatusLabel;

    void resetForm();
};

#endif // SIGNUPWINDOW_H
