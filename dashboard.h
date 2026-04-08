#ifndef DASHBOARD_H
#define DASHBOARD_H
#include <QPushButton>
#include <QWidget>

class Dashboard: public QWidget{
public:
    Dashboard();
private:
    QPushButton *dashboard;
    QPushButton *transactions;
    QPushButton *accounts;
};

#endif // DASHBOARD_H
