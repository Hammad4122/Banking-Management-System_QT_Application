#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "basepage.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class LoginWindow : public BasePage
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);

private slots:
    void handleLogin();
    void openSignup();
signals:
    void loginSuccessful();
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

    void resetForm();

};

#endif
