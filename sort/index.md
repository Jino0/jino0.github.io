# 排序

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
| 插入排序 |              |              |              |          |          |       |
| 插入排序 |              |              |              |          |          |       |

// 平均时间复杂度：O(Nlog2N)
// 最佳时间复杂度：
// 最差时间复杂度：O(N^2)
// 空间复杂度：O(1)
// 稳定性：不稳定
// 复杂性：较复杂
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
