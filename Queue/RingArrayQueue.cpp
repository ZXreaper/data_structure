#include <iostream>
using namespace std;

class Queue
{
public:
    Queue(int size = 10)
        : cap_(size)
        , front_(0)
        , rear_(0)
        , size_(0)
    {
        pQue_ = new int[size];
    }
    ~Queue()
    {
        delete[] pQue_;
        pQue_ = nullptr;
    }

public:
    void push(int val)
    {
        if((rear_ + 1) % cap_ == front_) 
        {
            expand(cap_ * 2);
        }
        pQue_[rear_] = val;
        rear_ = (rear_ + 1) % cap_;
        size_++;
    }

    void pop()
    {
        if(empty())
            throw "Queue is empty!";
        front_ = (front_ + 1) % cap_;
        size_--;
    }

    int front() const
    {
        if(empty())
            throw "Queue is empty!";
        return pQue_[front_];
    }

    int back() const
    {
        if(empty())
            throw "Queue is empty!";
        return pQue_[(rear_-1+cap_)%cap_];
    }

    int size() const
    {
        return size_;
    }

    bool empty() const
    {
        return front_ == rear_;
    }

private:
    void expand(int size)
    {
        int* temp = new int[size];
        int i = 0;
        while(!empty())
        {
            temp[i++] = front();
            pop();
        }
        delete[] pQue_;
        pQue_ = temp;
        rear_ = i;
        cap_ = size;
        front_ = 0;
        size_ = cap_;
    }

private:
    int* pQue_;
    int cap_;       // 记录空间容量
    int size_;      // 记录使用了多少空间
    int front_;     // 队头
    int rear_;      // 队尾
};


int main()
{
    int arr[] = {12,4,56,7,89,31,53,75};
    Queue que;

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