#include "avl.h"
#include <cmath>
#include <QDebug>
#include <algorithm>

namespace AVL {
// ======================== 成员函数 ====================


AvlNode::AvlNode()
{
    rectItem = new QGraphicsRectItem(10, 10, R + R - 10, R);
    textItem = new QGraphicsSimpleTextItem(rectItem);
    rectItem->setBrush(QColor(100, 255, 100));
    rectItem->setZValue(1);
    scene->addItem(rectItem);
}

AvlNode::~AvlNode() {
    // textItem会随着父组件rectItem一起释放
    delete rectItem;
    if (lLine) delete lLine;
    if (rLine) delete rLine;
}

// 主要是绘图相关更新，这里需要确保先知道孩子节点的坐标信息(dfs后续遍历即可)
void AvlNode::updateThisNode(QPoint new_pos) {
    // pos记录逻辑坐标，加上偏移量为具体渲染坐标
    QPoint pos_offset {-min_x + 100, 0};
    pos = new_pos;
    rectItem->setPos(pos + pos_offset);

    // 设置显示文本内容
    textItem->setPos(QPoint(R - 20, R - 20));
    QString msg = QString::number(key) + " | " + QString::number(cnt);
    textItem->setText(msg);

    pos_offset += QPoint{R + 10, R - 10};

    // 如果孩子存在，更新与孩子相连的line坐标
    if (lchild) {
        if (!lLine) {
            lLine = new QGraphicsLineItem();
            scene->addItem(lLine);
        }
        lLine->setLine(QLine(pos + pos_offset, lchild->pos + pos_offset));
    } else if (lLine) {
        // 旋转操作导致的叶子节点可能出现line指针悬空的情况，释放掉该line
        delete lLine;
        lLine = nullptr;
    }
    if (rchild) {
        if (!rLine) {
            rLine = new QGraphicsLineItem();
            scene->addItem(rLine);
        }
        rLine->setLine(QLine(pos + pos_offset, rchild->pos + pos_offset));
    } else if (rLine) {
        delete rLine;
        rLine = nullptr;
    }

}

// 设置该节点改变颜色，延时一段时间后恢复
void AvlNode::delay(int duration) {
    if (rectItem) rectItem->setBrush(QColor(255, 100, 100));
    sleep_for(duration * 1000);
    if (rectItem) rectItem->setBrush(QColor(100, 255, 100));
}

// ======================== AVL树非成员函数相关操作 ====================

// 设置延时，timer记时，同时loop进入事件循环;超时后发出timeout信号，loop退出循环
void sleep_for(int ms) {
    timer.start(ms);
    if (!loop->isRunning())
        loop->exec();
//    loop->exec();
}

// 获取节点，用智能指针包装，并完成初始化
NodePtr get_node(int key) {
    NodePtr node = std::make_shared<AvlNode>();
    node->key = key;
    node->height = 1;
    node->cnt = 1;
    return node;
}

// 维护树高
void pushup(NodePtr node) {
    if (node == nullptr) return;
    // lambda函数获取树高
    auto get_h = [](NodePtr& tmp) {
        if (tmp == nullptr) return 0;
        else return tmp->height;
    };
    node->height = std::max(get_h(node->lchild), get_h(node->rchild)) + 1;
}


// 左旋
void rotate_left(NodePtr& node) {
    NodePtr child = node->rchild;
    node->rchild = child->lchild;
    child->lchild = node;
    node = child;
    pushup(node->lchild);
    pushup(node);
}

// 右旋
void rotate_right(NodePtr& node) {
    NodePtr child = node->lchild;
    node->lchild = child->rchild;
    child->rchild = node;
    node = child;
    pushup(node->rchild);
    pushup(node);
}

// 检查是否平衡，不平衡则旋转调整
void check_balance(NodePtr& node) {
    if (node == nullptr) return;

    auto get_h = [](NodePtr& tmp) {
        if (tmp == nullptr) return 0;
        else return tmp->height;
    };
    // L*类型
    if (get_h(node->lchild) - get_h(node->rchild) == 2) {
        NodePtr& child = node->lchild;
        // LR类型
        if (get_h(child->lchild) - get_h(child->rchild) == -1)
            rotate_left(child), rotate_right(node);
        else
            rotate_right(node);
    }
    // R*类型
    if (get_h(node->lchild) - get_h(node->rchild) == -2) {
        NodePtr& child = node->rchild;
        // RL
        if (get_h(child->lchild) - get_h(child->rchild) == 1)
            rotate_right(child), rotate_left(node);
        else
            rotate_left(node);
    }
}

// 根据key值添加节点(引用传参，便于给空节点赋值时更新父节点的孩子指向; 也便于管理root节点)
void add(int key, NodePtr& node) {
    if (node == nullptr)
        node = get_node(key);
    else if (key == node->key)
        node->cnt++;
    else if (key < node->key)
        add(key, node->lchild);
    else
        add(key, node->rchild);
    pushup(node);
    check_balance(node);
}

// 删除节点
void remove(int key, NodePtr& node) {
    if (node == nullptr) {
        qDebug() << key << " not exist.\n";
        return;
    } else if (key > node->key) {
        remove(key, node->rchild);
    } else if (key < node->key) {
        remove(key, node->lchild);
    } else {
        if (node->cnt > 1) node->cnt--;
        // 被删除节点无左右孩子，叶子节点直接删
        else if (!node->lchild && !node->rchild)
            node = nullptr;
        // 只有右孩子，删该节点，右孩子提上来
        else if (!node->lchild)
            node = node->rchild;
        // 只有左孩子
        else if (!node->rchild)
            node = node->lchild;
        // 左右孩子都存在，这里用后继替换
        else {
            NodePtr back = node->rchild;
            while (back->lchild) back = back->lchild;
            std::swap(back->key, node->key);
            std::swap(back->cnt, node->cnt);
            remove(key, node->rchild);
        }
    }
    pushup(node);
    check_balance(node);
}

// dfs只能采取后续遍历，必须先更新儿子，最后更新父节点
void update_by_dfs(NodePtr& node, QPoint pos) {
    if (node == nullptr) return;

    // 更新维护边界值(先计算出值，再调用节点绘图相关，有效防止绘图错位)
    AvlNode::min_x = std::min(AvlNode::min_x, pos.x());
    AvlNode::max_x = std::max(AvlNode::max_x, pos.x());
    AvlNode::max_h = std::max(AvlNode::max_h, pos.y());
    // 根据树高决定树间距
    QPoint l_pos {pos};
    QPoint r_pos {pos};
    if (node->lchild) l_pos += QPoint(-node->R * pow(2, node->lchild->height-1), node->R * 2);
    if (node->rchild) r_pos += QPoint( node->R * pow(2, node->rchild->height-1), node->R * 2);
    update_by_dfs(node->lchild, l_pos);
    update_by_dfs(node->rchild, r_pos);
    node->updateThisNode(pos);
}

// 清空原有树，并随机初始化数据
void init_avl(NodePtr& root) {
    // 智能指针会递归释放孩子节点 (add引用传参，当root为空的时候会为其赋值)
    root = nullptr;
    AvlNode::max_h = AvlNode::min_x = AvlNode::max_x = 0;
    const int N = 20;
    int a[N];
    for (int i = 0; i < N; i++) a[i] = i + 1;
    std::random_shuffle(a, a + N);
    // 随机打乱数组a，再插入到avl树里
    for (int i = 0; i < N; i++) add(a[i], root);
}


// 查询
void search(int key, NodePtr& node) {
    if (node == nullptr)
        return;
    node->delay(1);
    if (key < node->key)
        search(key, node->lchild);
    else
        search(key, node->rchild);
}

}
