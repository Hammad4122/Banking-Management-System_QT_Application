#ifndef BASEPAGE_H
#define BASEPAGE_H
#include <QWidget>
#include "database.h"

class BasePage: public QWidget
{
    Q_OBJECT
public:
    explicit BasePage(QWidget *parent = nullptr);
    ~BasePage();
protected:
    BankDB db;

    void paintEvent(QPaintEvent *event = nullptr) override;


};

#endif // BASEPAGE_H
