#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 *  2020-09-29 - 排序
 *  create By liTeng
 */

#define LEFT 2 * nRootid + 1
#define RIGHT 2 * nRootid + 2

//打印
void printArr(int *arr, int nlen);
//交换
void swap(int *m, int *n);
//冒泡排序
void bubbleSort(int *arr, int nlen);
void bubbleSortDouble(int *arr, int nlen);
//选择排序
void SelectSort(int arr[], int nlen);
//插入排序
void InsertSort(int arr[], int nlen);
//计数排序
void CountSort(int arr[], int nlen);
//希尔排序
void ShellSort(int arr[], int nlen);
//快速排序
int Sort1(int arr[], int nLow, int nHigh);
int Sort(int arr[], int nLow, int nHigh);
void QuickSort(int arr[], int nLow, int nHigh);
//归并排序
void Merge(int arr[], int nLow, int nHigh);
void MergeSort(int arr[], int nLow, int nHigh);
//堆排序
void Adjust(int arr[], int nlen, int nRootid);
void HeapSort(int arr[], int nlen);
//桶排序
typedef struct node
{
    int nValue;
    struct node *pNext;
    struct node *pPre;
} Bucket;
void Buckett(Bucket *pHead);
void BucketSort(int arr[], int nlen);
//基数排序
typedef struct Node
{
    int nValue;
    struct Node *pNext;
} Radix;
void Radixx(int arr[], int nlen, int nNum, Radix **pRadix);
void RadixSort(int arr[], int nlen);
int main()
{
    int arr1[] = {410,999,550,640,671,791,800,1000};
    int arr[] = {1, 2, 33, 4, 36, 31, 30, 39, 23, 12, 35};
    // printArr(arr1, sizeof(arr1) / sizeof(int));
    RadixSort(arr1, sizeof(arr1) / sizeof(int));
    printArr(arr1, sizeof(arr1) / sizeof(int));

    return 0;
}
//-------基数排序-------------------------------------------
// 0 1 2 3 4 5 6 7 8 9
// 20 10  22    43 3  84  95 55   67   49
// 3  10   20  22  43   49 55   67  84       95
void Radixx(int arr[], int nlen, int nNum, Radix **pRadix)
{
    int nBase = 1;
    while (nNum > 1)
    {
        nBase *= 10;
        nNum--;
    }

    int i;
    Radix *pTemp;
    Radix *pNode;
    for (i = 0; i < nlen; i++)
    {
        nNum = arr[i] / nBase % 10;
        pTemp = (Radix *)malloc(sizeof(Radix));
        pTemp->nValue = arr[i];
        pTemp->pNext = NULL;

        if (pRadix[nNum] == NULL)
        {
            pRadix[nNum] = pTemp;
        }
        else
        {
            pNode = pRadix[nNum];
            while (pNode->pNext != NULL)
            {
                pNode = pNode->pNext;
            }
            pNode->pNext = pTemp;
        }
    }

    nNum = 0;
    for (i = 0; i < 10; i++)
    {
        pTemp = pRadix[i];
        while (pTemp)
        {
            arr[nNum] = pTemp->nValue;
            pTemp = pTemp->pNext;
            nNum++;
        }
    }

    for (i = 0; i < 10; i++)
    {
        pTemp = pRadix[i];
        while (pTemp)
        {
            pNode = pTemp;
            pTemp = pTemp->pNext;
            free(pNode);
            pNode = NULL;
        }
    }

    memset(pRadix, 0, sizeof(Radix *) * 10);
}
void RadixSort(int arr[], int nlen)
{
    if (arr == NULL || nlen <= 0)
        return;

    int i, nMax;
    nMax = arr[0];

    for (i = 0; i < nlen; i++)
    {
        if (arr[i] > nMax)
        {
            nMax = arr[i];
        }
    }

    int nLoopTimes = 0;
    while (nMax)
    {
        nLoopTimes++;
        nMax /= 10;
    }

    Radix **pRadix = (Radix **)malloc(sizeof(Radix *) * 10);
    memset(pRadix, 0, sizeof(Radix *) * 10);
    for (i = 1; i <= nLoopTimes; i++)
    {
        Radixx(arr, nlen, i, pRadix);
    }
    free(pRadix);
    pRadix = NULL;
}
//-------桶排序-------------------------------------------
// 平均时间复杂度：O(n + k)
// 最佳时间复杂度：O(n + k)
// 最差时间复杂度：O(n ^ 2)
// 空间复杂度：O(n * k)
// 稳定性：稳定
void Buckett(Bucket *pHead)
{
    if (pHead == NULL || pHead->pNext == NULL)
        return;
    Bucket *pSort = NULL;
    Bucket *pUnSort = NULL;

    pUnSort = pHead->pNext;
    int temp;
    while (pUnSort != NULL)
    {
        pSort = pUnSort->pPre;  //4
        temp = pUnSort->nValue; //2

        while (pSort != NULL && pSort->nValue > temp)
        {
            pSort->pNext->nValue = pSort->nValue;
            pSort = pSort->pPre;
        }
        if (pSort == NULL)
        {
            pHead->nValue = temp;
        }
        else
        {
            pSort->pNext->nValue = temp;
        }

        pUnSort = pUnSort->pNext;
    }
}
void BucketSort(int arr[], int nlen)
{
    if (arr == NULL || nlen < 0)
        return;
    int i, nMin, nMax, nMinIndex, nMaxIndex;
    nMin = arr[0];
    nMax = arr[0];
    for (i = 0; i < nlen; i++)
    {
        if (arr[i] < nMin)
            nMin = arr[i];
        if (arr[i] > nMax)
            nMax = arr[i];
    }
    printf("nMin: %d, nMax: %d\n", nMin, nMax);

    int nCount = 0;
    int nBase = 1;
    int nNum = nMin;
    while (nNum)
    {
        nCount++;
        nNum /= 10;
    }
    while (nCount)
    {
        nBase *= 10;
        nCount--;
    }
    nMinIndex = nMin / nBase;
    nMaxIndex = nMax / nBase;
    printf("nMInIndex: %d, nMaxIndex: %d\n", nMinIndex, nMaxIndex);

    Bucket **pBucket = (Bucket **)malloc(sizeof(Bucket) * (nMaxIndex - nMinIndex + 1));
    memset(pBucket, 0, sizeof(Bucket) * (nMaxIndex - nMinIndex + 1));

    Bucket *pTemp = NULL;
    for (i = 0; i < nlen; i++)
    {
        nCount = arr[i] / nBase - nMinIndex;

        pTemp = (Bucket *)malloc(sizeof(Bucket));
        pTemp->nValue = arr[i];
        pTemp->pNext = pBucket[nCount];

        if (pBucket[nCount] != NULL)
        {
            pBucket[nCount]->pPre = pTemp;
        }
        pBucket[nCount] = pTemp;
    }

    for (i = 0; i < nMaxIndex - nMinIndex + 1; i++)
    {
        Buckett(pBucket[i]);
    }

    nCount = 0;
    for (i = 0; i < nMaxIndex - nMinIndex + 1; i++)
    {
        pTemp = pBucket[i];
        while (pTemp)
        {
            arr[nCount] = pTemp->nValue;
            nCount++;
            pTemp = pTemp->pNext;
        }
    }
    Bucket *pDel = NULL;
    for (i = 0; i < nMaxIndex - nMinIndex + 1; i++)
    {
        pTemp = pBucket[i];
        while (pTemp)
        {
            pDel = pTemp;
            pTemp = pTemp->pNext;
            free(pDel);
            pDel = NULL;
        }
    }
    free(pBucket);
    pBucket = NULL;
}
//-------堆排序-------------------------------------------
// 平均时间复杂度：O(nlogn)
// 最佳时间复杂度：O(nlogn)
// 最差时间复杂度：O(nlogn)
// 稳定性：不稳定

void Adjust(int arr[], int nlen, int nRootid)
{
    while (1)
    {
        if (RIGHT < nlen)
        {
            if (arr[LEFT] < arr[RIGHT])
            {
                if (arr[RIGHT] > arr[nRootid])
                {
                    arr[RIGHT] = arr[RIGHT] ^ arr[nRootid];
                    arr[nRootid] = arr[RIGHT] ^ arr[nRootid];
                    arr[RIGHT] = arr[RIGHT] ^ arr[nRootid];

                    nRootid = RIGHT;
                    continue;
                }
                break;
            }
            else
            {
                if (arr[LEFT] > arr[nRootid])
                {
                    arr[LEFT] = arr[LEFT] ^ arr[nRootid];
                    arr[nRootid] = arr[LEFT] ^ arr[nRootid];
                    arr[LEFT] = arr[LEFT] ^ arr[nRootid];

                    nRootid = LEFT;
                    continue;
                }
                break;
            }
        }
        else if (LEFT < nlen)
        {
            if (arr[LEFT] > arr[nRootid])
            {
                arr[LEFT] = arr[LEFT] ^ arr[nRootid];
                arr[nRootid] = arr[LEFT] ^ arr[nRootid];
                arr[LEFT] = arr[LEFT] ^ arr[nRootid];

                nRootid = LEFT;
            }
            break;
        }
        else
        {
            break;
        }
    }
}
void HeapSort(int arr[], int nlen)
{
    if (arr == NULL || nlen <= 0)
        return;
    int i;
    for (i = nlen / 2 - 1; i >= 0; i--)
    {
        Adjust(arr, nlen, i);
    }
    // for (i = nlen - 1; i > 0; i--)
    // {
    //     arr[0] = arr[0] ^ arr[i];
    //     arr[i] = arr[0] ^ arr[i];
    //     arr[0] = arr[0] ^ arr[i];
    //     Adjust(arr, i, 0);
    // }
}
        //          1000                      400
        //          /  \                  999      500
        //       999   800             600  601  701  800
        //       / \   /  \          1000 
        //     600 601 701 500
        //  400
//-------归并排序-------------------------------------------
// 平均时间复杂度：O(nlogn)
// 最佳时间复杂度：O(n)
// 最差时间复杂度：O(nlogn)
// 空间复杂度：O(n)
// 排序方式：In-place
// 稳定性：稳定
void Merge(int arr[], int nLow, int nHigh)
{
    if (arr == NULL || nLow >= nHigh)
        return;

    int nBegin1, nEnd1, nBegin2, nEnd2;

    nBegin1 = nLow;
    nEnd1 = nLow + (nHigh - nLow) / 2;
    nBegin2 = nEnd1 + 1;
    nEnd2 = nHigh;

    int *pTemp = (int *)malloc(sizeof(int) * (nHigh - nLow + 1));
    int i = 0;
    while (nBegin1 <= nEnd1 && nBegin2 <= nEnd2)
    {
        if (arr[nBegin1] < arr[nBegin2])
        {
            pTemp[i] = arr[nBegin1];
            nBegin1++;
        }
        else
        {
            pTemp[i] = arr[nBegin2];
            nBegin2++;
        }
        i++;
    }
    while (nBegin1 <= nEnd1)
    {
        pTemp[i] = arr[nBegin1];
        i++;
        nBegin1++;
    }
    while (nBegin2 <= nEnd2)
    {
        pTemp[i] = arr[nBegin2];
        i++;
        nBegin2++;
    }
    for (int j = 0; j < nHigh - nLow + 1; j++)
    {
        arr[nLow + j] = pTemp[j];
    }
}
void MergeSort(int arr[], int nLow, int nHigh)
{
    if (arr == NULL || nLow >= nHigh)
        return;

    int nMid = nLow + (nHigh - nLow) / 2;
    MergeSort(arr, nLow, nMid);
    MergeSort(arr, nMid + 1, nHigh);

    Merge(arr, nLow, nHigh);
}
//-------快速排序-------------------------------------------
// 平均时间复杂度：O(NlogN)
// 最佳时间复杂度：O(NlogN)
// 最差时间复杂度：O(N^2)
// 空间复杂度：根据实现方式的不同而不同

// 区间分割
int Sort1(int arr[], int nLow, int nHigh)
{
    int nSmall;
    nSmall = nLow - 1;

    for (nLow = nLow; nLow < nHigh; nLow++)
    {
        if (arr[nLow] < arr[nHigh])
        {
            if (++nSmall != nLow)
            {
                arr[nSmall] = arr[nSmall] ^ arr[nLow];
                arr[nLow] = arr[nSmall] ^ arr[nLow];
                arr[nSmall] = arr[nSmall] ^ arr[nLow];
            }
        }
    }

    if (++nSmall != nHigh)
    {
        arr[nSmall] = arr[nSmall] ^ arr[nHigh];
        arr[nHigh] = arr[nSmall] ^ arr[nHigh];
        arr[nSmall] = arr[nSmall] ^ arr[nHigh];
    }
    return nSmall;
}
// 挖坑填补
int Sort(int arr[], int nLow, int nHigh)
{
    if (arr == NULL || nLow >= nHigh)
        return 0;

    int temp = arr[nLow]; //以此值将数组分割为两部分

    while (nLow < nHigh)
    {
        //从后往前找小的
        while (nLow < nHigh)
        {
            if (arr[nHigh] < temp)
            {
                arr[nLow] = arr[nHigh];
                nLow++;
                break;
            }
            nHigh--;
        }

        //从前往后找大的
        while (nLow < nHigh)
        {
            if (arr[nLow] > temp)
            {
                arr[nHigh] = arr[nLow];
                nHigh--;
                break;
            }
            nLow++;
        }
    }
    arr[nLow] = temp;
    return nLow;
} //
void QuickSort(int arr[], int nLow, int nHigh)
{
    if (arr == NULL || nLow >= nHigh)
        return;
    int nStandard = Sort1(arr, nLow, nHigh);
    QuickSort(arr, nLow, nStandard - 1);
    QuickSort(arr, nStandard + 1, nHigh);
}
//-------希尔排序-------------------------------------------
//分组插入，依然为有序最后一个，无序第一个
// 平均时间复杂度：O(Nlog2N)
// 最佳时间复杂度：
// 最差时间复杂度：O(N^2)
// 空间复杂度：O(1)
// 稳定性：不稳定
// 复杂性：较复杂
// 希尔排序的效率取决于增量值gap的选取，时间复杂度并不是一个定值。
void ShellSort(int arr[], int nlen)
{
    if (arr == NULL || nlen < 0)
        return;
    int i, j, k, temp, gap = nlen / 2;
    // 分组
    for (gap = nlen / 2; gap >= 1; gap /= 2)
    {
        // 各组依次遍历
        for (i = 0; i < gap; i++)
        { // 组内实行插入排序
            for (k = i + gap; k < nlen; k += gap)
            {
                j = k - gap;
                temp = arr[k];
                while (j >= i && arr[j] > temp)
                {
                    arr[j + gap] = arr[j];
                    j -= gap;
                }
                arr[j + gap] = temp;
            }
        }
    }
}
//-------计数排序-------------------------------------------
// ① 找出待排序的数组中最大和最小的元素
// ② 统计数组中每个值为i的元素出现的次数，存入数组C的第i项
// ③ 对所有的计数累加（从C中的第一个元素开始，每一项和前一项相加）
// ④ 反向填充目标数组：将每个元素i放在新数组的第C(i) 项，每放一个元素就将C(i) 减去1
// n 个 0-k 之前的整数
// 平均时间复杂度：O(n + k)
// 最佳时间复杂度：O(n + k)
// 最差时间复杂度：O(n + k)
// 空间复杂度：O(n + k)
void CountSort(int arr[], int nlen)
{
    if (arr == NULL || nlen < 0)
        return;
    int i = 0;
    int nMax = arr[0];
    int nMin = arr[0];
    for (i = 0; i < nlen; i++)
    {
        if (arr[i] < nMin)
        {
            nMin = arr[i];
        }
        if (arr[i] > nMax)
        {
            nMax = arr[i];
        }
    }
    //printf("nMax: %d, nMin: %d\n", nMax, nMin);

    int *pMark = (int *)malloc(sizeof(int) * (nMax - nMin + 1));
    memset(pMark, 0, sizeof(int) * (nMax - nMin + 1));
    //printArr(pMark, sizeof(int) * (nMax - nMin + 1));

    int nCount = 0;
    for (i = 0; i < nlen; i++)
    {
        nCount = arr[i] - nMin;
        pMark[nCount]++;
    }
    //printArr(pMark, sizeof(int) * nMax);
    int j = 0;
    for (i = 0; i < nMax - nMin + 1; i++)
    {
        while (pMark[i] > 0)
        {
            arr[j] = i + nMin;
            j++;
            pMark[i]--;
        }
    }
    free(pMark);
    pMark = NULL;
}
//-------插入排序-------------------------------------------
//从左向右的遍历过程中，在左侧构建有序序列，右侧元素依次插入左侧有序列表中
//有序、无序两个遍历
//插入的过程，即记录要插入点，找合适位置，往后挪动的过程
void InsertSort(int arr[], int nlen)
{
    if (arr == NULL || nlen < 0)
        return;
    int i, j, temp;
    //无序第一个
    for (i = 0; i < nlen; i++)
    {
        j = i - 1;     //有序最后一个
        temp = arr[i]; //记录无序第一个

        while (j >= 0 && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}
//-------选择排序-------------------------------------------
// 平均时间复杂度：O(N^2)
// 最佳时间复杂度：O(N^2)
// 最差时间复杂度：O(N^2)
// 空间复杂度：O(1)
// 排序方式：In-place
// 稳定性：不稳定
void SelectSort(int arr[], int nlen)
{
    if (arr == NULL || nlen < 0)
        return;
    int nMin = 0;
    for (int i = 0; i < nlen - 1; i++)
    {
        nMin = i;
        for (int j = i; j < nlen; j++)
        {
            if (arr[nMin] > arr[j])
            {
                arr[nMin] = arr[nMin] ^ arr[j];
                arr[j] = arr[nMin] ^ arr[j];
                arr[nMin] = arr[nMin] ^ arr[j];
            }
        }
        // nMin = i;
        // for (int j = i; j < nlen; j++)
        // {
        //     if (arr[j] < arr[nMin])
        //     {
        //         nMin = j;
        //     }
        // }
        // //printf("最小值为:%d,对应索引为：%d\n", arr[nMin], nMin);
        // if (i != nMin)
        // {
        //     swap(&arr[nMin], &arr[i]);
        // }
    }
}
//-------冒泡排序-------------------------------------------
//升序排序，i 每走一遍，就会把一个最大值的放在最后端，降序亦然
// 平均时间复杂度：O(N^2)
// 最佳时间复杂度：O(N)
// 最差时间复杂度：O(N^2)
// 空间复杂度：O(1)
// 排序方式：In-place
// 稳定性：稳定
void bubbleSort(int *arr, int nlen)
{
    if (arr == NULL || nlen < 0)
        return;
    int i, j;
    int temp = 0;
    int flag = 0;
    int n = 0;
    for (i = 0; i < nlen - 1; i++)
    {
        flag = 0;
        //优化1: j < legnth-i-1; 内部循环不用遍历 nlen-1;因为每一次 i+1均表示已经有一个在了合适的位置上
        for (j = 0; j < nlen - i - 1; j++) 
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                //优化3:记录此刻的值，j+1往后的数组已经为有序数组
                flag = j+1;
            }
            n++;
        }
        //优化2: 如果值没变,说明该数组已经是有序的数组了，排序结束
        if (flag == 0)
        {
            break;
        }
        printf("共比较%d次\n", flag);
        printArr(arr, 10);
        i = nlen - flag -1; // 10-5= 5   =0123 4 5 6789
    }
    printf("共比较%d次\n", n);
    return;
}
//双向冒泡排序
void bubbleSortDouble(int *arr, int nlen)
{
    if (arr == NULL || nlen < 0)
        return;

    int low = 0;
    int high = nlen - 1;

    while (low < high)
    {
        // 大的从左往右走，走到最右边
        for (int i = low; i < high; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(&arr[i], &arr[i + 1]);
            }
        }
        printArr(arr,10);
        high--;
        // 小的从右向左走，走到最左边
        for (int j = high; j > low; j--)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(&arr[j], &arr[j - 1]);
            }
        }
        printArr(arr,10);
        low++;
    }
}
//交换
void swap(int *m, int *n)
{
    int temp = *m;
    *m = *n;
    *n = temp;
}
//数组打印
void printArr(int *arr, int nlen)
{
    if (arr == NULL)
        return;

    for (int i = 0; i < nlen; i++)
    {
        printf("%d  ", arr[i]);
    }
    printf("\n");
}
