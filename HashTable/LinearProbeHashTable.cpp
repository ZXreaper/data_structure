#include <iostream>
using namespace std;

// 桶的状态
enum State
{
    STATE_UNUSE, // 从未使用过的桶
    STATE_USING, // 正在使用的桶
    STATE_DEL,   // 使用过但被删除了的桶
};

// 桶的类型
struct Bucket
{
    Bucket(int key = 0, State state = State::STATE_UNUSE)
        : key_(key)
        , state_(state)
    {}

    int key_;       // 存储的数据
    State state_;   // 桶的当前状态
};

// 线性探测哈希表类型
class HashTable
{
public:
    HashTable(int size = primes_[0], double loadFactor = 0.75)
        : useBucketNum_(0)
        , loadFactor_(loadFactor)
        , primeIdx_(0)
        {
            // 把用户传入的size调整到最近的比它大的素数上
            if(size != primes_[0])
            {
                for(; primeIdx_ < PRIME_SIZE; primeIdx_++)
                {
                    if(primes_[primeIdx_] > size)
                        break;
                }
                // 用户传入的size值过大，已经超过了素数表中最大的值了，调整到最后一个素数
                if(primeIdx_ == PRIME_SIZE)
                {
                    primeIdx_--;
                }
            }
            tableSize_ = primes_[primeIdx_];
            table_ = new Bucket[tableSize_];
        }

        ~HashTable()
        {
            delete[] table_;
            table_ = nullptr;
        }

public:
    // 插入元素 : 没有去重，可能有多个相同值的元素
    bool insert(int key)
    {
        // 考虑扩容
        double factor = useBucketNum_*1.0 / tableSize_;
        cout<< "factor: " << factor << endl;
        if(factor > loadFactor_)
        {
            // 哈希表扩容
            expand();
        }

        int idx = key % tableSize_;
        int i = idx;
        do
        {
            if(table_[i].state_ != State::STATE_USING)
            {
                table_[i].state_ = State::STATE_USING;
                table_[i].key_ = key;
                useBucketNum_++;
                return true;
            }
            i = (i + 1) % tableSize_;
        } while (i != idx);

        return false; // 不可能走到
    }

    // 删除元素：所有的key值都需要被删掉，因为可能有重复的元素
    bool erase(int key)
    {
        int idx = key % tableSize_;
        int i = idx;
        do
        {
            if(table_[i].state_ == State::STATE_USING && table_[i].key_ == key)
            {
                table_[i].state_ = State::STATE_DEL;
                useBucketNum_--;
            }
            i = (i+1) % tableSize_;
        } while (i != idx && table_[i].state_ != State::STATE_UNUSE);

        return true;
    }

    // 查询
    bool find(int key)
    {
        int idx = key % tableSize_;
        int i = idx;
        do
        {
            if(table_[i].state_ == State::STATE_USING && table_[i].key_ == key)
            {
                return true;
            }
            i = (i+1) % tableSize_;
        } while (i != idx && table_[i].state_ != State::STATE_UNUSE);

        return false;
    }

private:
    Bucket* table_;     // 指向动态开辟的哈希表
    int tableSize_;     // 哈希表当前的长度
    int useBucketNum_;  // 已经使用的桶的个数
    double loadFactor_; // 哈希表的装载因子
    
    static const int PRIME_SIZE = 10;      // 素数表的大小
    static int primes_[PRIME_SIZE];        // 素数表
    int primeIdx_;      // 当前使用的素数下标

private:
    // 扩容操作
    void expand()
    {
        primeIdx_++;
        if(primeIdx_ == PRIME_SIZE)
        {
            throw "HashTable is too large! Can't expand anymore!";
        }

        Bucket* tmp = new Bucket[primes_[primeIdx_]];
        
        // 老哈希表的元素重新哈希
        for(int i = 0; i<tableSize_; i++)
        {
            if(table_[i].state_ == State::STATE_USING)
            {
                int idx = table_[i].key_ % primes_[primeIdx_];
                int k = idx;
                do
                {
                    if(tmp[k].state_ != State::STATE_USING)
                    {
                        tmp[k].state_ = State::STATE_USING;
                        tmp[k].key_ = table_[i].key_;
                        break;
                    }
                    k = (k + 1) % primes_[primeIdx_];
                } while (k != idx);
                
            }
        }
        delete[] table_;
        table_ = tmp;
        tableSize_ = primes_[primeIdx_];
    }
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

    cout<<hashtbale.find(14)<<endl;
    hashtbale.erase(14);
    cout<<hashtbale.find(14)<<endl;

    return 0;
}