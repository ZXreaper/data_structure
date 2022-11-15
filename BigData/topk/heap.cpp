#include <iostream>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <unordered_map>
#include <functional>
using namespace std;

#if 0
int main()
{
    vector<int> vec;
    srand(time(NULL));
    for(int i = 0; i<1000; i++)
    {
        vec.push_back(rand() % 10000);
    }
#if 0
    // 求vec中值最小的前5个元素
    priority_queue<int> q;
    int k = 5;
    for(int i = 0; i<5; i++)
    {
        q.push(vec[i]);
    }

    for(int i = 5; i<1000; i++)
    {
        int cur = q.top();
        if(cur > vec[i])
        {
            q.pop();
            q.push(vec[i]);
        }
    }

    while(q.size())
    {
        cout << q.top() << " ";
        q.pop();
    }
    cout<<endl;
#endif
    // 求vec中值最大的前5个元素
    priority_queue<int, vector<int>, greater<int>> q;
    int k = 5;
    for(int i = 0; i<5; i++)
    {
        q.push(vec[i]);
    }

    for(int i = 5; i<1000; i++)
    {
        int cur = q.top();
        if(cur < vec[i])
        {
            q.pop();
            q.push(vec[i]);
        }
    }

    while(q.size())
    {
        cout << q.top() << " ";
        q.pop();
    }
    cout<<endl;

    return 0;
}
#endif

// 查重和top k问题综合起来
int main()
{
    vector<int> vec;
    srand(time(NULL));
    for(int i = 0; i<10000; i++)
    {
        vec.push_back(rand() % 1000);
    }
#if 0
    // 统计重复次数最小的前3个数字
    unordered_map<int, int> hashtable;
    // 需要自定义priority_queue的比较函数
    using PII = pair<int, int>;
    using Comp = function<bool(PII&, PII&)>;
    priority_queue<PII, vector<PII>, Comp> heap(
        [](PII& a, PII& b)->bool {
            return a.second < b.second;
    });
    int len = vec.size();
    for(int i = 0; i<len; i++)
    {
        hashtable[vec[i]]++;
    }
    int k = 3;
    auto it = hashtable.begin();
    for(int i = 0; i<k; i++)
    {
        heap.push(*it);
        it++;
    }
    for(; it != hashtable.end(); ++it)
    {
        if(heap.top().second > it->second)
        {
            heap.pop();
            heap.push(*it);
        }
    }
    
    while(heap.size())
    {
        cout << "key: " << heap.top().first
             << " cnt: " << heap.top().second << endl;
        heap.pop();
    }
#endif
    // 统计重复次数最大的前3个数字
    unordered_map<int, int> hashtable;
    // 需要自定义priority_queue的比较函数
    using PII = pair<int, int>;
    using Comp = function<bool(PII&, PII&)>;
    priority_queue<PII, vector<PII>, Comp> heap(
        [](PII& a, PII& b)->bool {
            return a.second > b.second;
    });
    int len = vec.size();
    for(int i = 0; i<len; i++)
    {
        hashtable[vec[i]]++;
    }
    int k = 3;
    auto it = hashtable.begin();
    for(int i = 0; i<k; i++)
    {
        heap.push(*it);
        it++;
    }
    for(; it != hashtable.end(); ++it)
    {
        if(heap.top().second < it->second)
        {
            heap.pop();
            heap.push(*it);
        }
    }
    
    while(heap.size())
    {
        cout << "key: " << heap.top().first
             << " cnt: " << heap.top().second << endl;
        heap.pop();
    }

    return 0;
}