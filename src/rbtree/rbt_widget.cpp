#include "rbt_widget.h"
#include "ui_rbt_widget.h"
#include "rbt.h"
#include <QDebug>

RbtWidget::RbtWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RbtWidget)
{
    ui->setupUi(this); 
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    RBT::RbtNode::scene = scene;
    RBT::nil = std::make_shared<RBT::RbtNode>();
    RBT::root = RBT::nil;

    // 初始化槽函数
    connect(ui->initBtn, &QPushButton::clicked, this, [=] {
        RBT::init_rbt(RBT::root);
        RBT::update_by_dfs(RBT::root);
        int max_w = RBT::root->max_x - RBT::root->min_x + 300;
        int max_h = RBT::root->max_h + 100;
        scene->setSceneRect(0, 0, max_w, max_h);
        scene->update();
    });
    // add添加数据槽函数 
    connect(ui->addBtn, &QPushButton::clicked, this, [=] {
        RBT::add(ui->inputKey->value(), RBT::root);
        RBT::update_by_dfs(RBT::root);
        // 调整画布大小
        int max_w = RBT::RbtNode::max_x - RBT::RbtNode::min_x + 300;
        int max_h = RBT::RbtNode::max_h + 100;
        scene->setSceneRect(0, 0, max_w, max_h);
        scene->update();
    });
    // remove删除数据槽函数
    connect(ui->delBtn, &QPushButton::clicked, this, [=] {
        RBT::remove(ui->inputKey->value(), RBT::root);
        // 重置nil内部指针;如果删除的是root节点，可能出现删除后nil内部指针未释放的情况
        RBT::nil->parent = RBT::nil->lchild = RBT::nil->rchild = nullptr;
        RBT::update_by_dfs(RBT::root);
        // 调整画布大小
        int max_w = RBT::RbtNode::max_x - RBT::RbtNode::min_x + 300;
        int max_h = RBT::RbtNode::max_h + 100;
        scene->setSceneRect(0, 0, max_w, max_h);
        scene->update();
    });
    // 清除数据
    connect(ui->clearBtn, &QPushButton::clicked, this, [=] {
        RBT::release_tree(RBT::root);
        RBT::root = RBT::nil;
        scene->update();
    });
}

RbtWidget::~RbtWidget() {
    delete ui;
}
