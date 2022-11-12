#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

// 链式哈希表
class HashTable
{
public:
    HashTable(int size = 0, double loadFactor = 0.75)
        : useBucketNum_(0)
        , loadFactor_(loadFactor)
        , primeIdx_(0)
    {
        if(size != primes_[0])
        {
            for(; primeIdx_ < PRIME_SIZE; primeIdx_++)
            {
                if(primes_[primeIdx_] >= size)
                    break;
            }
            if(primeIdx_ == PRIME_SIZE)
            {
                primeIdx_--;
            }
        }
        table_.resize(primes_[primeIdx_]);
    }
    // 析构函数不用写，我们没有手动的增加内存

public:
    // 增加元素：不能重复插入key
    void insert(int key)
    {
        // 判断扩容
        double factor = useBucketNum_ * 1.0 / table_.size();
        cout<< "factor : " << factor <<endl;
        if(factor > loadFactor_)
        {
            expand();
        }

        int idx = key % table_.size();
        if(table_[idx].empty())
        {
            useBucketNum_++;
            table_[idx].emplace_back(key);
        }
        else
        {
            // 需要先看一下桶里面有没有当前值的元素
            // 使用全局的范型算法，而不是调用自己的成员方法find
            auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
            if(it == table_[idx].end())
            {
                // key不存在
                table_[idx].emplace_front(key);
            }
        }
    }

    // 删除元素
    void erase(int key)
    {
        int idx = key % table_.size();
        auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
        if(it != table_[idx].end())
        {
            table_[idx].erase(it);
            if(table_[idx].empty()) 
            {
                useBucketNum_--;
            }
        }
    }

    // 搜索元素
    bool find(int key)
    {
        int idx = key % table_.size();
        auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
        return it != table_[idx].end();
    }

private:
    void expand()
    {
        if(primeIdx_+1 == PRIME_SIZE)
        {
            throw "HashTable can't expand anymore!";
        }

        primeIdx_++;
        // useBucketNum会发生变化，需要重新计算桶的使用个数
        useBucketNum_ = 0;

        vector<list<int>> oldTable;
        // swap的效率会不会很低？？？ 实际上当两个容器使用的空间配置器allocator是一样的时候，那么直接交换来那个容器的
        // 成员变量即可，不会涉及到内存的开辟和拷贝，效率高！
        table_.swap(oldTable);
        table_.resize(primes_[primeIdx_]);
        
        for(auto lis : oldTable)
        {
            for(auto key : lis)
            {
                int idx = key % primes_[primeIdx_];
                if(table_[idx].empty())
                {
                    useBucketNum_++;
                }
                table_[idx].emplace_front(key);
            }
        }
    }

private:
    vector<list<int>> table_;   // 哈希表的数据结构
    int useBucketNum_;          // 记录桶的个数
    double loadFactor_;         // 记录哈希表的装载因子

    static const int PRIME_SIZE = 10;      // 素数表的大小
    static int primes_[PRIME_SIZE];        // 素数表
    int primeIdx_;      // 当前使用的素数下标
};

int HashTable::primes_[PRIME_SIZE] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

int main()
{
    HashTable hashtbale;
    hashtbale.insert(21);
    hashtbale.insert(32);
    hashtbale.insert(14);
    hashtbale.insert(15);
    hashtbale.insert(16);   
    hashtbale.insert(17); 

    cout<<hashtbale.find(14)<<endl;
    hashtbale.erase(14);
    cout<<hashtbale.find(14)<<endl;
    return 0;
}