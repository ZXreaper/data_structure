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

    // 递归插入接口
    void insert(const T &val)
    {
        root_ = insert(root_, val);
    }    

    // 递归查询接口
    bool query(const T &val)
    {
        return query(root_, val) != nullptr;
    }

    // 递归删除接口
    void remove(const T &val)
    {
        root_ = remove(root_, val);
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

    // 递归插入操作实现
    Node* insert(Node *node, const T &val)
    {
        if(node == nullptr)
        {
            return new Node(val);
        }
        if(node->data_ == val)
        {
            return node;
        }
        else if(comp_(node->data_, val))
        {
            node->right_ = insert(node->right_, val);
        }
        else
        {
            node->left_ = insert(node->left_, val);
        }
        return node;
    }

    // 递归删除操作实现
    Node* remove(Node *node, const T &val)
    {
        if(node == nullptr) return nullptr;
        if(node->data_ == val)
        {
            // 情况3
            if(node->left_ != nullptr && node->right_ != nullptr)
            {
                // 找前驱节点
                Node *pre = node->left_;
                while(pre->right_ != nullptr)
                {
                    pre = pre->right_;
                }
                node->data_ = pre->data_;
                // 通过递归直接删除前驱节点
                node->left_ = remove(node->left_, pre->data_);
            }
            else    // 情况1和情况2
            {
                if(node->left_ != nullptr)
                {
                    Node* left = node->left_;
                    delete node;
                    return left;
                }
                else if(node->right_ != nullptr)
                {
                    Node* right = node->right_;
                    delete node;
                    return right;
                }
                else    // 删除叶子结点
                {
                    delete node;
                    return nullptr;
                }
            }
        }
        else if(comp_(node->data_, val))
        {
            node->right_ = remove(node->right_, val);
        }
        else
        {
            node->left_ = remove(node->left_, val);
        }
        return node;
    }

    // 递归查询操作
    Node* query(Node* node, const T &val)
    {
        if(node == nullptr) return nullptr;
        if(node->data_ == val) return node;
        else if(comp_(node->data_, val))
        {
            return query(node->right_, val);
        }
        else
        {
            return query(node->left_, val);
        }
    }

private:
    Node* root_;     // 指向bst树的根节点
    Compare comp_;   // 定义一个函数对象
};

int main()
{
    int ar[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    BSTree<int> bst;
    for(int v : ar)
    {
        bst.insert(v);
    }

    bst.preOrder();
    bst.inOrder();
    bst.postOrder();
    bst.levelOrder();
    cout<<bst.high()<<endl;
    cout<<bst.number()<<endl;

    cout<<bst.query(67)<<endl;
    cout<<bst.query(12)<<endl;

    bst.insert(12);
    cout<<bst.query(12)<<endl;
    bst.remove(12);
    bst.remove(34);
    bst.remove(58);
    cout<<bst.query(12)<<endl;
    cout<<bst.query(58)<<endl;

    bst.inOrder();
    
    return 0;
}