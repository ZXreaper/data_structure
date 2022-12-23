#include <iostream>
#include <string>
using namespace std;

int BF(string s, string t)
{
    int i = 0, j = 0, len_s = s.size(), len_t = t.size();
    while(i<len_s && j<len_t)
    {
        if(s[i] == t[j]) i++, j++;
        else {
            i = i - j + 1;
            j = 0;
        }
    }
    if(j == len_t) return i-j;
    return -1;
}

int main()
{
    string s = "ABCDCABDEFG";
    string t = "ABX";
    
    int pos = BF(s, t);  // 找到了返回其实位置，否则返回-1
    cout << pos << endl;
    return 0;
}