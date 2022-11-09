#include <iostream>
using namespace std;

class LinkedQueue
{
public:
    LinkedQueue()
        : size_(0)
    {
        head_ = new Node();
        head_->next_ = head_;
        head_->pre_ = head_;
    }
    ~LinkedQueue()
    {
        Node* p = head_->next_;
        while(p != head_)
        {
            head_->next_ = head_->next_->next_;
            head_->next_->pre_ = head_;
            delete p;
            p = head_->next_;
        }
        delete head_;
        head_ = nullptr;
    }

public:
    void push(int val)
    {
        Node* node = new Node(val);
        Node* p = head_->pre_;
        node->next_ = head_;
        head_->pre_ = node;
        p->next_ = node;
        node->pre_ = p;
        size_++;
    }

    void pop()
    {
        Node* p = head_->next_;
        head_->next_ = p->next_;
        p->next_->pre_ = head_;
        delete p;
        size_--;
    }

    int front() const
    {
        if(empty())
            throw "Queue is empty!";
        return head_->next_->data_;
    }

    int back() const
    {
        if(empty())
            throw "Queue is empty!";
        return head_->pre_->data_;
    }

    bool empty() const
    {
        return head_->next_ == head_;
    }

    int size() const
    {
        return size_;
    }

private:
    struct Node
    {
        Node(int data = 0) : data_(data), next_(nullptr), pre_(nullptr) {}
        int data_;
        Node* next_;
        Node* pre_;
    };
    Node* head_;    // 指向头节点
    int size_;
};


int main()
{
    int arr[] = {12,4,56,7,89,31,53,75};
    LinkedQueue que;

    for (int v : arr)
    {
        que.push(v);
    }

    while(!que.empty())
    {
        cout<<que.front()<<" ";
        que.pop();
    }
    cout<<endl;

    for (int v : arr)
    {
        que.push(v);
    }

    cout<< que.front() <<endl;
    cout<< que.back() <<endl;

    que.push(123);
    que.push(123);
    que.push(123);
    que.push(123);
    que.push(123);

    while(!que.empty())
    {
        cout<<que.front()<<" ";
        que.pop();
    }
    cout<<endl;

    return 0;
}