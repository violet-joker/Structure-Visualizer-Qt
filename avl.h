#ifndef AVL_H
#define AVL_H

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
    void updateThisNode(QPoint new_pos);
    void delay(int duration);

public:
    static inline int max_x {1};
    static inline int min_x {1};
    static inline int max_h {1};
    static inline int R {50};
    static inline QGraphicsScene* scene;

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
void pushup(NodePtr node);
void rotate_left(NodePtr& node);
void rotate_right(NodePtr& node);
void check_balance(NodePtr& node);
void add(int key, NodePtr& node);
void remove(int key, NodePtr& node);
void update_by_dfs(NodePtr& node, QPoint pos = {0, 0});
void init_avl(NodePtr& root);
void search(int key, NodePtr& node);

}
#endif // AVL_H
