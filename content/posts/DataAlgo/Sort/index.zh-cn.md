---
title: "十大经典排序"
subtitle: ""
date: 2022-08-30T01:20:20+08:00
lastmod: 2022-08-31T14:57:36+08:00
draft: false
authors: []
description: ""

tags: ["Sort"]
categories: ["algorithm"]
series: []

hiddenFromHomePage: false
hiddenFromSearch: false

featuredImage: "pexels-kevin-bidwell.jpeg"
featuredImagePreview: "pexels-kevin-bidwell.jpeg"

toc:
  enable: true
math:
  enable: false
lightgallery: false
license: ""
---
常见的排序算法
<!--more-->
各种性能总结
| 方法    | 平均时间复杂度  | 最佳时间复杂度 | 最差时间复杂度 | 空间复杂度 | 排序方式  | 稳定性 
| :----:  |    :----:    | :----:       | :----:      | :----:    | :-----: | :----: |
| 冒泡排序 |   O(N^2)     |  O(N)        |    O(N^2)    |   O(1)   | In-place |  YES  |
| 插入排序 |              |              |              |          |          |       |
| 选择排序 |              |              |              |          |          |       |
| 计数排序 |O(n + k)      |   O(n + k)   |   O(n + k)   |O(n + k)  |          |       |
| 希尔排序 |O(Nlog2N)     |              |   O(N^2)     |   O(1)   |          | NO    |
| 快速排序 | O(NlogN)     |   O(NlogN)   |    O(N^2)    |          |          |       |
|  堆排序  |              |              |              |          |          |       |
|  桶排序  | O(n + k)     |  O(n + k)    |  O(n ^ 2)    | O(n * k) |          | 稳定   |
| 基数排序 |              |              |              |          |          |       |

## 冒泡排序
注意三个 **优化点**

```js
let arr = [3, 5, 1, 7, 0, 2, 4, 6];
var bubbleSort = function (arr) {
    let flag = 0;
    for (let i = 0; i < arr.length-1; i++) {
        //优化1: j < legnth-i-1; 内部循环不用遍历 nlen-1;因为每一次 i+1均表示已经有一个在了合适的位置上
        for (let j = 0; j < arr.length - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                let temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
            //优化3:记录此刻的值，j+1往后的数组已经为有序数组
            flag = j+1;
        }
        //优化2: 如果值没变,说明该数组已经是有序的数组了，排序结束
        if (flag == 0)
        {
            break;
        }
        if (flag) {
            i = arr.length - flag -1;
        }
    }
    return arr;
}
console.log(bubbleSort(arr));
```
### 双向冒泡排序
```js
let arr = [3, 5, 1, 7, 0, 2, 4, 6];
var bubbleSortDouble = function (arr) {
    if (arr.length < 0)
        return;

    let low = 0, high = arr.length - 1;
    while (low < high) {
        // 大的从左往右走，走到最右边
        for (let i = low; i < high; i++) {
            if (arr[i] > arr[i + 1]) {
                let temp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = temp;
            }
        }

        high--;
        // 小的从右向左走，走到最左边
        for (let j = high; j > low; j--) {
            if (arr[j] < arr[j - 1]) {
                let temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
        }
        low++;
    }
    return arr;
}
console.log(bubbleSortDouble(arr));
```

## 选择排序

```js
let arr = [3, 5, 1, 7, 0, 2, 4, 6];
var SelectSort = function (arr) {
    if (arr.length < 0) return;
    let nMin = 0;
    for (let i = 0; i < arr.length - 1; i++)
    {
        nMin = i;
        for (let j = i; j < arr.length; j++)
        {
            if (arr[nMin] > arr[j])
            {
                arr[nMin] = arr[nMin] ^ arr[j];
                arr[j] = arr[nMin] ^ arr[j];
                arr[nMin] = arr[nMin] ^ arr[j];
            }
        }
        // nMin = i;
        // for (let j = i; j < arr.length; j++)
        // {
        //     if (arr[j] < arr[nMin])
        //     {
        //         nMin = j;
        //     }
        // }
        // //prletf("最小值为:%d,对应索引为：%d\n", arr[nMin], nMin);
        // if (i != nMin)
        // {
        //     swap(&arr[nMin], &arr[i]);
        // }
    }
    return arr;
}
console.log(SelectSort(arr));
```

## 插入排序

```js
//-------插入排序-------------------------------------------
//从左向右的遍历过程中，在左侧构建有序序列，右侧元素依次插入左侧有序列表中
//有序、无序两个遍历
//插入的过程，即记录要插入点，找合适位置，往后挪动的过程
let arr = [3, 5, 1, 7, 0, 2, 4, 6];
var InsertSort = function (arr) {

    if (arr.length < 0) return;
    let i, j, temp;
    //无序第一个
    for (i = 0; i < arr.length; i++)
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

    return arr;
}
console.log(InsertSort(arr));
```

## 计数排序
```js
① 找出待排序的数组中最大和最小的元素
② 统计数组中每个值为i的元素出现的次数，存入数组C的第i项
③ 对所有的计数累加（从C中的第一个元素开始，每一项和前一项相加）
④ 反向填充目标数组：将每个元素i放在新数组的第C(i) 项，每放一个元素就将C(i) 减去1
```
```js
let arr = [3, 5, 1, 7, 0, 2, 4, 6,2];
var CountSort = function (arr) {
    if (arr.length < 0) return;

    let nMin = 0, nMax = 0;
    for (let i = 0; i < arr.length; i++) {
        if (arr[i] < nMin) {
            nMin = arr[i];
        }
        if (arr[i] > nMax) {
            nMax = arr[i];
        }
    }
    let nMaxMin = nMax - nMin + 1;

    let pMark = new Array(nMaxMin).fill(0);
    
    for (let i = 0; i < arr.length; i++) {
        pMark[arr[i] - nMin]++;
    }
    
    let j = 0;
    for (let i = 0; i < nMaxMin; i++) {
        while (pMark[i] > 0) {
            arr[j] = i + nMin;
            j = j + 1;
            pMark[i]--;
        }
    }
    return arr;
}
console.log(CountSort(arr));
```


## 希尔排序

```js
//-------希尔排序-------------------------------------------
//分组插入，依然为有序最后一个，无序第一个
// 希尔排序的效率取决于增量值gap的选取，时间复杂度并不是一个定值。
let arr = [3, 5, 1, 7, 0, 2, 4, 6, 2];
// let arr = [12, 4, 10, 4, 2, 9, 7];
// let arr = [900,200,300,401,602,801];
var ShellSort = function (arr) {
    if (arr.length < 0) return;
    let i, j, k, temp, gap = arr.length / 2;
    // 分组
    for (gap = Math.floor(arr.length / 2); gap >= 1; gap = Math.floor(gap/ 2)) {
        console.log(gap)
        // 各组依次遍历
        for (i = 0; i < gap; i++) { // 组内实行插入排序
            for (k = i + gap; k < arr.length; k += gap) {
                j = k - gap;
                temp = arr[k];
                while (j >= i && arr[j] > temp) {
                    arr[j + gap] = arr[j];
                    j -= gap;
                }
                arr[j + gap] = temp;
            }
        }
    }
    return arr;
}
console.log(ShellSort(arr));
```

## 快速排序
### 区间分割
```cpp
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
void QuickSort(int arr[], int nLow, int nHigh)
{
    if (arr == NULL || nLow >= nHigh)
        return;
    int nStandard = Sort1(arr, nLow, nHigh);
    QuickSort(arr, nLow, nStandard - 1);
    QuickSort(arr, nStandard + 1, nHigh);
}
```
### 挖坑填补
```cpp
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
```

## 归并排序
```cpp
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
```

## 堆排序
```js
建堆的过程，只能保证最大的再最上面，可以保证所有的父节点均比子节点大，但是不能保证子节点之间的大小。
所以需要仅一步操作，每次均取最大值即可。
```
```cpp
#define LEFT 2 * nRootid + 1
#define RIGHT 2 * nRootid + 2

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

    for (i = nlen - 1; i > 0; i--)
    {
        arr[0] = arr[0] ^ arr[i];
        arr[i] = arr[0] ^ arr[i];
        arr[0] = arr[0] ^ arr[i];
        Adjust(arr, i, 0);
    }
}
```









## 桶排序

```cpp

typedef struct node
{
    int nValue;
    struct node *pNext;
    struct node *pPre;
} Bucket;

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
```

## 基数排序

```cpp
typedef struct Node
{
    int nValue;
    struct Node *pNext;
} Radix;

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
```