#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>
#include <QPoint>
#include <QTimer>
#include <QEventLoop>
#include <memory>

namespace RBT {

class RbtNode;
using NodePtr = std::shared_ptr<RbtNode>;

class RbtNode {
public:
    RbtNode();
    ~RbtNode();
    void updateThisNode(QPoint new_pos);    // 更新节点坐标
    void delay(int duration);               // 延时

public:
    static inline int max_x {1};            // 记录最大横坐标 
    static inline int min_x {1};            // 记录最小横坐标
    static inline int max_h {1};            // 记录最大高度
    static inline int R {50};               // 定义基本单位，便于计算位置、大小
    static inline QGraphicsScene* scene;    // 需要存储画布便于更新节点

    // rbt树基础数据
    int color;
    int key {0};
    int cnt {0};
    int height {0};
    NodePtr lchild {nullptr};
    NodePtr rchild {nullptr};
    NodePtr parent {nullptr};
    QPoint pos {0, 0};

private:
    // 绘图所需组件
    QGraphicsRectItem* rectItem {nullptr};
    QGraphicsSimpleTextItem* textItem {nullptr};
    QGraphicsLineItem* lLine {nullptr};
    QGraphicsLineItem* rLine {nullptr};
};

inline NodePtr root;
inline NodePtr nil;
inline QTimer timer;
inline QEventLoop* loop;
static const int RED = 1, BLACK = 2;

void sleep_for(int ms);
NodePtr get_node(int key);
void pushup(NodePtr node);              // 递归向上归时维护树高
void left_rotate(NodePtr& node);        // 左旋(以引用的方式传值，便于修改对应关系)
void right_rotate(NodePtr& node);       // 右旋
void check_red(NodePtr node);           // 检查插入操作是否破坏红色节点不相邻性质
void check_black(NodePtr node);         // 检查删除操作是否出现双黑节点需要调整
void release_tree(NodePtr root);        // 递归清空红黑树
void init_rbt(NodePtr& root);           // 初始化rbt树，随机插入数据
void update_by_dfs(NodePtr& node, QPoint pos = {0, 0});         // dfs更新所有节点位置
void add(int key, NodePtr& node, NodePtr parent = nil);         // 插入数据
void remove(int key, NodePtr& node);    // 删除数据

/*
void search(int key, NodePtr& node);    // 查询数据(后续考虑加锁防止错误操作导致的资源竞争)
*/

}
