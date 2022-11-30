#include <iostream>
using namespace std;

// 红黑树
template<typename T>
class RBTree
{
public:
    RBTree() : root_(nullptr) {}

    // 插入操作
    void insert(const T &val)
    {
        if(root_ == nullptr)
        {
            root_ = new Node(val);
            return ;
        }
        Node *parent = nullptr;
        Node *cur = root_;
        while(cur != nullptr)
        {
            if(cur->data_ > val)
            {
                parent = cur;
                cur = cur->left_;
            }
            else if(cur->data_ < val)
            {
                parent = cur;
                cur = cur->right_;
            }
            else
            {
                return ;
            }
        }
        // 插入节点  设置当前节点的parent和颜色
        Node *node = new Node(val, parent, nullptr, nullptr, RED);
        if(parent->data_ > val)
        {
            parent->left_ = node;
        }
        else
        {
            parent->right_ = node;
        }

        // 如果新插入的红色节点，父节点也是红色，不满足红黑树的性质，进行插入调整操作
        if(RED == color(parent))
        {
            fixAfterInsert(node);
        }
    }

    // 删除操作
    void remove(const T &val)
    {
        if(root_ == nullptr)
            return ;

        Node *cur = root_;
        while(cur != nullptr)
        {
            if(cur->data_ > val)
            {
                cur = cur->left_;
            }
            else if(cur->data_ < val)
            {
                cur = cur->right_;
            }
            else
                break;
        }
        if(cur == nullptr)
        {
            return ;
        }
        // 删除前驱节点  情况三
        if(cur->left_ != nullptr && cur->right_ != nullptr)
        {
            Node *pre = cur->left_;
            // 找前驱
            while(pre->right_ != nullptr)
            {
                pre = pre->right_;
            }
            cur->data_ = pre->data_;
            cur = pre;  // cur指向前驱节点
        }
        // 删除cur指向的节点  情况一和二
        Node *child = cur->left_;
        if(child == nullptr)
        {
            child = child->right_;
        }
        if(child != nullptr)
        {
            child->parent_ = cur->parent_;
            if(cur->parent_ == nullptr)
            {
                // root_ -> cur_
                root_ = child;
            }
            else
            {
                if(cur->parent_->left_ == cur)
                {
                    cur->parent_->left_ = child;
                }
                else
                {
                    cur->parent_->right_ = child;
                }
            }
            Color c = color(cur);
            delete cur;

            if(c == BLACK) // 删除的是黑色节点，要进行删除调整操作
            {
                fixAfterRemove(child);
            }
        }
        else
        {

        }
    }

private:
    // 红黑树节点颜色
    enum Color
    {
        BLACK,
        RED
    };

    // 节点类型
    struct Node
    {
        Node(T data=T(), Node *left = nullptr, Node *right = nullptr, Node *parent = nullptr, Color color = BLACK)
            : data_(data)
            , left_(left)
            , right_(right)
            , parent_(parent)
            , color_(color)
        {}
        T data_;        // 数据域
        Node *left_;    // 左儿子
        Node *right_;   // 右儿子
        Node *parent_;  // 父节点
        Color color_;   // 节点的颜色
    };

    // 返回节点颜色
    Color color(Node *node)
    {
        return node == nullptr ? BLACK : node->color_;
    }

    // 设置节点颜色
    void setColor(Node *node, Color color)
    {
        node->color_ = color;
    }

    // 返回节点的左孩子
    Node *left(Node *node) 
    {
        return node->left_;
    }
    
    // 返回节点的右孩子
    Node *right(Node *node)
    {
        return node->right_;
    }

    // 返回节点的父亲
    Node *parent(Node *node)
    {
        return node->parent_;
    }

    // 左旋转
    void leftRotate(Node *node)
    {
        Node *child = node->right_;
        Node *parent = node->parent_;
        child->parent_ = parent;
        if(parent == nullptr)
        {
            // node本神就是root节点
            root_ = child;
        }
        else
        {
            if(node->parent_->left_ == node)
            {
                // node在父节点的左孩子
                parent->left_ = child;
            }
            else
            {
                // node在父节点的右孩子
                parent->right_ = child;
            }
        }
        node->right_ = child->left_;
        if(child->left_ != nullptr)
        {
            child->left_->parent_ = node;
        }
        child->left_ = node;
        node->parent_ = child;

    }

    // 右旋转
    void rightRotate(Node *node)
    {
        Node *child = node->left_;
        Node *parent = node->parent_;
        child->parent_ = parent;
        if(parent == nullptr)
        {
            root_ = child;
        }
        else
        {
            if(parent->left_ == node)
            {
                parent->left_ = child;
            }
            else
            {
                parent->right_ = child;
            }
        }
        node->left_ = child->right_;
        if(child->right_ != nullptr)
        {
            child->right_->parent_ = node;
        }
        child->right_ = node;
        node->parent_ = child;
    }

    // 红黑树的插入调整操作
    // 插入节点可能在左边或者右边，每一边有3种情况，总共6种情况
    void fixAfterInsert(Node *node)
    {
        // 当前节点是红色，如果其父节点也是红色，那么我们需要进行调整
        while(color(parent(node)) == RED)
        {
            // 插入的节点在左子树当中
            if(left(parent(parent(node))) == parent(node))
            {
                Node *uncle = right(parent(parent(node)));
                if(color(uncle) == RED)     // 情况1
                {
                    setColor(parent(node), BLACK);      // 把父亲的颜色置成黑色
                    setColor(uncle, BLACK);             // 把叔叔的颜色置成黑色
                    setColor(parent(parent(node)), RED);// 把爷爷的颜色置成红色
                    node = parent(parent(node));        // 爷爷的父亲可能是红色，所以将node置成爷爷，继续调整
                }
                else        // 情况2和3
                {
                    // 先处理情况3，最后统一处理情况2
                    if(right(parent(node)) == node)
                    {
                        node = parent(node); // 为了将情况3的node和情况2的node统一起来，我们将情况3种的node置为其父节点，这样旋转之后就和情况2的node一样了
                        leftRotate(node);
                    }
                    // 统一处理情况2
                    setColor(parent(node), BLACK);
                    setColor(parent(parent(node)), RED);
                    rightRotate(parent(parent(node)));
                    break;  // 调整已经完成。因此红黑树在插入过程中最多进行两次旋转操作
                }
            }
            else  // 插入的节点在右子树当中
            {
                Node *uncle = left(parent(parent(node)));
                if(color(uncle) == RED)     // 情况1
                {
                    setColor(parent(node), BLACK);      // 把父亲的颜色置成黑色
                    setColor(uncle, BLACK);             // 把叔叔的颜色置成黑色
                    setColor(parent(parent(node)), RED);// 把爷爷的颜色置成红色
                    node = parent(parent(node));        // 爷爷的父亲可能是红色，所以将node置成爷爷，继续调整
                }
                else        // 情况2和3
                {
                    // 先处理情况3，最后统一处理情况2
                    if(left(parent(node)) == node)
                    {
                        node = parent(node); // 为了将情况3的node和情况2的node统一起来，我们将情况3种的node置为其父节点，这样旋转之后就和情况2的node一样了
                        rightRotate(node);
                    }
                    // 统一处理情况2
                    setColor(parent(node), BLACK);
                    setColor(parent(parent(node)), RED);
                    leftRotate(parent(parent(node)));
                    break;  // 调整已经完成。因此红黑树在插入过程中最多进行两次旋转操作
                }
            }
        }

        // 此处强制root为黑色节点
        setColor(root_, BLACK);
    }

    // 红黑树的删除调整操作
    void fixAfterRemove(Node *node)
    {
        while (color(node) == BLACK)
        {
            if(left(parent(node)) == node)  // 删除的黑色节点在左子树
            {
                Node *brother = right(parent(node));
                // 先处理情况四
                if(color(brother) == RED)
                {
                    setColor(parent(node), RED);
                    setColor(brother, BLACK);
                    leftRotate(parent(node));
                    brother = right(parent(node));  // 更新兄弟节点
                }
                // 情况四处理完后，保证兄弟节点是黑色的
                // 再处理情况三
                if(color(brother->left_) == BLACK && color(brother->right_) == BLACK)
                {
                    setColor(brother, RED);
                    node = parent(node);
                }
                else
                {
                    if(color(right(brother)) != RED)    // 情况二
                    {
                        setColor(brother, RED);
                        setColor(left(brother), BLACK);
                        rightRotate(brother);
                        brother = right(parent(node));
                    }

                    // 归结到情况一
                    setColor(brother, color(parent(node)));
                    setColor(parent(node), BLACK);
                    setColor(right(brother), BLACK);
                    leftRotate(parent(node));
                    break;
                }
            }
            else        // 删除的黑色节点在右子树
            {
                Node *brother = left(parent(node));
                // 先处理情况四
                if(color(brother) == RED)
                {
                    setColor(parent(node), RED);
                    setColor(brother, BLACK);
                    rightRotate(parent(node));
                    brother = left(parent(node));  // 更新兄弟节点
                }
                // 情况四处理完后，保证兄弟节点是黑色的
                // 再处理情况三
                if(color(brother->left_) == BLACK && color(brother->right_) == BLACK)
                {
                    setColor(brother, RED);
                    node = parent(node);
                }
                else
                {
                    if(color(left(brother)) != RED)    // 情况二
                    {
                        setColor(brother, RED);
                        setColor(right(brother), BLACK);
                        leftRotate(brother);
                        brother = left(parent(node));
                    }

                    // 归结到情况一
                    setColor(brother, color(parent(node)));
                    setColor(parent(node), BLACK);
                    setColor(left(brother), BLACK);
                    rightRotate(parent(node));
                    break;
                }
            }
        }

        // 如果发现node指向的节点是红色，直接涂成黑色，调整结束
        setColor(node, BLACK);
    }

    Node *root_;        // 指向红黑树的根节点
};

int main()
{
    RBTree<int> rbt;
    
    return 0;
}