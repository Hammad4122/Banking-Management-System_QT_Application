#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class LoginWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);

private slots:
    void handleLogin();
    void openSignup();

private:
    QLabel *titleLabel;
    QLabel *statusLabel;
    QLabel *logoLabel;
    QLabel *logoTitleLabel;
    QLineEdit *userField;
    QLineEdit *passField;
    QPushButton *loginBtn;
    QPushButton *signupLink;

};

#endif
