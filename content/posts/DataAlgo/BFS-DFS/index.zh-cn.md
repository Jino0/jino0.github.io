---
title: "DFS && BFS "
subtitle: ""
date: 2022-09-01T19:57:20+08:00
lastmod: 2022-09-05T16:50:19+08:00
draft: false
authors: []
description: ""

tags: ["BFS","DFS"]
categories: ["algorithm"]
series: []

hiddenFromHomePage: false
hiddenFromSearch: false

featuredImage: "pexels-detavernier-odile.jpeg"
featuredImagePreview: "pexels-detavernier-odile.jpeg"

toc:
  enable: true
math:
  enable: false
lightgallery: false
license: ""
---
> `深度优先遍历`（Depth First Search, 简称 DFS） 与`广度优先遍历`（Breath First Search）是图论中两种非常重要的算法，生产上广泛用于拓扑排序，寻路（走迷宫），搜索引擎，爬虫等，也频繁出现在 leetcode，高频面试题中。
<!--more-->

## DFS 简介
**先递归下去，再回溯上来**。从图中一个未访问的顶点 V 开始，沿着一条路一直走到底，然后从这条路尽头的节点回退到上一个节点，再从另一条路开始走到底...不断递归重复此过程，直到所有的顶点都遍历完成，它的特点是不撞南墙不回头，先走完一条路，再换一条路继续走。

## BFS 简介
从图的一个未遍历的节点出发，先遍历这个节点的相邻节点，再依次遍历每个相邻节点的相邻节点。    
深度优先搜索旨在不管有多少条岔路，先一条路走到底，不成功就返回上一个路口然后就选择下一条岔路，而广度优先搜索旨在面临一个路口时，把所有的岔路口都记下来，然后选择其中一个进入，然后将它的分路情况记录下来，然后再返回来进入另外一个岔路，并重复这样的操作。

## 数据结构上的运用
DFS 用递归的形式，用到了栈结构，先进后出。
BFS 选取状态用队列的形式，先进先出。

## 复杂度
DFS 的复杂度与BFS的复杂度大体一致，不同之处在于遍历的方式与对于问题的解决出发点不同，DFS适合目标明确，而BFS适合大范围的寻找。

## 思想
思想上来说这两种方法都是**穷竭列举**所有的情况。

### **高频算法题系列：BFS**

## 打开转盘锁 BFS
[【LeetCode 直通车】：752 打开转盘锁（中等](https://leetcode-cn.com/problems/open-the-lock/)
```js
有一把带有四个数字的密码锁，每个位置上有 0 ~ 9 共 10 个数字。每次只能将其中一个位置上的数字转动一下。可以向上转，也可以向下转。
比如：1 -> 2、2 -> 1。
密码锁的初始数字为：0000。现在给定一组表示死亡数字的字符串数组 deadends，和一个带有四位数字的目标字符串 target。
如果密码锁转动到 deadends 中任一字符串状态，则锁就会永久锁定，无法再次旋转。
要求：给出最小的选择次数，使得锁的状态由 0000 转动到 target。
```
```js
/**
* @param {string[]} deadends
* @param {string} target
* @return {number}
*/
var openLock = function(deadends, target) {
	let queue = new Queue();
	let visited = new Set();
	let step = 0;
	queue.push('0000');
	visited.add('0000');
	while (!queue.isEmpty()) {
		let size = queue.size();
		for (let i = 0; i < size; i++) {
			let str = queue.pop();
			if (deadends.includes(str)) continue;
			if (target === str) {
				return step;
			}
			for (let j = 0; j < 4; j++) {
				let plusStr = plusOne(str, j);
				let minusStr = minusOne(str, j);
				if (!visited.has(plusStr)) {
					queue.push(plusStr);
					visited.add(plusStr)
				}
				if (!visited.has(minusStr)) {
					queue.push(minusStr);
					visited.add(minusStr)
				}
			}
		}
		step++;
	}
	return -1;
};
function plusOne(str, index) {
	let strArr = str.split('');
	if (strArr[index] === '9') {
		strArr[index] = '0'
	} else {
		strArr[index] = (Number(strArr[index]) + 1).toString()
	}
	return strArr.join('');
}
function minusOne(str, index) {
	let strArr = str.split('');
	if (strArr[index] === '0') {
		strArr[index] = '9'
	} else {
		strArr[index] = (Number(strArr[index]) - 1).toString()
	}
	return strArr.join('');
}
class Queue {
	constructor() {
		this.items = [];
		this.count = 0;
		this.lowerCount = 0;
	}
	push(elem) {
		this.items[this.count++] = elem;
	}
	pop() {
		if (this.isEmpty()) {
			return;
		}
		const elem = this.items[this.lowerCount];
		delete this.items[this.lowerCount];
		this.lowerCount++;
		return elem;
	}
	isEmpty() {
		if (this.size() === 0) return true;
		return false;
	}
	size() {
		return this.count - this.lowerCount;
	}
}
```

## 二叉树的最小深度 BFS
[【LeetCode 直通车】：111 二叉树的最小深度（简单）](https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/)
```js
给定一个二叉树，找出其最小深度。
最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
说明: 叶子节点是指没有子节点的节点。

示例:
给定二叉树 [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
返回它的最小深度 2.
```


```js
/**
* Definition for a binary tree node.
* function TreeNode(val) {
*     this.val = val;
*     this.left = this.right = null;
* }
*
* @param {TreeNode} root
* @return {number}
*/
var minDepth = function(root) {
	if (root == null) return 0;
	let depth = 1;
	let queue = new Queue();
	queue.push(root);
	while (!queue.isEmpty()) {
		let size = queue.size();
		for (let i = 0; i < size; i++) {
				const node = queue.pop();
				if (node.left == null && node.right == null) return depth;
				if (node.left) {
					queue.push(node.left);
				}
				if (node.right) {
					queue.push(node.right);
				}
		}
		depth++;
	}
	return depth;
};
class Queue {
	constructor() {
		this.items = [];
		this.count = 0;
		this.lowerCount = 0;
	}
	push(elem) {
		this.items[this.count++] = elem;
	}
	pop() {
		if (this.isEmpty()) {
				return;
		}
		const elem = this.items[this.lowerCount];
		delete this.items[this.lowerCount];
		this.lowerCount++;
		return elem;
	}
	isEmpty() {
		if (this.size() === 0) return true;
		return false;
	}
	size() {
		return this.count - this.lowerCount;
	}
}
```

## 岛屿的最大面积 DFS
[【LeetCode 直通车】：695 岛屿的最大面积（中等）](https://leetcode-cn.com/problems/max-area-of-island/)
```js
描述：给定一个只包含 0、1 元素的二维数组，1 代表岛屿，0 代表水。一座岛的面积就是上下左右相邻的 1 所组成的连通块的数目。
要求：计算出最大的岛屿面积。
```
  ![](maxarea1-grid.jpeg)
```js
/**
* @param {number[][]} grid
* @return {number}
*/
let maxX, maxY;
let visited;
let globalMaxArea;
var maxAreaOfIsland = function(grid) {
	visited = new Set();
	maxX = grid.length;
	maxY = grid[0].length;
	globalMaxArea = 0;
	for (let i = 0; i < maxX; i++) {
		for (let j = 0; j < maxY; j++) {
			if (grid[i][j] === 1) {
				visited.add(`(${i}, ${j})`);
				globalMaxArea = Math.max(globalMaxArea, dfs(grid, i, j));
			}
			visited.clear();
		}
	}
	return globalMaxArea;
};
function dfs(grid, x, y) {
	let res = 1;
	for (let i = -1; i <= 1; i++) {
		for (let j = -1; j <= 1; j++) {
			if (Math.abs(i) === Math.abs(j)) continue;
			const newX = x + i;
			const newY = y + j;
			if (newX >= maxX || newX < 0 || newY >= maxY || newY < 0)
				continue;
			if (visited.has(`(${newX}, ${newY})`)) continue;
			visited.add(`(${newX}, ${newY})`);
			const areaCnt = grid[newX][newY]
			if (areaCnt === 1) {
				const cnt = dfs(grid, newX, newY);
				res += cnt;
			} 
		}
	}
	return res;
}
```

## 相同的树 DFS
[【LeetCode 直通车】：100 相同的树（简单）](https://leetcode-cn.com/problems/same-tree/)
```js
给定两个二叉树 p 和 q。判断这两棵树是否相同。

两棵树相同的定义：
	结构上相同；
	节点具有相同的值
```
    
```js
/**
* Definition for a binary tree node.
* function TreeNode(val) {
*     this.val = val;
*     this.left = this.right = null;
* }
*
* @param {TreeNode} p
* @param {TreeNode} q
* @return {boolean}
*/
var isSameTree = function(p, q) {
	if (p == null && q == null) return true;
	if (p == null || q == null) return false;
	if (p.val !== q.val) return false;
	return isSameTree(p.left, q.left) && isSameTree(p.right, q.right);
};
```
    
