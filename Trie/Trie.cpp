#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
using namespace std;

// Trie字典树
class TrieTree
{
public:
    TrieTree()
    {
        root_ = new TrieNode('\0', 0);
    }

    ~TrieTree()
    {
        queue<TrieNode*> que;
        que.push(root_);
        while(que.size())
        {
            TrieNode* front = que.front();
            que.pop();
            for(auto &[k, v] : front->nodeMap_)
            {
                que.push(v);
            }
            // 释放当前节点资源
            delete front;
        }
    }

    // 添加单词
    void add(const string& word)
    {
        TrieNode* cur = root_;

        for(int i = 0; i<word.size(); i++)
        {
            auto ChildIt = cur->nodeMap_.find(word[i]);
            if(ChildIt == cur->nodeMap_.end())
            {
                // 相应字符的节点没有，创建它
                TrieNode* child = new TrieNode(word[i], 0);
                cur->nodeMap_.emplace(word[i], child);
                cur = child;
            }
            else
            {
                // 相应字符的节点已经存在，移动cur指向对应的字符节点
                cur = ChildIt->second;
            }
        }
        // cur指向了word单词的最后一个节点
        cur->freqs_++;
    }

    // 删除单词
    void remove(const string& word)
    {
        TrieNode* cur = root_;
        TrieNode* del = root_;  // 从哪个节点开始删除
        char delch = word[0];   // 删除节点中的哪个字符
        
        // 寻找看要删除的单词是否存在
        for(int i = 0; i<word.size(); i++)
        {
            auto childIt = cur->nodeMap_.find(word[i]);
            if(childIt == cur->nodeMap_.end())
            {
                return ;
            }

            // 如果在寻找的过程中发现路径上还存在别的单词（即要删除的词中包含了一个更短的词，这个更短的词所含的部分不应该被删除）
            if(cur->freqs_ > 0 || cur->nodeMap_.size() > 1)
            {
                del = cur;
                delch = word[i];
            }

            // cur移动到子节点
            cur = childIt->second;
        }
        // cur指向了末尾字符节点；word单词存在
        if(cur->nodeMap_.empty())
        {
            // 开始删除
            TrieNode* child = del->nodeMap_[delch];
            del->nodeMap_.erase(delch);

            queue<TrieNode*> que;
            que.push(child);
            while(que.size())
            {
                TrieNode* front = que.front();
                que.pop();
                for(auto &[k, v] : front->nodeMap_)
                {
                    que.push(v);
                }
                // 释放当前节点资源
                delete front;
            }
        }
        else
        {
            // 当前单词末尾字符后面还有字符节点，不做任何节点删除操作
            cur->freqs_ = 0;
        }
    }

    // 查询单词
    int query(const string& word)
    {
        TrieNode* cur = root_;
        for(int i = 0; i<word.size(); i++)
        {
            auto childIt = cur->nodeMap_.find(word[i]);
            if(childIt == cur->nodeMap_.end())
            {
                return 0;
            }
            else
            {
                cur = childIt->second;
            }
        }
        return cur->freqs_;
    }

    // 前序遍历字典树。应用场景：串排序方面，输出按照字典序排序后的串。
    void preOrder()
    {
        string word;
        vector<string> wordList;
        preOrder(root_, word, wordList);
        for(auto word : wordList)
        {
            cout << word << " ";
        }
        cout << endl;
    }

    // 串的前缀搜索
    vector<string> queryPrefix(const string& prefix)
    {
        TrieNode* cur = root_;
        for(int i = 0; i<prefix.size(); i++)
        {
            auto childIt = cur->nodeMap_.find(prefix[i]);
            if(childIt == cur->nodeMap_.end())
            {
                return {};
            }
            cur = childIt->second;
        }
        // cur指向了前缀的最后一个字符节点了
        vector<string> wordList;
        preOrder(cur, prefix, wordList);
        return wordList;
    }

private:
    // 节点类型定义
    struct TrieNode
    {
        TrieNode(char ch, int freqs)
            : ch_(ch)
            , freqs_(freqs)
        {}

        char ch_;                           // 节点存储的字符数据
        int freqs_;                         // 单词的末尾字符存储单词的数量（频率）
        map<char, TrieNode*> nodeMap_;      // 存储孩子节点字符数据和节点指针的对应关系
    };

private:
    void preOrder(TrieNode* root, string word, vector<string>& wordList)
    {
        if(root->freqs_ > 0)
        {
            wordList.emplace_back(word);
        }
        for(auto &[k, v] : root->nodeMap_)
        {
            preOrder(v, word+k, wordList);
        }
    }

private:
    TrieNode* root_;
};

int main()
{
    TrieTree trie;
    trie.add("hello");
    trie.add("hello");
    trie.add("helloo");
    trie.add("hel");
    trie.add("hel");
    trie.add("china");
    trie.add("ch");
    trie.add("ch");
    trie.add("heword");
    trie.add("hellw");
    trie.remove("hellw");
    trie.remove("hello");
    cout << trie.query("hello") << endl;
    cout << trie.query("helloo") << endl;
    cout << trie.query("hel") << endl;
    cout << trie.query("china") << endl;
    cout << trie.query("ch") << endl;
    cout << trie.query("hellw") << endl;

    cout << "--------------------------" << endl;
    trie.preOrder();

    cout << "--------------------------" << endl;

    vector<string> words = trie.queryPrefix("he");
    for(auto word : words)
    {
        cout << word << " " << endl;
    }    
    cout<<endl;
    return 0;
}