#ifndef BASEPAGE_H
#define BASEPAGE_H
#include <QWidget>
#include <qlabel.h>
#include <qpushbutton.h>
#include "database.h"

class BasePage: public QWidget
{
    Q_OBJECT
public:
    explicit BasePage(QWidget *parent = nullptr);
    ~BasePage();

    void static toggleGlobalTheme();
    void applyCurrentTheme();
    void updateToggleIcon();
protected:
    BankDB db;
    // Static strings so they are shared by all child classes
    static const QString lightBlueTheme;
    static const QString darkEmeraldTheme;
    void paintEvent(QPaintEvent *event = nullptr) override;


    QPushButton* themeToggleBtn;
    static bool isDarkMode;

    QLabel* logoLabel = nullptr;
};

#endif // BASEPAGE_H
