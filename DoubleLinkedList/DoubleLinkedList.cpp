#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// 定义双向链表的节点类型
struct Node
{
    Node(int data = 0) : data_(data), next_(nullptr), pre_(nullptr) {}
    int data_;
    Node* next_;
    Node* pre_;
};

// 双向链表
class DoubleLinkedList
{
public:
    DoubleLinkedList()
    {
        head_ = new Node();
    }
    ~DoubleLinkedList()
    {
        Node* p = head_;
        while(p != nullptr)
        {
            head_ = head_->next_;
            delete p;
            p = head_;
        }
    }
public:
    // 头插法
    void InsertHead(int val)
    {
        Node* p = new Node(val);
        p->next_ = head_->next_;
        p->pre_ = head_;
        // 判断是否是只有当前这一个节点，如果有其他节点，需要把后继节点的前向指针做修改
        if(p->next_ != nullptr)
        {
            p->next_->pre_ = p;
        }
        head_->next_ = p;
    }

    // 尾插法
    void InsertTail(int val)
    {
        Node* p = head_;
        while(p->next_ != nullptr)
        {
            p = p->next_;
        }
        Node* node = new Node(val);
        p->next_ = node;
        node->pre_ = p;
        node->next_ = nullptr;      // 省略也行
    }

    // 找节点
    bool Find(int val)
    {
        Node* p = head_->next_;
        while(p != nullptr)
        {
            if(p->data_ == val) return true;
            p = p->next_;
        }
        return false;
    }

    // 删节点
    void Remove(int val)
    {
        Node* p = head_->next_;
        while(p != nullptr)
        {
            if(p->data_ == val)
            {
                p->pre_->next_ = p->next_;
                // 如果有后面的节点再进行修改
                if(p->next_ != nullptr)
                {
                    p->next_->pre_ = p->pre_;
                }
                delete p;
                return ;
            }
            else
            {
                p = p->next_;
            }
        }
    }

    // 打印
    void show()
    {
        Node* p = head_->next_;
        while(p != nullptr)
        {
            cout<< p->data_ << " ";
            p = p->next_;
        }
        cout<<endl;
    }

private:
    Node* head_;
};



int main()
{
    DoubleLinkedList dlink;
    dlink.InsertHead(100);
    dlink.InsertTail(29);
    dlink.InsertTail(239);
    dlink.InsertTail(298);
    dlink.InsertTail(129);
    dlink.InsertTail(78);
    dlink.InsertTail(56);
    dlink.show();

    dlink.InsertHead(200);
    dlink.show();
    dlink.Remove(200);
    dlink.show();
    dlink.Remove(56);
    dlink.show();
    dlink.Remove(129);
    dlink.show();

    return 0;
}