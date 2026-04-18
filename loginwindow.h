#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "basepage.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "usersessionhandler.h"

class LoginWindow : public BasePage
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);
    void resetForm();

private slots:
    void handleLogin();
    void openSignup();
signals:
    void loginSuccessful(UserSessionHandler* session);
    void signupRequested();
    void themeChangeRequested();
private:
    QLabel *titleLabel;
    QLabel *statusLabel;
    QLabel *logoTitleLabel;
    QLineEdit *userField;
    QLineEdit *passField;
    QPushButton *loginBtn;
    QPushButton *signupLink;


};

#endif
