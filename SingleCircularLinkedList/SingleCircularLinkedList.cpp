#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// 单向循环链表
class CircleLink
{
public:
    CircleLink()
    {
        // 初始化头节点，头节点
        head_ = new Node();
        tail_ = head_;
        head_->next_ = head_;
    }
    ~CircleLink()
    {
        Node* p = head_;
        while(p->next_ != head_)
        {
            Node* q = p->next_;
            p->next_ = q->next_;
            delete q;
        }
        delete head_;
        head_ = nullptr;
    }

public:
    // 尾插法
    void InsertTail(int val)
    {
        Node* p = new Node(val);
        p->next_ = head_;
        tail_->next_ = p;
        tail_ = p;
    }

    // 头插法
    void InsertHead(int val)
    {
        Node* p = new Node(val);
        p->next_ = head_->next_;
        head_->next_ = p;
        // 如果添加的节点是第一个节点，那么tail指针也需要移动
        if(p->next_ == head_)
        {
            tail_ = p;
        }
    }

    // 删除节点
    void Remove(int val)
    {
        Node* q = head_;
        Node* p = head_->next_;

        while(p != head_)
        {
            if(p->data_ != val)
            {
                p = p->next_;
                q = q->next_;
            }
            else
            {
                q->next_ = p->next_;
                delete p;
                // 如果删除的是末尾节点
                if(q->next_ == head_)
                {
                    tail_ = q;
                }
                return ;
            }
        }
    }

    bool Find(int val) const
    {
        Node* p = head_->next_;
        while(p != head_)
        {
            if(p->data_ == val) return true;
            p = p->next_;
        }
        return false;
    }

    void show() const
    {
        Node* p = head_->next_;
        while(p != head_)
        {
            cout<< p->data_ << " ";
            p = p->next_;
        }
        cout<<endl;
    }

private:
    struct Node
    {
        Node(int data = 0): data_(data), next_(nullptr) {}
        int data_;
        Node* next_;
    };

    Node* head_;    // 指向头节点
    Node* tail_;    // 指向末尾节点
};

int main()
{
    CircleLink clink;

    clink.InsertHead(100);

    srand(time(NULL));
    for(int i = 0; i < 10; i++)
    {
        clink.InsertTail(rand() % 100);
    }

    clink.InsertTail(200);

    clink.show();

    clink.Remove(200);

    clink.show();

    clink.InsertTail(300);

    clink.show();

    cout<<clink.Find(100)<<endl;

    return 0;
}