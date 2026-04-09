#include "dashboardwindow.h"
#include <qboxlayout.h>

DashboardWindow::DashboardWindow(QWidget *parent): BasePage(parent) {

    this->setObjectName("dashboardPage");

    // 2. Create the Layout and attach it to the holder
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 3. Create and add your widgets
    label = new QLabel("Hello Dashboard Window");
    layout->addWidget(label);

    this->setStyleSheet(
        "#dashboardPage { background-color: #FFFFFF;}"
        "QLabel {color: black;}"
        );

    // 4. Set the window properties
    setAttribute(Qt::WA_DeleteOnClose);
}
