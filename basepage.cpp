#include "basepage.h"
#include <QStyleOption>
#include <QPainter>

// BasePage.cpp
BasePage::BasePage(QWidget *parent) : QWidget(parent) {
    if (!db.connectDB()) {
        qDebug() << "BasePage: Failed to connect to Database";
    }
}

BasePage::~BasePage() {
    db.disconnectDB();
}

void BasePage::paintEvent(QPaintEvent *event) {

        QStyleOption opt;
        opt.initFrom(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}
