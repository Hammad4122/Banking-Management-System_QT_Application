#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "basepage.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include "usersessionhandler.h"

/**
 * LoginWindow
 *
 * Provides:
 *  - Username / Password fields
 *  - A role selector ComboBox (User | Admin) below the password field
 *  - Theme toggle button
 *
 * Emits loginSuccessful(session) for normal users.
 * Emits adminLoginSuccessful()    for the hardcoded admin account.
 */
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
    void adminLoginSuccessful();
    void signupRequested();
    void themeChangeRequested();

private:
    QLabel      *titleLabel;
    QLabel      *statusLabel;
    QLabel      *logoTitleLabel;
    QLineEdit   *userField;
    QLineEdit   *passField;
    QComboBox   *roleCombo;       // ← NEW: User / Admin selector
    QPushButton *loginBtn;
    QPushButton *signupLink;
};

#endif // LOGINWINDOW_H
