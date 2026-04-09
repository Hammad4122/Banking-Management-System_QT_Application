#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include "basepage.h"
#include <qmainwindow.h>
#include <QLabel>
class DashboardWindow: public BasePage
{
    Q_OBJECT
public:
    explicit DashboardWindow(QWidget *parent = nullptr);
private slots:
private:
    QLabel *label;
};

#endif // DASHBOARD_H
