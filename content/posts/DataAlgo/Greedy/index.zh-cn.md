---
title: "贪心算法"
subtitle: ""
date: 2022-08-25T19:33:20+08:00
lastmod: 2022-08-25T19:33:50+08:00
draft: false
authors: []
description: ""

tags: ["Greey"]
categories: ["algorithm"]
series: []

hiddenFromHomePage: false
hiddenFromSearch: false

featuredImage: "hot_air_balloons.jpeg"
featuredImagePreview: "hot_air_balloons.jpeg"

toc:
  enable: true
math:
  enable: false
lightgallery: false
license: ""
---
贪心算法（greedy algorithm），又称贪婪算法，是寻找最优解问题的常用方法。
<!--more-->

## 简介
贪心算法（greedy algorithm），又称贪婪算法，是一种在每一步选择中都采取在当前状态下最好或最优（即最有利）的选择，从而希望导致结果是最好或最优的算法。比如在旅行推销员问题中，如果旅行员每次都选择最近的城市，那这就是一种贪心算法。

贪心算法在有最优子结构的问题中尤为有效。最优子结构的意思是局部最优解能决定全局最优解。简单地说，问题能够分解成子问题来解决，子问题的最优解能递推到最终问题的最优解。

贪心算法与动态规划的不同在于它对每个子问题的解决方案都做出选择，不能回退。动态规划则会保存以前的运算结果，并根据以前的结果对当前进行选择，有回退功能。

贪心法可以解决一些最优化问题，如：求图中的最小生成树、求哈夫曼编码……对于其他问题，贪心法一般不能得到我们所要求的答案。一旦一个问题可以通过贪心法来解决，那么贪心法一般是解决这个问题的最好办法。由于贪心法的高效性以及其所求得的答案比较接近最优结果，贪心法也可以用作辅助算法或者直接解决一些要求结果不特别精确的问题。在不同情况，选择最优的解，可能会导致辛普森悖论（Simpson's Paradox），不一定出现最优的解。

## 基本步骤：

步骤1：从某个初始解出发；     
步骤2：采用迭代的过程，当可以向目标前进一步时，就根据局部最优策略，得到一部分解，缩小问题规模；     
步骤3：将所有解综合起来。     

## 跳跃游戏
[【LeetCode 直通车】：55 跳跃游戏（中等）](https://leetcode-cn.com/problems/jump-game)
```js
给定一个非负整数数组，你最初位于数组的第一个位置。 数组中的每个元素代表你在该位置可以跳跃的最大长度。判断你是否能够到达最后一个位置。

示例 1:
输入: [2,3,1,1,4]
输出: true
解释: 从位置 0 到 1 跳 1 步, 然后跳 3 步到达最后一个位置。

示例 2:
输入: [3,2,1,0,4]
输出: false
解释: 无论怎样，你总会到达索引为 3 的位置。但该位置的最大跳跃长度是 0 ， 所以你永远不可能到达最后一个位置。
```
有关动态规划的问题，大多是让你求最值的，比如最长子序列，最小编辑距离，最长公共子串等等等。这就是规律，因为动态规划本身就是运筹学里的一种求最值的算法。

那么贪心算法作为特殊的动态规划也是一样，一般也是求最值。这道题表面上不是求最值，但是可以改一改：

请问通过题目中的跳跃规则，最多能跳多远？如果能够越过最后一格，返回 true，否则返回 false。

所以说，这道题肯定可以用动态规划求解的。但是由于它比较简单，直接上贪心：
```js
var canJump = function(nums) {
    let faster = 0;
    for (let i = 0; i < nums.length - 1; i++) {
        faster = Math.max(faster, i + nums[i]);
        if (faster <= i) return false;
    }
    return faster >= nums.length - 1;
};
```
    
## 跳跃游戏 II
[【LeetCode 直通车】：45 跳跃游戏 II（中等）](https://leetcode.cn/problems/jump-game-ii)
```js
给定一个非负整数数组，你最初位于数组的第一个位置。数组中的每个元素代表你在该位置可以跳跃的最大长度。你的目标是使用最少的跳跃次数到达数组     
的最后一个位置。

示例:
输入: [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
```
从后往前，以始为终，找能到 n 的最远的 n-1，再找能到 n-1 的 最远 n-2。

```js
var jump = function(nums) {
    let count = 0;
    if(nums.length == 1) {
        return count;
    }
    // 最後一個位置。
    for(let i = nums.length-1; i > 0; i--) {
        // 取出当前位置的值
        // 从前往后循环都一样，因为你必须循环一遍，才能找到最大的那一个元素。
        // 最后前面的一个元素，肯定可以达到，至少为 1 步
        // 从前向后，记录肯定是最远的。
        for(let j = 0; j < i; j++) {
            // 哪一个值并不重要，重要的是距离
            let len = i - j;
            let maxLen = nums[j];
            // 可以达到
            if(maxLen >= len && len > 1) {
                i -= (len-1);
                break;
            }
        }
        // 次数递增
        count++;
    }
    return count;
};
```
另一种思路

```cpp
例：[2,3,1,1,4] 输出：2
var jump = function(nums) {
    let n = nums.length;
    let end = 0, farthest = 0;
    let jumps = 0;
    for (let i = 0; i < n - 1; i++) {                // 0 1 2 3 4
        farthest = Math.max(nums[i] + i, farthest);  // 2 4 3 4 8
        if (end == i) {                              // 0
            jumps++;                                 // 1   2
            end = farthest;                          // 2   4
        }
    }
    return jumps;
};
```

