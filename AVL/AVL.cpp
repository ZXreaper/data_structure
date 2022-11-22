#include <iostream>
#include <algorithm>
using namespace std;

// AVL Tree
template<typename T>
class AVLTree
{
public:
    AVLTree() : root_(nullptr) {}
    ~AVLTree() {} // 析构操作实际上是需要将树中的节点都释放掉的，这里省略了，重点放在avl的插入、删除、旋转操作上

    // AVL树的插入操作接口
    void insert(const T &val)
    {
        root_ = insert(root_, val);
    }

    // AVL树的删除操作接口
    void remove(const T &val)
    {
        root_ = remove(root_, val);
    }

private:
    // 定义AVL树节点类型
    struct Node
    {
        Node(T data=T())
            : data_(data)
            , left_(nullptr)
            , right_(nullptr)
            , height_(1)
        {}
        T data_;
        Node *left_;
        Node *right_;
        int height_;    // 记录节点的高度值
    };

    // 返回节点的高度值
    int height(Node *node)
    {
        return node == nullptr ? 0 : node->height_;
    }

    // 右旋转操作 以参数node为轴做右旋转操作，并把新的节点返回
    Node* rightRotate(Node *node)
    {
        // 节点旋转
        Node *child = node->left_;
        node->left_ = child->right_;
        child->right_ = node;
        // 高度更新  先更新node的，在更新child的
        node->height_ = max(height(node->left_), height(node->right_)) + 1;
        child->height_ = max(height(child->left_), height(child->right_)) + 1;
        // 返回新的节点
        return child;
    }

    // 左旋转操作 以参数node为轴做左旋转操作，并把新的节点返回
    Node* leftRotate(Node *node)
    {
        // 节点旋转
        Node *child = node->right_;
        node->right_ = child->left_;
        child->left_ = node;
        // 高度更新  先更新node的，在更新child的
        node->height_ = max(height(node->left_), height(node->right_)) + 1;
        child->height_ = max(height(child->left_), height(child->right_)) + 1;
        // 返回新的节点
        return child;
    }

    // 左平衡操作 以参数node为轴做左-右旋转操作，并把新的根节点返回
    // 左孩子的右子树太高了，先以左孩子为根节点做左旋转，再做右旋转
    Node* leftBalance(Node *node)
    {
        node->left_ = leftRotate(node->left_);
        return rightRotate(node);
    }

    // 右平衡操作 以参数node为轴做右-左旋转操作，并把新的根节点返回
    // 右孩子的左子树太高了，先以右孩子为根节点做右旋转，再做左旋转
    Node* rightBalance(Node *node)
    {
        node->right_ = rightRotate(node->right_);
        return leftRotate(node);
    }

    // AVL插入操作实现
    Node* insert(Node* node, const T &val)
    {
        if(node == nullptr)
        {
            return new Node(val);
        }
        if(val > node->data_)
        {
            node->right_ = insert(node->right_, val);
            // 在递归回溯时判断节点是否失衡
            if(height(node->right_) - height(node->left_) > 1)
            {
                if(height(node->right_->right_) >= height(node->right_->left_))
                {
                    // 节点失衡，由于右孩子的右子树太高了
                    node = leftRotate(node);
                }
                else
                {
                    // 节点失衡，由于右孩子的左子树太高了
                    node = rightBalance(node);
                }
            }
        }
        else if(val < node->data_)
        {
            node->left_ = insert(node->left_, val);
            // 在递归回溯时判断节点是否失衡
            if(height(node->left_) - height(node->right_) > 1)
            {
                if(height(node->left_->left_) >= height(node->left_->right_))
                {
                    // 节点失衡，由于左孩子的左子树太高了
                    node = rightRotate(node);
                }
                else
                {
                    // 节点失衡，由于左孩子的右子树太高了
                    node = leftBalance(node);
                }
            }
        }

        // 因为子树中增加了新的节点，在递归回溯时检测更新节点高度
        node->height_ = max(height(node->left_), height(node->right_)) + 1;

        return node;
    }

    // 删除操作实现
    Node* remove(Node* node, const T &val)
    {
        if(node == nullptr)
            return nullptr;
        
        if(node->data_ > val)
        {
            node->left_ = remove(node->left_, val);
            // 左子树删除节点，可能造成右子树太高
            if(height(node->right_) - height(node->left_) > 1)
            {
                if(height(node->right_->right_) >= height(node->right_->left_))
                {
                    // 右孩子的右子树太高
                    node = leftRotate(node);
                }
                else
                {
                    // 右孩子的左子树太高
                    node = rightBalance(node);
                }
            }
        }
        else if(node->data_ < val)
        {
            node->right_ = remove(node->right_, val);
            // 右子树删除节点，可能造成左子树太高
            if(height(node->left_) - height(node->right_) > 1)
            {
                if(height(node->left_->left_) >= height(node->left_->right_))
                {
                    // 左孩子的左子树太高
                    node = rightRotate(node);
                }
                else
                {
                    // 左孩子的右子树太高
                    node = leftBalance(node);
                }
            }
        }
        else
        {
            // 找到了 先处理有两个孩子的节点的情况
            if(node->left_ != nullptr && node->right_ != nullptr)
            {
                // 为了避免删除前驱或者后继节点造成节点失衡，谁高删除谁
                if(height(node->left_) > height(node->right_))
                {
                    // 删前驱
                    Node *pre = node->left_;
                    while(pre->right_ != nullptr)
                        pre = pre->right_;
                    node->data_ = pre->data_;
                    node->left_ = remove(node->left_, pre->data_); // 删前驱节点
                }
                else
                {
                    // 删后继
                    Node *post = node->right_;
                    while(post->left_ != nullptr)
                        post = post->left_;
                    node->data_ = post->data_;
                    node->right_ = remove(node->right_, post->data_); // 删后继节点
                }
            }
            else    // 删除节点，最多有一个孩子
            {
                if(node->left_ != nullptr)
                {
                    Node *left = node->left_;
                    delete node;
                    return left;
                }
                else if(node->right_ != nullptr)
                {
                    Node *right = node->right_;
                    delete node;
                    return right;
                }
                else
                {
                    return nullptr;
                }
            }
        }

        // 更新节点高度
        node->height_ = max(height(node->left_), height(node->right_)) + 1;

        return node;  // 递归回溯过程中，把当前节点给父节点返回
    }

    Node *root_;    // 指向根节点
};


int main()
{
    AVLTree<int> avl;
    
    for(int i = 1; i<=10; i++)
    {
        avl.insert(i);
    }

    avl.remove(9);
    avl.remove(10);
    avl.remove(6);
    avl.remove(1);
    avl.remove(2);
    avl.remove(3);

    return 0;
}