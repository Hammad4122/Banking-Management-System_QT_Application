#include "basepage.h"
#include <QStyleOption>
#include <QPainter>

void BasePage::paintEvent(QPaintEvent *event) {

        QStyleOption opt;
        opt.initFrom(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}
