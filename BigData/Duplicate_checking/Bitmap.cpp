#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <memory>
#include <time.h>
using namespace std;

/*
    有1亿个整数，最大值不超过1亿，问都有哪些元素重复了？谁是第一个重复的？谁是第一个不重复的？
    内存限制100M

    1亿 = 100M
    哈希表：100M * 4 = 400M  400M * 2 = 800M

    位图算法
    int bitmap[100000000/32 + 1]  3.2M
*/

int main()
{
    vector<int> vec{ 12, 78, 90, 123, 8, 9, 12 };

    // 定义位图数组
    int maxv = vec[0];
    for(int i = 1; i<vec.size(); i++)
    {
        if(vec[i] > maxv)
            maxv = vec[i];
    }

    int *bitmap = new int[maxv / 32 + 1]();
    unique_ptr<int> ptr(bitmap);    // 使用智能指针管理一下bitmap，当出作用域后，智能指针自动释放指向内存，不需要我们手动delete管理内存

    // 找第一个重复出现的数字
    for(auto key : vec)
    {
        int index = key / 32;
        int offset = key % 32;
        
        // 取key对应的位的值
        if(0 == (bitmap[index] & (1 << offset)))
        {
            // 表示key没有出现过
            bitmap[index] |= (1 << offset);
        }
        else
        {
            cout << key << "是第一个重复出现的数字" << endl;
        }
    }

    return 0;
}