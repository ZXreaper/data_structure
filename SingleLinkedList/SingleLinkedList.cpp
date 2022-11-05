#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// 节点类型
struct Node
{
    Node(int data = 0) : data_(data), next_(nullptr) {};
    int data_;
    Node* next_;
};

class Clink
{
public:
    Clink()
    {
        // 给head_初始化指向头节点
        head_ = new Node();
    }
    ~Clink()
    {
        // 节点的释放
        Node* p = head_;
        while(p != nullptr)
        {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
        head_ = nullptr;
    }
public:
    // 链表的尾插法 O(N)  为了提高尾插法的效率，可以专门为链表提供一个尾节点
    void InsertTail(int val)
    {
        // 先找到当前链表的末尾节点
        Node* p = head_;
        while(p->next_ != nullptr) p = p->next_;
        // 生成新节点
        Node *node = new Node(val);
        p->next_ = node;
    }

    // 链表的头插法 O(1)
    void InsertHead(int val)
    {
        Node *node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
    }

    // 链表节点的删除，按值删除第一个出现的值为val的节点
    void Remove(int val)
    {
        Node* p = head_;
        Node* q = head_->next_;
        while(q != nullptr)
        {
            if(q->data_ == val)
            {
                p->next_ = q->next_;
                delete q;
                return ;
            }
            p = q;
            q = q->next_;
        }
    }

    // 链表节点的删除，按值删除所有值为val的节点
    void RemoveAllVal(int val)
    {
        Node* p = head_;
        Node* q = head_->next_;
        while(q != nullptr)
        {
            if(q->data_ == val)
            {
                p->next_ = q->next_;
                delete q;
                q = p->next_;
                continue;
            }
            p = q;
            q = q->next_;
        }
    }

    // 搜索
    bool Find(int val)
    {
        Node* p = head_->next_;
        while(p != nullptr)
        {
            if(p->data_ == val)
                return true;
            p = p->next_;
        }
        return false;
    }

    // 链表打印
    void show()
    {
        Node* p = head_->next_;
        while(p != nullptr)
        {
            cout<<p->data_<<" ";
            p = p->next_;
        }
        cout<<endl;
    }
private:
    Node *head_;    // 指向链表的头节点
};

int main()
{
    Clink link;
    srand(time(0));
    for(int i = 0; i<10; i++)
    {
        int val = rand() % 100;
        link.InsertHead(val);
        cout<<val<<" ";
    }
    cout<<endl;

    link.InsertTail(23);
    link.InsertHead(23);
    link.InsertHead(23);
    link.InsertHead(23);
    link.InsertHead(45);

    link.show();

    link.Remove(200);
    link.RemoveAllVal(23);

    link.show();
    return 0;
}