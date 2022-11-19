#include <iostream>
#include <functional>
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

    cout<<bst.n_query(67)<<endl;
    cout<<bst.n_query(12)<<endl;

    bst.n_insert(12);
    bst.n_remove(12);
    bst.n_remove(34);
    bst.n_remove(58);
    cout<<bst.n_query(12)<<endl;

    return 0;
}