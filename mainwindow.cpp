#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centeral = new QWidget(this);
    setCentralWidget(centeral);

    EnableButton = new QPushButton("Enable Input",this);
    DisableButton = new QPushButton("Disable Input",this);
    input = new QLineEdit(this);

    input->setEnabled(false);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(EnableButton);
    buttonsLayout->addWidget(DisableButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(centeral);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(input);

    QObject::connect(EnableButton,&QPushButton::clicked,[this](){
        input->setEnabled(true);
    });
    QObject::connect(DisableButton,&QPushButton::clicked,[this](){
        input->setEnabled(false);
    });

}

MainWindow::~MainWindow(){}
