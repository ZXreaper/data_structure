#include <iostream>
using namespace std;

// 可扩容
class SeqStack
{
public:
    SeqStack(int size = 10)
        : mtop(0)
        , mcap(size)
    {
        mpStack = new int[size];
    }
    ~SeqStack()
    {
        delete[] mpStack;
        mpStack = nullptr;
    }

public:
    void push(int val)
    {
        // 先判断需不需要扩容
        if(mtop == mcap)
        {
            expand(mcap*2);
        }
        mpStack[mtop++] = val;
    }

    void pop()
    {
        if(empty())
        {
            throw "Stack is empty!";
        }
        mtop--;
    }

    int top() const
    {
        if(empty())
        {
            throw "Stack is empty!";
        }
        return mpStack[mtop-1];
    }

    int size() const
    {
        return mtop;
    }

    bool empty() const
    {
        return mtop == 0;
    }

private:
    void expand(int size)
    {
        int* p = new int[size];
        for(int i = 0; i<mtop; i++)
        {
            p[i] = mpStack[i];
        }
        delete[] mpStack;
        mpStack = p;
        mcap = size;
    }

private:
    int* mpStack;
    int mtop;       // 栈顶位置
    int mcap;       // 栈空间大小
};

int main()
{
    int arr[] = {12, 4, 56, 7, 89, 31, 53, 75};
    SeqStack s;
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