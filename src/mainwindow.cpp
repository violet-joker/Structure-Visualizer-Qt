#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "avl/avl_widget.h"
#include "rbtree/rbt_widget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setStyleSheet("background-color: silver; ");
    ui->stackedWidget->addWidget(new AvlWidget(ui->stackedWidget));
    ui->stackedWidget->addWidget(new RbtWidget(ui->stackedWidget));
    connect(ui->avlBtn, &QPushButton::clicked, this, [=] { ui->stackedWidget->setCurrentIndex(0); });
    connect(ui->rbtBtn, &QPushButton::clicked, this, [=] { ui->stackedWidget->setCurrentIndex(1); });
}

MainWindow::~MainWindow() {
    delete ui;
}
