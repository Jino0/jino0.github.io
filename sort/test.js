let arr = [373, 425, 119, 712, 320, 229, 904, 666,33];
var QuickSort = function (arr) {

    if (arr.length < 0) return;
    let i, j, temp;
    //无序第一个
    for (i = 1; i < arr.length; i++)
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
console.log(QuickSort(arr));
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
//-------希尔排序-----