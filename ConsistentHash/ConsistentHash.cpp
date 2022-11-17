#include <iostream>
#include <string>
#include <set>
#include <list>
#include <map>
#include "md5.h"
using namespace std;

// 一致性哈希环的取值类型
using uint = unsigned int;

class PhysicalHost; // 前置声明物理节点主机类型

// 虚拟节点
class VirtualHost
{
public:
    VirtualHost(string ip, PhysicalHost *p)
        : ip_(ip)
        , physicalHost_(p)
    {
        md5_ = ::getMD5(ip_.c_str());
    }

    bool operator<(const VirtualHost& host) const
    {
        return md5_ < host.md5_;
    }

    bool operator==(const VirtualHost& host) const
    {
        return ip_ == host.ip_;
    }

    uint getMD5() const
    {
        return md5_;
    }

    const PhysicalHost* getPhysicalHost() const
    {
        return physicalHost_;
    }
 
private:
    string ip_;     // 虚拟节点ip信息
    uint md5_;       // 虚拟节点在一致性哈希环上的位置
    PhysicalHost* physicalHost_;    // 虚拟节点所属的物理节点
};

// 物理节点
class PhysicalHost
{
public:
    PhysicalHost(string ip, int vnumber)
        : ip_(ip)
    {
        for(int i = 0; i<vnumber; i++)
        {
            // 虚拟节点需要一个ip，还需要记录它属于哪个物理节点
            virtualHosts_.emplace_back(
                ip + "#" + ::to_string(i),
                this
            );
        }
    }

    string getIP() const
    {
        return ip_;
    }

    const list<VirtualHost>& getVirtualHosts() const
    {
        return virtualHosts_;
    }
private:
    string ip_;                         // 物理机器的ip地址
    list<VirtualHost> virtualHosts_;    // 存储虚拟节点列表
};

// 一致性哈希
class ConsistentHash
{
public:
    // 在一致性哈希环上添加物理主机的虚拟节点
    void addHost(PhysicalHost &host)
    {
        // 获取物理主机所有的虚拟节点列表
        auto list = host.getVirtualHosts();
        for(auto host : list)
        {
            hashCircle_.insert(host);
        }
    }

    // 在一致性哈希环上删除物理主机的虚拟节点
    void delHost(PhysicalHost &host)
    {
        // 获取物理主机所有的虚拟节点列表
        auto list = host.getVirtualHosts();
        for(auto host : list)
        {
            // find通过==号运算符进行比较，因此VirtualHost类需要提供==号运算符的重载函数
            auto it = hashCircle_.find(host);
            if(it != hashCircle_.end())
            {
                // 在一致性哈希环上删除所有物理主机对应的虚拟节点
                hashCircle_.erase(it);
            }
        }
    }

    // 返回负载的真实物理节点的IP信息
    string getHost(string clientip) const
    {
        uint md5 = getMD5(clientip.c_str());
        for(auto vhost : hashCircle_)
        {
            if(vhost.getMD5() > md5)
            {
                return vhost.getPhysicalHost()->getIP();
            }
        }
        // 映射从0开始遇见的第一个虚拟节点
        return hashCircle_.begin()->getPhysicalHost()->getIP();
    }

private:
    set<VirtualHost> hashCircle_;   // 一致性哈希环
};

void showConsistentHash(ConsistentHash& chash);

int main()
{
    // 测试一致性哈希算法的功能
    PhysicalHost host1("10.117.124.10", 200);
    PhysicalHost host2("10.117.124.20", 200);
    PhysicalHost host3("10.117.124.30", 200);

    ConsistentHash chash;
    chash.addHost(host1);
    chash.addHost(host2);
    chash.addHost(host3);

    showConsistentHash(chash);

    // 模拟host1有故障，观察一致性哈希运算的容灾
    chash.delHost(host1);

    showConsistentHash(chash);

    return 0;
}

void showConsistentHash(ConsistentHash& chash)
{
    list<string> iplists {
        "192.168.1.123",
        "192.168.1.12",
        "192.168.1.13",
        "192.168.1.23",
        "192.168.1.54",
        "192.168.1.89",
        "192.168.1.21",
        "192.168.1.27",
        "192.168.1.49",
        "192.168.1.145",
        "192.168.2.34",
        "192.168.6.78",
        "192.168.2.90",
        "192.168.4.5"
    };

    // 统计用的
    map<string, list<string>> logMap; 

    for(auto clientip : iplists)
    {
        string host = chash.getHost(clientip);
        logMap[host].emplace_back(clientip);
    }

    for(auto pair : logMap)
    {
        cout << "物理主机：" << pair.first << endl;
        cout << "映射客户端的数量" << pair.second.size() << endl;
        for(auto ip : pair.second)
        {
            cout<< ip << endl;
        }

        cout<< "-------------------------------" << endl;
    }
    cout<<endl;
}