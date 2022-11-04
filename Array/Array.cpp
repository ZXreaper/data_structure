#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Array
{
public:
    Array(int size = 10) : mCap_(size), mCur(0)
    {
        mpArr = new int[mCap_];
    }
    ~Array()
    {
        delete []mpArr;
        mpArr = nullptr;
    }

public:
    // 末尾增加元素
    void push_back(int val)
    {
        // 需要扩容
        if(mCur + 1 > mCap_)
        {
            expand(2 * mCap_);
        }
        mpArr[mCur++] = val;
    }
    // 末尾删除元素
    void pop_back()
    {
        if(mCur > 0)
            mCur--;
        else
        {
            cout<<"No item in Array currently!"<<endl;
        }
    }
    // 按位置增加元素
    void insert(int pos, int val)
    {
        if(pos < 0 || pos > mCur)
        {
            return ;  // throw "pos invalid!"
        }
        // 需要扩容
        if(mCur + 1 > mCap_)
        {
            expand(2 * mCap_);
        }
        for(int i = mCur-1; i>=pos; i--)
        {
            mpArr[i+1] = mpArr[i];
        }
        mpArr[pos] = val;
        mCur++;
    }
    // 元素查询 : 找到了返回元素下标，否则返回-1
    int find(int val)
    {
        for(int i = 0; i<mCur; i++)
        {
            if(mpArr[i] == val)
            {
                return i;
            }
        }
        return -1;
    }
    // 按位置删除
    void erase(int pos)
    {
        if(pos < 0 || pos >= mCur)
        {
            return ;
        }
        for(int i = pos+1; i<=mCur-1; i++)
        {
            mpArr[i-1] = mpArr[i];
        }
        mCur--;
    }
    // 打印数据
    void show() const
    {
        for(int i = 0; i<mCur; i++)
        {
            cout<<mpArr[i]<<" ";
        }
        cout<<endl;
    }
private:
    // 数组扩容
    void expand(int size)
    {
        int *temp = new int[size];
        for(int i = 0; i<mCur; i++)
        {
            temp[i] = mpArr[i];
        }
        mCap_ = size;
        delete []mpArr;
        mpArr = temp;
    }
private:
    int *mpArr;     // 指向数组的内存
    int mCap_;      // 数组的容量
    int mCur;       // 数组有效元素个数
};

int main()
{
    Array arr;

    srand(time(0));
    for(int i = 0; i<10; i++)
    {
        arr.push_back(rand() % 100);
    }
    arr.show();
    arr.pop_back();
    arr.show();

    arr.push_back(10);
    arr.show();

    arr.insert(0, 100);
    arr.insert(10, 200);
    arr.show();

    int pos = arr.find(100);
    if(pos != -1)
    {
        arr.erase(pos);
        arr.show();
    }

    return 0;
}