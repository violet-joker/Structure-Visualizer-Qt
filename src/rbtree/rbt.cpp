#include "rbt.h"
#include <algorithm>
#include <cmath>
#include <QColor>
#include <QDebug>

namespace RBT {
//============================ 成员函数 =========================
RbtNode::RbtNode() {
    // 这里宽度减去10，制造空隙，不至于太紧凑
    rectItem = new QGraphicsRectItem(10, 10, R + R - 10, R);
    textItem = new QGraphicsSimpleTextItem(rectItem);
    rectItem->setZValue(1);
    scene->addItem(rectItem);
    color = RED;

    static bool firstCall = true;
    if (firstCall) {
        // 第一次为nil节点 (是否会导致资源竞争?是否需要加锁?待定)
        rectItem->hide();
        color = BLACK;
        firstCall = false;
    }
}

RbtNode::~RbtNode() {
    delete rectItem;
    if (lLine) delete lLine;
    if (rLine) delete rLine;
}

// 更新该节点位置即连线情况
void RbtNode::updateThisNode(QPoint new_pos) {
    // pos记录逻辑坐标，加上偏移量为具体渲染坐标
    QPoint pos_offset {-min_x + 100, 0};
    pos = new_pos;
    rectItem->setPos(pos + pos_offset);

    // 设置节点颜色
    rectItem->setBrush(color == RED ? QColor(255, 100, 100) : QColor(100, 100, 100));
    // 设置显示文本内容
    textItem->setPos(QPoint(R - 20, R - 20));
    QString msg = QString::number(key) + " | " + QString::number(cnt);
    textItem->setText(msg);
    pos_offset += QPoint{R + 10, R - 10};

    // 如果孩子存在，更新与孩子相连的line坐标
    if (lchild != nil) {
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
    if (rchild != nil) {
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

// ================================= 非类成员函数实现 ===========================

// 申请节点，并完成初始化
NodePtr get_node(int key) {
    NodePtr node = std::make_shared<RbtNode>();
    node->key = key;
    node->cnt = 1;
    node->height = 1;
    node->lchild = node->rchild = node->parent = nil;
    return node;
}
// 维护树高
void pushup(NodePtr node) {
    if (node == nil) return;
    node->height = std::max(node->lchild->height, node->rchild->height) + 1;
}

// 左旋(调整孩子、父亲指向，并更新树高)
void left_rotate(NodePtr& node) {
    NodePtr tmp = node->rchild;
    // 更新父节点儿子指向
    if (node->parent != nil) {
        if (node->parent->lchild == node)
            node->parent->lchild = tmp;
        else
            node->parent->rchild = tmp;
    }
    // 改变孩子、父亲指针指向
    node->rchild = tmp->lchild, tmp->lchild->parent = node;
    tmp->parent = node->parent;
    tmp->lchild = node, node->parent = tmp;
    node = tmp;
    // 先更新子树，再更新node
    pushup(node->lchild);
    pushup(node);
    // 更新根节点
    if (node->parent == nil) root = node;
    // 旋转操作可能导致nil空节点内部指针指向，这里重新置空，以免错误的计数引用导致无法正确是否内存
    nil->parent = nil->lchild = nil->rchild = nullptr;
}

// 右旋(同左旋)
void right_rotate(NodePtr& node) {
    NodePtr tmp = node->lchild;
    if (node->parent != nil) {
        if (node->parent->lchild == node)
            node->parent->lchild = tmp;
        else
            node->parent->rchild = tmp;
    }
    node->lchild = tmp->rchild, tmp->rchild->parent = node;
    tmp->parent = node->parent;
    tmp->rchild = node, node->parent = tmp; 
    node = tmp;
    pushup(node->rchild);
    pushup(node);
    if (node->parent == nil) root = node;
    nil->parent = nil->lchild = nil->rchild = nullptr;
}

// 检查插入操作是否破坏红色节点不相邻性质
void check_red(NodePtr node) {
    if (node == root) node->color = BLACK;
    if (node->color == BLACK) return;
    // 父节点为黑，不作调整
    if (node->parent->color == BLACK) return;

    // 后续父节点为红，祖父必定存在且为黑
    NodePtr fa = node->parent;  // 父节点
    NodePtr gfa = fa->parent;   // 祖父节点 
    NodePtr uncle = gfa->lchild == fa ? gfa->rchild : gfa->lchild;  // 叔节点

    // 叔节点为红，叔、父变黑，祖父变红；红节点上移，后续递归判断
    if (uncle->color == RED) {
        fa->color = uncle->color = BLACK;
        gfa->color = RED;
        return;
    }

    // 叔节点为黑，旋转调整(变色维护红节点不相邻性质，旋转维护黑路同性质)
    if (fa == gfa->lchild) {
        // LR类型 (左旋fa节点，变成LL类型)
        if (node == fa->rchild)
            left_rotate(fa);    // 旋转操作引用传参，旋转后fa身份仍然正确
        // LL类型
        fa->color = BLACK;
        gfa->color = RED; 
        right_rotate(gfa);
    } else {
        // RL类型
        if (node == fa->lchild)
            right_rotate(fa);
        // RR 类型
        fa->color = BLACK;
        gfa->color = RED;
        left_rotate(gfa);
    }
}

// 检查删除操作出现的双黑、红黑节点并进行调整
void check_black(NodePtr node) {
    if (node->parent == nil) root = node;
    // 根节点或红黑节点，变黑即可
    if (node == root || node->color == RED + BLACK) {
        node->color = BLACK;
        return;
    } else if (node->color != BLACK + BLACK) {
        return;
    }

    // 当前不为根节点，则父节点必定存在；且当前节点不为红，其兄弟节点也必定存在
    NodePtr fa = node->parent;
    NodePtr bro = fa->lchild == node ? fa->rchild : fa->lchild;

    // L* 类型(双黑节点在右边，兄弟在左，需要旋转左子树进行调整)
    if (node == fa->rchild) {
        // 若兄弟为红(此时父节点必为黑)，旋转调整成兄弟为黑的情况
        if (bro->color == RED) {
            fa->color = RED; 
            bro->color = BLACK;
            right_rotate(fa);
            fa = fa->rchild;
            bro = fa->lchild;
        }
        // LR 类型，兄弟节点只存在右红孩子，旋转转换成LL类型
        if (bro->lchild->color != RED && bro->rchild->color == RED) {
            bro->color = RED;
            bro->rchild->color = BLACK;
            left_rotate(bro); 
        }
        // LL 类型，兄弟节点存在左红孩子
        // 通过变色、旋转使得node所在分支多一个黑节点，使得消除node后进入平衡
        if (bro->lchild->color == RED) {
            // 旋转会将左链上移，将所有节点继承其父节点颜色即可，再将fa节点置黑
            bro->lchild->color = bro->color;
            bro->color = fa->color;
            fa->color = BLACK;
            right_rotate(fa);
        } else {
            // 兄弟节点不存在红孩子,兄弟变红，双黑节点上移
            bro->color = RED;
            fa->color += BLACK;
        }
    } else {
        // R* 类型 (node在左，兄弟在右)
        // 兄弟为红(fa为黑)，旋转成兄弟为黑
        if (bro->color == RED) {
            fa->color = RED;
            bro->color = BLACK;
            left_rotate(fa);
            fa = fa->lchild;
            bro = fa->rchild;
        }
        // RL 类型，旋转成RR
        if (bro->rchild->color != RED && bro->lchild->color == RED) {
            bro->color = RED;
            bro->lchild->color = BLACK;
            right_rotate(bro);
        }
        // RR 类型
        if (bro->rchild->color == RED) {
            bro->rchild->color = bro->color;
            bro->color = fa->color;
            fa->color = BLACK;
            left_rotate(fa);
        } else {
            // bro无红孩子，双黑上移
            bro->color = RED;
            fa->color += BLACK;
        }
    }
    // 调整结束，node变回单黑
    node->color -= BLACK;
}

// 添加节点
void add(int key, NodePtr& node, NodePtr parent) {
    if (node == nil)
        node = get_node(key), node->parent = parent;
    else if (key == node->key)
        node->cnt++;
    else if (key < node->key)
        add(key, node->lchild, node);
    else
        add(key, node->rchild, node);
    pushup(node);
    check_red(node);
}

// 删除节点
void remove(int key, NodePtr& node) {
    if (node == nil)
        qDebug() << key << " not exist"; 
    else if (key < node->key)
        remove(key, node->lchild);
    else if (key > node->key)
        remove(key, node->rchild);
    else {
        if (node->cnt > 1) {
            node->cnt--;
            return;
        }
        // 需要删除节点
        if (node->lchild != nil && node->rchild != nil) {
            // 所删节点左右孩子均存在，这里用后继替换
            NodePtr tmp = node->rchild; 
            while (tmp->lchild != nil) tmp = tmp->lchild;
            std::swap(node->key, tmp->key);
            std::swap(node->cnt, tmp->cnt);
            remove(key, node->rchild);
        } else if (node->lchild != nil) {
            // 只存在左孩子(单个孩子，必定是当前为黑，孩子为红，孩子提上来并变色即可)
            node->lchild->parent = node->parent;
            // 由于引用传值，这里的node是父节点的某个孩子的引用，所以不用再调整父节点的孩子指针
            node = node->lchild;
            node->color = BLACK;
        } else if (node->rchild != nil) {
            // 只存在右孩子(同上)
            node->rchild->parent = node->parent;
            node = node->rchild;
            node->color = BLACK;
        } else {
            // 左右孩子都不存在
            // 只剩根节点
            if (node == root) {
                node = root = nil;
                return;
            }
            // 若节点为红，直接删
            if (node->color == RED) {
                node = nil;
                return;
            }
            // 节点为黑，删除后变成双黑节点
            // 所有空节点指向的都是nil，这里操作nil便于后续判断
            nil->parent = node->parent;
            node = nil;
            node->color += BLACK;
        }
    }
    check_black(node);
    pushup(node);
}

// 递归断掉parent节点
void release_tree(NodePtr root) {
    if (root == nullptr) return;
    release_tree(root->lchild);
    release_tree(root->rchild);
    root->parent = nullptr;
}

// 初始化红黑树，随机顺序插入20个点
void init_rbt(NodePtr& root) {
    // 首先释放原先的红黑树
    release_tree(root);
    root = nil;
    RbtNode::max_h = RbtNode::min_x = RbtNode::max_x = 0;

 /*
  * 测试数据
    int a[20] = {15, 9, 18, 6, 13, 10, 17, 27, 23, 34, 25, 37};
    int n = 12;
    for (int i = 0; i < n; i++) add(a[i], root);

    int b[20] = {18, 25, 15, 6, 13, 37, 27, 17, 34, 9, 10, 23};
    int m = 12;
    for (int i = 0; i < m; i++) {
        remove(b[i], root);
        sleep(1);
    }
    return;
*/
    int a[20], n = 20; 
    for (int i = 0; i < n; i++) a[i] = i;
    std::random_shuffle(a, a + n);
    for (int i = 0; i < n; i++) add(a[i], root);
}

// dfs遍历重新绘制所有节点(每次树的结构发生改变时调用)
void update_by_dfs(NodePtr& node, QPoint pos) {
    if (node == nil) return;

    // 更新维护边界值(先计算出值，再调用节点绘图相关，有效防止绘图错位)
    RbtNode::min_x = std::min(RbtNode::min_x, pos.x());
    RbtNode::max_x = std::max(RbtNode::max_x, pos.x());
    RbtNode::max_h = std::max(RbtNode::max_h, pos.y());
    // 根据树高决定树间距
    QPoint l_pos {pos}; // 左子树新坐标
    QPoint r_pos {pos}; // 右子树新坐标
    if (node->lchild) l_pos += QPoint(-node->R * pow(2, node->lchild->height-1), node->R * 2);
    if (node->rchild) r_pos += QPoint( node->R * pow(2, node->rchild->height-1), node->R * 2);
    update_by_dfs(node->lchild, l_pos);
    update_by_dfs(node->rchild, r_pos);
    node->updateThisNode(pos);
}

//=========================== 非成员函数 =======================
}
