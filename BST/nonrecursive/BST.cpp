#include <iostream>
#include <functional>
#include <algorithm>
using namespace std;

// BST树
template<typename T, typename Compare=less<T> >
class BSTree
{
public:
    BSTree() : root_(nullptr) {}
    ~BSTree() {}
    
    // 非递归插法操作
    void n_insert(const T &val)
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
            if(cur->data_ == val)
            {
                // 不插入元素相同的值
                return ;
            }
            else if(comp_(cur->data_, val))
            {
                parent = cur;
                cur = cur->right_;
            }
            else
            {
                parent = cur;
                cur = cur->left_;
            }
        }
        if(comp_(val, parent->data_))
        {
            parent->left_ = new Node(val);
        }
        else
        {
            parent->right_ = new Node(val);
        }
    }

    // 非递归删除操作
    void n_remove(const T &val)
    {
        if(root_ == nullptr)
        {
            return ;
        }
        Node *parent = nullptr;
        Node *cur = root_;
        while(cur != nullptr)
        {
            if(cur->data_ == val)
            {
                break;
            }
            else if(comp_(cur->data_, val))
            {
                parent = cur;
                cur = cur->right_;
            }
            else
            {
                parent = cur;
                cur = cur->left_;
            }
        }
        // 没找到待删除节点
        if(cur == nullptr)
        {
            return ;
        }
        // 情况3:待删除节点有两个孩子
        if(cur->left_ != nullptr && cur->right_ != nullptr)
        {
            parent = cur;
            // 找前驱节点
            Node *pre = cur->left_;
            while(pre->right_ != nullptr)
            {
                pre = pre->right_;
            }
            cur->data_ = pre->data_;
            cur = pre;      // 让cur指向前驱节点
        }

        // cur指向删除节点，parent指向其父节点，统一处理情况1或者情况2
        Node *child = cur->left_;
        if(child == nullptr)
        {
            child = cur->right_;
        }

        if(parent == nullptr) // 特殊情况 表示删除的是根节点
        {
            root_ = child;
        }
        else
        {
            if(parent->left_ == cur)
            {
                parent->left_ = child;
            }
            else
            {
                parent->right_ = child;
            }
        }

        delete cur; // 删除当前节点
    }

    // 非递归查询操作
    bool n_query(const T &val)
    {
        Node *cur = root_;
        while(cur != nullptr)
        {
            if(cur->data_ == val)
            {
                return true;
            }
            else if(comp_(cur->data_, val))
            {
                cur = cur->right_;
            }
            else
            {
                cur = cur->left_;
            }
        }
        return false;
    }

    // 递归前序遍历接口 给用户调用的
    void preOrder()
    {
        cout<<"[递归]前序遍历：";
        preOrder(root_);
        cout<<endl;
    }

    // 递归中序遍历接口 给用户调用的
    void inOrder()
    {
        cout<<"[递归]中序遍历：";
        inOrder(root_);
        cout<<endl;
    }

    // 递归后序遍历接口 给用户调用的
    void postOrder()
    {
        cout<<"[递归]后序遍历：";
        postOrder(root_);
        cout<<endl;
    }

    // 递归层序遍历接口 给用户调用的
    void levelOrder()
    {
        cout<<"[递归]层序遍历：";
        int h = high();
        for(int i = 0; i<h; i++)
        {
            levelOrder(root_, i);
        }
        cout<<endl;
    }

    // 递归求二叉树层数接口 给用户调用的
    int high()
    {
        return level(root_);
    }

    // 递归求二叉树节点个数接口
    int number()
    {
        return number(root_);
    }

private:
    // 节点定义
    struct Node
    {
        Node(T data = T())  // T() 零构造:对于c++基本类型的话就是0值或者null，对于指针类型就是空，对于自定义类型来说，就是调用该类型的默认构造
            : data_(data)
            , left_(nullptr)
            , right_(nullptr)
        {}
        T data_;
        Node* left_;
        Node* right_;
    };

    // 递归前序遍历
    void preOrder(Node *node)
    {
        if(node == nullptr) return ;
        cout<<node->data_<<" ";
        preOrder(node->left_);
        preOrder(node->right_);
    }

    // 递归中序遍历
    void inOrder(Node *node)
    {
        if(node == nullptr) return ;
        inOrder(node->left_);
        cout<<node->data_<<" ";
        inOrder(node->right_);
    }

    // 递归后序遍历
    void postOrder(Node *node)
    {
        if(node == nullptr) return ;
        postOrder(node->left_);
        postOrder(node->right_);
        cout<<node->data_<<" ";
    }

    // 递归求层序遍历
    void levelOrder(Node* node, int h)
    {
        if(node == nullptr) return ;
        if(h == 0)
        {
            cout<<node->data_<<" ";
            return ;
        }
        levelOrder(node->left_, h-1);
        levelOrder(node->right_, h-1);
    }

    // 递归实现求二叉树层数
    int level(Node *node)
    {
        if(node == nullptr) return 0;
        return max(level(node->left_), level(node->right_)) + 1;
    }

    // 递归求二叉树节点个数
    int number(Node *node)
    {
        if(node == nullptr) return 0;
        return number(node->left_) + number(node->right_) + 1;
    }

    Node* root_;     // 指向bst树的根节点
    Compare comp_;   // 定义一个函数对象
};

int main()
{
    int ar[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    BSTree<int> bst;
    for(int v : ar)
    {
        bst.n_insert(v);
    }

    bst.preOrder();
    bst.inOrder();
    bst.postOrder();
    bst.levelOrder();
    cout<<bst.high()<<endl;
    cout<<bst.number()<<endl;

    cout<<bst.n_query(67)<<endl;
    cout<<bst.n_query(12)<<endl;

    bst.n_insert(12);
    bst.n_remove(12);
    bst.n_remove(34);
    bst.n_remove(58);
    cout<<bst.n_query(12)<<endl;

    return 0;
}