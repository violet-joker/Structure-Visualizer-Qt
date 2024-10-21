#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "avl.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 添加画布场景
    QGraphicsScene* scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 650, 400);
    ui->graphicsView->setScene(scene);
    AVL::AvlNode::scene = scene;
    AVL::loop = new QEventLoop();

    // 设置addBtn的槽函数，点击后匿名函数捕获avl根节点，以及需要添加的key值，调用add函数添加节点
    connect(ui->addBtn, &QPushButton::clicked, this, [=, &root = AVL::root] {
        int key = ui->inputKey->value();
        AVL::add(key, root);
        AVL::update_by_dfs(root);
        // 调整画布大小
        int max_w = root->max_x - root->min_x + 300;
        int max_h = root->max_h + 100;
        if (max_h > scene->sceneRect().height() || max_w > scene->sceneRect().width())
            scene->setSceneRect(0, 0, max_w, max_h), scene->update();
        scene->update();
    });
    // 设置init_avl槽函数
    connect(ui->initBtn, &QPushButton::clicked, this, [=, &root = AVL::root] {
        AVL::init_avl(root);
        AVL::update_by_dfs(root);
        int max_w = root->max_x - root->min_x + 300;
        int max_h = root->max_h + 100;
        scene->setSceneRect(0, 0, max_w, max_h), scene->update();
        scene->update();
    });
    // 设置删除操作槽函数
    connect(ui->delBtn, &QPushButton::clicked, this, [=, &root = AVL::root] {
        if (root == nullptr) return;
        int key = ui->inputKey->value();
        remove(key, root);
//        root->max_h = root->max_x = root->min_x = 0;
        AVL::update_by_dfs(root);
        // 删除操作只会导致树越来越小，越来越紧凑，考虑到变化过程中最好主体位置不变，这里放弃更新画布
//        int max_w = root->max_x - root->min_x + 300;
//        int max_h = root->max_h + 100;
//        scene->setSceneRect(0, 0, max_w, max_h), scene->update();
        scene->update();
    });
    // 设置查找操作槽函数
    connect(ui->searchBtn, &QPushButton::clicked, this, [=, &root = AVL::root] {
        int key = ui->inputKey->value();
        AVL::search(key, root);
    });
    // 设置延时机制timer.start开始记时，同时loop进入事件循环;timer发出超时信号后loop退出事件循环
    connect(&AVL::timer, &QTimer::timeout, AVL::loop, &QEventLoop::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}
