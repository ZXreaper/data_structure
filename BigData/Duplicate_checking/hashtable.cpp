#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <time.h>
using namespace std;

int main()
{
    vector<int> vec;
    srand(time(NULL));
    for(int i = 0; i<10000; i++)
    {
        vec.push_back(rand() % 10000);
    }
    // 找第一个重复出现的数字
    unordered_set<int> s1;
    for(auto key : vec)
    {
        auto it = s1.find(key);
        if(it == s1.end())
        {
            s1.insert(key);
        }
        else
        {
            cout<< "key: " << key << endl;
            break;
        }
    }

    // 统计重复出现数字的个数
    unordered_map<int, int> hashtable;
    for(auto key : vec)
    {
        hashtable[key]++;
    }
    for(auto &[k,v] : hashtable)
    {
        if(v > 1)
        {
            cout<< "key: " << k << " " << v << endl;
        }
    }

    // 一组数据有些数字是重复的，把重复的数字过滤掉，每个数字只出现一次
    unordered_set<int> s1;
    for(auto key : vec)
    {
        s1.emplace(key);
    }

    // 让你找出第一个没有重复出现过的字符
    string src = "ajdfijadifjj";
    unordered_map<char, int> m;
    for(char c : src)
    {
        m[c]++;
    }
    for(auto &[k, v] : m)
    {
        if(v > 1)
        {
            cout<< k << endl;
            return 0;
        }
    }
    cout<< "没有重复的字符！"<<endl;

    return 0;
}