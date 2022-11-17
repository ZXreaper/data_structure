#include "md5.h"
#include <iostream>
using namespace std;

int main()
{
    cout << MD5("hello world!") << endl;
    cout << getMD5("hello world") << endl;
    return 0;
}