#include <iostream>
using namespace std;

// 链式栈
class LinkStack
{
public:
    LinkStack() : mcap_(0)
    {
        head_ = new Node();
    }
    ~LinkStack()
    {
        Node* p = head_->next_;
        while(p != nullptr)
        {
            head_->next_ = p->next_;
            delete p;
            p = head_->next_;
        }
        delete head_;
        head_ = nullptr;
    }

public:
    // 头插法
    void push(int val)
    {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
        mcap_++;
    }

    void pop()
    {
        if(empty())
            throw "Stack is empty!";
        Node* p = head_->next_;
        head_->next_ = p->next_;
        delete p;
        mcap_--;
    }

    int top()
    {
        if(empty())
            throw "Stack is empty!";
        return head_->next_->data_;
    }

    bool empty() const
    {
        return head_->next_ == nullptr;
    }

    int size() const
    {
        return mcap_;
    }

private:
    struct Node
    {
        Node(int data = 0) : data_(data), next_(nullptr) {}
        int data_;
        Node* next_;
    };

    Node* head_;
    int mcap_;
};

int main()
{
    int arr[] = {12, 4, 56, 7, 89, 31, 53, 75};
    LinkStack s;
    for(int v : arr)
    {
        s.push(v);
    }
    while(!s.empty())
    {
        int t = s.top();
        s.pop();
        cout<<t<<endl;
    }
    // cout<<s.top()<<endl;
    return 0;
}