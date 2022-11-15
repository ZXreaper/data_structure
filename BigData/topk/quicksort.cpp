#include <iostream>
using namespace std;

// 快排分割
int Partition(int arr[], int begin, int end)
{
    int val = arr[begin];
    int i = begin, j = end;
    while(i<j)
    {
        // 从右往左找第一个小于基准数的，把它赋给i
        while(i<j && arr[j] > val)
            j--;
        if(i<j)
        {
            arr[i] = arr[j];
            i++;
        }
        // 从左往右找第一个大于基准数的，把它赋给j
        while(i<j && arr[i] < val)
            i++;
        if(i<j)
        {
            arr[j] = arr[i];
            j--;
        }
    }

    arr[i] = val;
    return i;
}

// 注意k是下标
void SelectTopK(int arr[], int begin, int end, int k)
{
    int pos = Partition(arr, begin, end);
    if(pos == k-1)
        return ;
    else if(pos > k-1)
    {
        SelectTopK(arr, begin, pos-1, k);
    }
    else
    {
        SelectTopK(arr, pos+1, end, k);
    }
}

int main()
{
    int arr[] = {64, 45, 52, 80, 66, 68, 0, 2, 18, 75};
    int size = sizeof arr / sizeof arr[0];
    
    // 求值最小的前3个元素
    SelectTopK(arr, 0, size-1, 3);

    for(int i = 0; i<3; i++)
    {
        cout << arr[i] << " ";
    }
    cout<<endl;
    return 0;
}