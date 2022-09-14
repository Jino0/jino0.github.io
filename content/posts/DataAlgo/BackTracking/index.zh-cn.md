---
title: "回溯 算法"
subtitle: ""
date: 2022-09-05T16:53:19+08:00
lastmod: 2022-09-07T00:53:45+08:00
draft: false
authors: []
description: ""

tags: ["backtracking"]
categories: ["algorithm"]
series: []

hiddenFromHomePage: false
hiddenFromSearch: false

featuredImage: "pexels-brett-sayle.jpeg"
featuredImagePreview: "pexels-brett-sayle.jpeg"

toc:
  enable: true
math:
  enable: false
lightgallery: false
license: ""
---

回溯法可以理解为通过选择不同的岔路口寻找目的地，一个岔路口一个岔路口的去尝试找到目的地。如果走错了路，继续返回来找到岔路口的另一条路，直到找到目的地。

<!--more-->

## 简介
一种能避免不必要搜索的穷举式的搜索算法。采用试错的思想，在搜索尝试过程中寻找问题的解，当探索到某一步时，发现原先的选择并不满足求解条件，或者还需要满足更多求解条件时，就退回一步（回溯）重新选择，这种走不通就退回再走的技术称为「回溯法」，而满足回溯条件的某个状态的点称为「回溯点」。     

简单来说，回溯算法采用了一种 「走不通就回退」 的算法思想。

回溯算法通常用简单的递归方法来实现，在进行回溯过程中更可能会出现两种情况：

找到一个可能存在的正确答案；
在尝试了所有可能的分布方法之后宣布该问题没有答案。

回溯算法的基本思想是：以深度优先搜索的方式，根据产生子节点的条件约束，搜索问题的解。当发现当前节点已不满足求解条件时，就「回溯」返回，尝试其他的路径。

那么，在写回溯算法时，我们可以按照这个思想来书写回溯算法，具体步骤如下：
```js
明确所有选择：画出搜索过程的决策树，根据决策树来确定搜索路径。
明确终止条件：推敲出递归的终止条件，以及递归终止时的要执行的处理方法。
将决策树和终止条件翻译成代码：
    定义回溯函数（明确函数意义、传入参数、返回结果等）。
    书写回溯函数主体（给出约束条件、选择元素、递归搜索、撤销选择部分）。
    明确递归终止条件（给出递归终止条件，以及递归终止时的处理方法）。
```

## 通用模版
```py
res = []    # 存放所欲符合条件结果的集合
path = []   # 存放当前符合条件的结果
def backtracking(nums):             # nums 为选择元素列表
    if 遇到边界条件:                  # 说明找到了一组符合条件的结果
        res.append(path[:])         # 将当前符合条件的结果放入集合中
        return

    for i in range(len(nums)):      # 枚举可选元素列表
                        # 有时该处也应该加入一遍筛选条件，具体看题
        path.append(nums[i])        # 选择元素
        backtracking(nums)          # 递归搜索
        path.pop()                  # 撤销选择

backtracking(nums)
```
## 子集
[【LeetCode 直通车】：78 子集](https://leetcode.cn/problems/subsets/)
```js
给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。
解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

示例 1：
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

示例 2：
输入：nums = [0]
输出：[[],[0]]
```

```js
/**
 * @param {number[]} nums
 * @return {number[][]}
 */
var subsets = function(nums) {
    let res = [];
    backTrack(nums, res, 0, []);
    return res;
};
function backTrack(nums, res, index, track){
    if(Array.isArray(track)){
        res.push(track.slice());
    }
    if(index === nums.length){
        return ;
    }
    for(let i=index; i<nums.length; i++){
        track.push(nums[i]);
        backTrack(nums, res, i+1, track);// [] 
        track.pop();
    }
}

[] [1] [1,2] [1,2,3] [1,3] [2] [2,3] [3]
i=0 [1] index=1 [1]
    i=1 index=2 [1,2]
        i=2 index=3 [1,2,3] b; pop [1,2]
    i=1 index=2 [1,2] pop [1]
    i=2 index=3 [1,3] pop [1]
i=0 [1] index=1 [1] pop []

i=1 index=2 [2]  
    i=2 index=3 [2,3] pop [2]

i=2
```

```js
var subsets = function(nums) {
    const t = [];
    const ans = [];
    const dfs = (cur) => {
        if (cur === nums.length) {
            ans.push(t.slice());
            return;
        }
        t.push(nums[cur]);    // [1] [1,2] [1,2,3] 
        dfs(cur + 1);
        t.pop(t.length - 1);
        dfs(cur + 1);
    }
    dfs(0);
    return ans;
};
```

## 全排列
[【LeetCode 直通车】：46 全排列（中等）](https://leetcode-cn.com/problems/permutations/)
```js
给定一个不含重复数字的数组 nums ，返回其所有可能的全排列 。你可以 按任意顺序 返回答案。

示例 1：
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

示例 2：
输入：nums = [0,1]
输出：[[0,1],[1,0]]

示例 3：
输入：nums = [1]
输出：[[1]]
```
    
```js
/**
* @param {number[]} nums
* @return {number[][]}
*/
let results = [];
var permute = function(nums) {
    results = [];
    backtrack(nums, []);
    return results;
};
function backtrack(nums, track) {
    if (nums.length === track.length) {
        results.push(track.slice());
        return;
    }
    for (let i = 0; i < nums.length; i++) {
        if (track.includes(nums[i])) continue;
        track.push(nums[i]);
        backtrack(nums, track);
        track.pop();
    }
}
```
    
## 括号生成
[【LeetCode 直通车】：22 括号生成（中等）](https://leetcode-cn.com/problems/generate-parentheses/)
```js
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

示例 1：
输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]

示例 2：
输入：n = 1
输出：["()"]
```

```js
/**
* @param {number} n
* @return {string[]}
*/
var generateParenthesis = function(n) {
    let validRes = [];
    backtrack(n * 2, validRes, '');
    return validRes;
};
function backtrack(len, validRes, bracket) {
    if (bracket.length === len) {
        if (isValidCombination(bracket)) {
            validRes.push(bracket);
        }
        return;
    }
    for (let str of ['(', ')']) {
        bracket += str;
        backtrack(len, validRes, bracket);
        bracket = bracket.slice(0, bracket.length - 1);
    }
}
function isValidCombination(bracket) {  // (())()
    let stack = new Stack();
    for (let i = 0; i < bracket.length; i++) {
        const str = bracket[i];
        if (str === '(') {
            stack.push(str);
        } else if (str === ')') {
            const top = stack.pop();
            if (top !== '(') return false;
        }
    }
    return stack.isEmpty();
}
class Stack {
    constructor() {
        this.count = 0;
        this.items = [];
    }
    push(element) {
        this.items[this.count] = element;
        this.count++;
    }
    pop() {
        if (this.isEmpty()) return;
        const element = this.items[this.count - 1];
        delete this.items[this.count - 1];
        this.count--;
        return element;
    }
    size() {
        return this.count;
    }
    isEmpty() {
        return this.size() === 0;
    }
}
```
    
## 复原 IP 地址
[【LeetCode 直通车】：93 复原 IP 地址（中等）](https://leetcode-cn.com/problems/restore-ip-addresses/)
```js
有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。

例如："0.1.2.201" 和 "192.168.1.1" 是有效 IP 地址，但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是无效 IP 地址。
给定一个只包含数字的字符串 s ，用以表示一个 IP 地址，返回所有可能的有效 IP 地址，这些地址可以通过在 s 中插入 '.' 来形成。
你不能重新排序或删除 s 中的任何数字。你可以按任何顺序返回答案。

示例 1：
输入：s = "25525511135"
输出：["255.255.11.135","255.255.111.35"]

示例 2：
输入：s = "0000"
输出：["0.0.0.0"]

示例 3：
输入：s = "101023"
输出：["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
```
```js
/**
 * @param {string} s
 * @return {string[]}
 */
var restoreIpAddresses = function (s) {
    if (s.length > 12) return [];
    let res = [];
    const track = [];
    backtracking(s, res, track);
    return res;
};

function backtracking(s, res, track) {
    if (track.length === 4 && s.length === 0) {
        res.push(track.join('.'));
        return;
    }

    const len = s.length >= 3 ? 3 : s.length;
    for (let i = 0; i < len; i++) {
        const str = s.slice(0, i + 1);
        if (parseInt(str) > 255) continue;
        if (i >= 1 && parseInt(str) < (1 + '0'.repeat(i)))
            continue;
        track.push(str);
        backtracking(s.slice(i + 1), res, track);
        track.pop();
    }
}
```

```js
//2
var restoreIpAddresses = function(s) {
    const SEG_COUNT = 4;
    const segments = new Array(SEG_COUNT);
    const ans = [];

    const dfs = (s, segId, segStart) => {
        // 如果找到了 4 段 IP 地址并且遍历完了字符串，那么就是一种答案
        if (segId === SEG_COUNT) {
            if (segStart === s.length) {
                ans.push(segments.join('.'));
            }
            return;
        }

        // 如果还没有找到 4 段 IP 地址就已经遍历完了字符串，那么提前回溯
        if (segStart === s.length) {
            return;
        }

        // 由于不能有前导零，如果当前数字为 0，那么这一段 IP 地址只能为 0
        if (s.charAt(segStart) === '0') {
            segments[segId] = 0;
            dfs(s, segId + 1, segStart + 1);
        }

        // 一般情况，枚举每一种可能性并递归
        let addr = 0;
        for (let segEnd = segStart; segEnd < s.length; ++segEnd) {
            addr = addr * 10 + (s.charAt(segEnd) - '0');
            if (addr > 0 && addr <= 0xFF) {
                segments[segId] = addr;
                dfs(s, segId + 1, segEnd + 1);
            } else {
                break;
            }
        }
    }

    dfs(s, 0, 0);
    return ans;
};
```

## N皇后
[【LeetCode 直通车】：51 N皇后（困难）](https://leetcode-cn.com/problems/n-queens/)
```js
按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

示例：
输入    n = 4
输出    [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
解释    如下图所示，4 皇后问题存在 2 个不同的解法。
```
<div align=center><img src="nQueens.jpeg" width="300"></div>

```js
/**
 * @param {number} n
 * @return {string[][]}
 */
var solveNQueens = function (n) {
    let res = [], board = [];
    for (let i = 0; i < n; i++) {
        board[i] = [];
        for (j = 0; j < n; j++) {
            board[i][j] = '.';
        }
    }
    backtracking(0, res, board, n);
    return res;
};

function backtracking(row, res, board, n) {
    if (row === n) {  // 合理结果push,递归结束
        res.push(deepClone(board));
        return;
    }
    for (let i = 0; i < n; i++) {
        if (checkIsNotValid(board, row, i, n)) continue;//检查解的合理性
        board[row][i] = 'Q';// 写入解
        backtracking(row + 1, res, board, n);//递归
        board[row][i] = '.'; // 回溯
    }
}

function checkIsNotValid(board, row, column, n) {
    // 行
    for (let i = 0; i < n; i++) {
        if (board[i][column] === 'Q') return true;
    }
    // 列 不必要，因为是一行行下来的所以没必要了
    for (let i = 0; i < n; i++) {
        if (board[row][i] === 'Q') return true;
    }
    // 斜线，又分为：右上，右下，左上，左下。也是因为一行行下来的，所以只需要检测上面的。左上，右上
    // 左上
    for (let i = row - 1, j = column - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] === 'Q') return true;
    }
    // 右上
    for (let i = row - 1, j = column + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] === 'Q') return true;
    }

}

function deepClone(board) {
    let res = [];
    for (let i = 0; i < board.length; i++) {
        res[i] = board[i].join('');
    }
    return res;
}
```