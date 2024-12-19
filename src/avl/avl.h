#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>
#include <QPoint>
#include <QTimer>
#include <QEventLoop>
#include <memory>

namespace AVL {
class AvlNode
{
public:
    AvlNode();
    ~AvlNode();
    void updateThisNode(QPoint new_pos);    // 更新节点坐标
    void delay(int duration);               // 延时

public:
    static inline int max_x {1};            // 记录最大横坐标 
    static inline int min_x {1};            // 记录最小横坐标
    static inline int max_h {1};            // 记录最大高度
    static inline int R {50};               // 定义基本单位，便于计算位置、大小
    static inline QGraphicsScene* scene;    // 需要存储画布便于更新节点

    // avl树基础数据
    int key {0};
    int cnt {0};
    int height {0};
    std::shared_ptr<AvlNode> lchild {nullptr};
    std::shared_ptr<AvlNode> rchild {nullptr};
    QPoint pos {0, 0};

private:
    // 绘图所需组件
    QGraphicsRectItem* rectItem {nullptr};
    QGraphicsSimpleTextItem* textItem {nullptr};
    QGraphicsLineItem* lLine {nullptr};
    QGraphicsLineItem* rLine {nullptr};
};

using NodePtr = std::shared_ptr<AvlNode>;
inline NodePtr root;
inline QTimer timer;
inline QEventLoop* loop;

void sleep_for(int ms);

NodePtr get_node(int key);
void pushup(NodePtr node);              // 递归向上归时维护树高
void rotate_left(NodePtr& node);        // 左旋(以引用的方式传值，便于修改对应关系)
void rotate_right(NodePtr& node);       // 右旋
void check_balance(NodePtr& node);      // 检查平衡，并做出相应调整
void add(int key, NodePtr& node);       // 插入数据
void remove(int key, NodePtr& node);    // 删除数据
void update_by_dfs(NodePtr& node, QPoint pos = {0, 0});
void init_avl(NodePtr& root);           // 初始化avl树，随机插入数据
void search(int key, NodePtr& node);    // 查询数据(后续考虑加锁防止错误操作导致的资源竞争)

}
