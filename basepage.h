#ifndef BASEPAGE_H
#define BASEPAGE_H
#include <QWidget>


class BasePage: public QWidget
{
    Q_OBJECT
public:
    explicit BasePage(QWidget *parent = nullptr): QWidget(parent) {};

protected:
    void paintEvent(QPaintEvent *event = nullptr) override;
};

#endif // BASEPAGE_H
