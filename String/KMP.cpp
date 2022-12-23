#include <iostream>
#include <string>
#include <memory>
using namespace std;

int* getnext(string s)
{
    int* next = new int[s.size()];
    int j = 0;      // j用来遍历子串
    int k = -1;     // k表示公共前缀的长度
    next[j] = k;
    int len = s.size();

    while(j < len - 1)
    {
        if((k == -1) || (s[j] == s[k]))
         {
            j++, k++;
            if(s[k] == s[j])
            {
                // kmp算法的优化
                next[j] = next[k];
            }
            else
            {
                next[j] = k;
            }
        }
        else
        {
            k = next[k];    // 做k值回溯，继续找最长的公共前缀和
        }
    }
    return next;
}

int KMP(string s, string t)
{
    int* next = getnext(t);

    cout << t << " : ";
    for(int i = 0; i<t.size(); i++)
    {
        cout << next[i] << " ";
    }
    cout<<endl;

    unique_ptr<int> ptr(next);   // 相当于加上了delete操作
    int i = 0, j = 0, len_s = s.size(), len_t = t.size();
    while(i<len_s && j<len_t)
    {
        if((j == -1) || (s[i] == t[j])) {
            i++, j++;
        }
        else {
            // KMP的算法核心就是i不回退，只回退j
            j = next[j];
        }
    }
    if(j == len_t) return i-j;
    return -1;
}

int main()
{
    string s = "ABCDCABDEFG";
    string t = "ABCABCAABCABCAA";
    
    int pos = KMP(s, t);  // 找到了返回其实位置，否则返回-1
    cout << pos << endl;
    return 0;
}