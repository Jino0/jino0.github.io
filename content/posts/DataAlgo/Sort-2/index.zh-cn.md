---
title: "排序算法题"
subtitle: ""
date: 2022-08-31T15:08:36+08:00
lastmod: 2022-09-01T00:40:23+08:00
draft: false
authors: []
description: ""

tags: ["Sort"]
categories: ["algorithm"]
series: []

hiddenFromHomePage: false
hiddenFromSearch: false

featuredImage: "pexels-lad-fury.jpeg"
featuredImagePreview: "pexels-lad-fury.jpeg"

toc:
  enable: true
math:
  enable: false
lightgallery: false
license: ""
---
常见的排序算法相关题。
<!--more-->


## 用最少数量的箭引爆气球
<!-- 【排序算法】 -->
[【LeetCode 451】最少数量的箭（中等）](https://leetcode-cn.com/problems/minimum-number-of-arrows-to-burst-balloons/)
```js
有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 points ，其中 points[i] = [xstart, xend] 表示水平直径在
 xstart 和 xend 之间的气球。你不知道气球的确切 y 坐标。

一支弓箭可以沿着 x 轴从不同点 完全垂直 地射出。在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足
`xstart ≤ x ≤ xend`，则该气球会被引爆。可以射出的弓箭的数量没有限制。弓箭一旦被射出之后，可以无限地前进。

给你一个数组 points ，返回引爆所有气球所必须射出的 最小弓箭数 。
 
示例 1：
输入：points = [[10,16],[2,8],[1,6],[7,12]]
输出：2
解释：气球可以用 2 支箭来爆破:
- 在 x = 6 处射出箭，击破气球 [2,8] 和 [1,6]。
- 在 x = 11 处发射箭，击破气球 [10,16] 和 [7,12]。

示例 2：
输入：points = [[1,2],[3,4],[5,6],[7,8]]
输出：4
解释：每个气球需要射出一支箭，总共需要 4 支箭。

示例 3：
输入：points = [[1,2],[2,3],[3,4],[4,5]]
输出：2
解释：气球可以用2支箭来爆破:
- 在 x = 2 处发射箭，击破气球 [1,2] 和 [2,3]。
- 在 x = 4 处射出箭，击破气球 [3,4] 和 [4,5]。
```

其实就是找可以重叠的，跟嵌套还不一样，只要有重叠部分就可以用一支剑来打破。     

先给 [start, end] 中的 end 排序，得到 end 为递增的数组。       

再判断 start ，当后一个 start2 大于上一个 end1 的时候，就需要再射出一支箭。      

当上一个 end1 大于 后一个 start2 的时候，即有 end1 > start2 ，本身 start1 < end1，start2 < end2 。    

故有 start1 < start2 < end2 < start2，即有重叠部分，只用一支箭即可。        
```cpp
[1,6][2,8][7,12][10,16]
0123456      
0023456 78         
0000007 89123        
0000000 001234567   
/**
* @param {number[][]} points
* @return {number}
*/
var findMinArrowShots = function(points) {
    if (!points.length ) {
        return 0;
    }
    points.sort((a, b) => a[1] - b[1]);
    let pos = points[0][1]
    let ans = 1;
    for (let balloon of points) {
        if (balloon[0] > pos) {
            pos = balloon[1];
            ans++;
        }
    }
    return ans;
}*
```
    
## 合并区间
<!-- 排序算法+区间问题 -->
[【LeetCode 56】 合并区间（中等）](https://leetcode-cn.com/problems/merge-intervals/)
```js
以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。
请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

示例 1：
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].

示例 2：
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
```
先对 [starti, endi] 中的 starti 排序。
整一个新数组，只包含第一个元素，然后遍历后面的依次拿到，逐步插入。
插入的时候，比较 未排序的第一个 start 与 已排序的最后一个 end。
如果小于，说明重叠，更新已排序的end，如果大于，说明没有重叠，直接添加进来即可。

```js
intervals = [[1,3],[2,6],[8,10],[15,18]]
/**
* @param {number[][]} intervals
* @return {number[][]}
*/
var merge = function(intervals) {
    if (intervals.length === 0) return [];
    intervals.sort((a, b) => a[0] - b[0]);
    let mergeArr = [intervals[0]];
    let last, curr;
    for (let j = 1; j < intervals.length; j++) {
        last = mergeArr[mergeArr.length - 1]; // last[1] : 已合并的最右(最大)
        curr = intervals[j]; // curr[0] : 待合并的最左(最小) 
        
        if (last[1] >= curr[0]) {   
            last[1] = Math.max(curr[1], last[1]);
        } else {
            mergeArr.push(curr);
        }
    }
    return mergeArr;
};
```