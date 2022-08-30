---
draft: true
---
<!--more-->

### **高频算法题系列：二分查找**

- **29、寻找两个正序数组的中位数【二分查找】**👉 [【LeetCode 4】 寻找中位数（困难）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fmedian-of-two-sorted-arrays%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/78821aaa-5a3e-4b74-b929-32121f6d3bed/Untitled.png)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/f549df0d-ba7e-4baa-aff0-736f6bc60f9b/Untitled.png)
    
    ```cpp
    */**
     * @param {number[]} nums1
     * @param {number[]} nums2
     * @return {number}
     */*
    var findMedianSortedArrays = function(nums1, nums2) {
        let m = nums1.length, n = nums2.length;
        let i = 0, j = 0;
        let newArr = [];
        while (i < m && j < n) {
            if (nums1[i] < nums2[j]) {
                newArr.push(nums1[i++]);
            } else {
                newArr.push(nums2[j++]);
            }
        }
        newArr = newArr.concat(i < m ? nums1.slice(i) : nums2.slice(j));
        const len = newArr.length;
        console.log(newArr)
        if (len % 2 === 0) {
            return (newArr[len / 2] + newArr[len / 2 - 1]) / 2;
        } else {
            return newArr[Math.floor(len / 2)];
        }
    };
    
    // 二分版
    var findMedianSortedArrays = function(nums1, nums2) {
        const len1 = nums1.length;
        const len2 = nums2.length;
        const mid = (len1 + len2 + 1) >> 1;
        const left = getK(nums1, nums2, 0, 0, mid);
        // 判断总长度奇偶
        if ((len1 + len2) % 2) {
            return left; //基数
        } else {
            const right = getK(nums1, nums2, 0, 0, mid + 1);
            return (left + right) / 2
        }
    };
    
    // 取第k小的数
    function getK(nums1, nums2, start1, start2, k) {
        const len1 = nums1.length;
        const len2 = nums2.length;
        /* 特例 */
        // nums1 数组的元素排除完
        if (len1 === start1) return nums2[start2 + k - 1];
        if (len2 === start2) return nums1[start1 + k - 1];
        // 排除到只剩两个元素取最小 即剩余元素的最小值
        if (k === 1) return Math.min(nums1[start1], nums2[start2]);
    
        /* 通常情况 */
        // 取k的一半 同时注意可能会超出数组长度 最多取数组最后一个元素
        const i = start1 + Math.min(len1, k >> 1) - 1;
        const j = start2 + Math.min(len2, k >> 1) - 1;
        // j 前面的所有元素被排除了 同时缩减k的值
        if (nums1[i] > nums2[j]) {
            return getK(nums1, nums2, start1, j + 1, k - (j - start2 + 1));
        } else {
            return getK(nums1, nums2, i + 1, start2, k - (i - start1 + 1));
        }
    }
    ```
    
- **30、判断子序列【二分查找】**👉 [【LeetCode 392】判断子序列（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fis-subsequence%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/a550eb8b-2699-43cd-be0d-bf06320753ac/Untitled.png)
    
    ```cpp
    */**
     * @param {string} s
     * @param {string} t
     * @return {boolean}
     */*
    var isSubsequence = function(s, t) {
        let hash = {};
        for (let i = 0; i < t.length; i++) {
            if (!hash[t[i]]) hash[t[i]] = [];
            hash[t[i]].push(i);
        }
    		// hash：[(a:[0])]
        let lastMaxIndex = 0;
        for (let i = 0; i < s.length; i++) {
            if (hash[s[i]]) {
                const index = binarySearch(hash[s[i]], lastMaxIndex);
                console.log('index', index, hash[s[i]]);
                if (index === -1) return false;
                lastMaxIndex = hash[s[i]][index] + 1;
            } else return false;
        }
        return true;
    };
    function binarySearch(array, targetIndex) {
        let left = 0, right = array.length;
        while (left < right) {
            let mid = left + Math.floor((right - left) / 2);
            if (array[mid] >= targetIndex) {
                right = mid;
            } else if (array[mid] < targetIndex) {
                left = mid + 1;
            }
        }
        if (left >= array.length || array[left] < targetIndex) return -1;
        return left;
    }
    // 贪心
    var isSubsequence = function(s, t) {
        let n = s.length;
        let m = t.length;
        let i = 0, j = 0;
        while (i < n && j < m) {
            if (s[i] == t[j]) {
                i++;
            }
            j++;
        }
        return i == n;
    };
    
    //动态规划
    bool isSubsequence(char* s, char* t) {
        int n = strlen(s), m = strlen(t);
    
        int f[m + 1][26];
        memset(f, 0, sizeof(f));
        for (int i = 0; i < 26; i++) {
            f[m][i] = m;
        }
    
        for (int i = m - 1; i >= 0; i--) {
            for (int j = 0; j < 26; j++) {
                if (t[i] == j + 'a')
                    f[i][j] = i;
                else
                    f[i][j] = f[i + 1][j];
            }
        }
        int add = 0;
        for (int i = 0; i < n; i++) {
            if (f[add][s[i] - 'a'] == m) {
                return false;
            }
            add = f[add][s[i] - 'a'] + 1;
        }
        return true;
    }
    ```
    
- **31、 在排序数组中查找元素的第一个和最后一个位置【二分搜索】**👉 [【LeetCode 直通车】：34 在排序数组中查找元素的第一个和最后一个位置（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Ffind-first-and-last-position-of-element-in-sorted-array%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/af28c664-a6cd-497a-82d5-3fe0a573611a/Untitled.png)
    
    ```cpp
    */**
     * @param {number[]} nums
     * @param {number} target
     * @return {number[]}
     */*
    var searchRange = function(nums, target) {
        const left = leftBound(nums, target);
        const right = rightBound(nums, target);
        return [left, right];
    };
    function leftBound(nums, target) {
        let left = 0;
        let right = nums.length - 1;
        while (left <= right) {
            let mid = Math.floor(left + (right - left) / 2);
            if (nums[mid] === target) {
                right = mid - 1;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid - 1;
            }
        }
        if (left >= nums.length || nums[left] !== target) {
            return -1;
        }
        return left;
    }
    function rightBound(nums, target) {
        let left = 0;
        let right = nums.length - 1;
        while (left <= right) {
            let mid = Math.floor(left + (right - left) / 2);
            if (nums[mid] === target) {
                left = mid + 1;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid - 1;
            }
        }
        if (right < 0 || nums[right] !== target) {
            return -1;
        }
        return right;
    }
    ```
    


### **高频算法题系列：BFS**

- **39、打开转盘锁【BFS】**👉 [【LeetCode 直通车】：752 打开转盘锁（中等](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fopen-the-lock%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/ce2cdfb6-9b54-4f0d-aaea-227ef90ccdf6/Untitled.png)
    
    ```cpp
    */**
     * @param {string[]} deadends
     * @param {string} target
     * @return {number}
     */*
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
    
- **40二叉树的最小深度【BFS】**👉 [【LeetCode 直通车】：111 二叉树的最小深度（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fminimum-depth-of-binary-tree%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/f71afde5-430d-472a-83f9-445c9e356ae4/Untitled.png)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/4b40e5d7-e4d6-4559-aa49-389d3c488995/Untitled.png)
    
    ```cpp
    */**
     * Definition for a binary tree node.
     * function TreeNode(val) {
     *     this.val = val;
     *     this.left = this.right = null;
     * }
     *//**
     * @param {TreeNode} root
     * @return {number}
     */*
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
    

### **【🔥】高频算法题系列：栈**

- **41、最小栈【栈】**👉 [【LeetCode 直通车】：155 最小栈（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fmin-stack%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/29a85eb4-0c0e-43a7-afae-9ca6833729e9/Untitled.png)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/3f5b7444-e3ad-4a81-b18a-8ab84bbdd867/Untitled.png)
    
    ```cpp
    */**
     * initialize your data structure here.
     */*
    var MinStack = function() {
        this.stack = [];
        this.minArr = [];
        this.count = 0;
        this.min = Number.MAX_SAFE_INTEGER;
    };
    */** 
     * @param {number} x
     * @return {void}
     */ 3526578*
    MinStack.prototype.push = function(x) {
        this.min = Math.min(this.min, x);
        this.minArr[this.count] = this.min;
        this.stack[this.count] = x;
        this.count++;
    };
    */**
     * @return {void}
     */*
    MinStack.prototype.pop = function() {
        const element = this.stack[this.count - 1];
        if (this.count - 2 >= 0) this.min = this.minArr[this.count - 2];
        else  this.min = Number.MAX_SAFE_INTEGER;
        delete this.stack[this.count - 1];
        delete this.minArr[this.count - 1];
        this.count--;
        return element;
    };
    */**
     * @return {number}
     */*
    MinStack.prototype.top = function() {
        if (this.count >= 1) {
            return this.stack[this.count - 1];
        }
        return null;
    };
    */**
     * @return {number}
     */*
    MinStack.prototype.getMin = function() {
        const element = this.minArr[this.count - 1];
        return element;
    };
    */**
     * Your MinStack object will be instantiated and called as such:
     * var obj = new MinStack()
     * obj.push(x)
     * obj.pop()
     * var param_3 = obj.top()
     * var param_4 = obj.getMin()
     */*
    ```
    

**【系列】下一个更大元素 【栈】**

- **42 、**👉 [【LeetCode 直通车】：496 下一个更大元素 I（简单](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fnext-greater-element-i%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/376064b3-4844-4b19-b551-5d09cb66f505/Untitled.png)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/8dfcb1e3-98a7-4468-ad5d-6c73b393c47e/Untitled.png)
    
    ```cpp
    */**
     * @param {number[]} nums
     * @return {number[]}
     */
    //        4 1 2
    //        2 5 3 6 8 4 7 1
    //        7 
    // stack: 2 5 6 8
    //   map: -1 -1  7 
    //        7 -1 5
    var nextGreaterElement = function(nums1, nums2) {
        const map = new Map();
        const stack = [];
        for (let i = nums2.length - 1; i >= 0; --i) {
            const num = nums2[i];
            while (stack.length && num >= stack[stack.length - 1]) {
                stack.pop();
            }
            map.set(num, stack.length ? stack[stack.length - 1] : -1);
            stack.push(num);
        }
        const res = new Array(nums1.length).fill(0).map((_, i) => map.get(
    																																nums1[i]));
        return res;
    }；*
    ```
    

👉 [【LeetCode 直通车】：503 下一个更大元素 II（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fnext-greater-element-ii%2F)

- **43【面试真题】有效的括号【栈】**👉 [【LeetCode 直通车】：20 有效的括号（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fvalid-parentheses%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/f94ff437-ce1c-41c8-9d62-907831fe407d/Untitled.png)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/46ca6c3b-8c1f-4d68-93c5-cdcc0b55867b/Untitled.png)
    
    ```cpp
    */**
     * @param {string} s
     * @return {boolean}
     */*
    var isValid = function(s) {
        if (s.length === 0) {
            return true;
        }
        if (s.length % 2 !== 0) {
            return false;
        }
        let map = {
            ')': '(',
            ']': '[',
            '}': '{',
        };
        let left = ['(', '[', '{'];
        let right = [')', ']', '}'];    
        let stack = new Stack();
        for (let i = 0; i < s.length; i++) {
            if (!right.includes(s[i])) {
                stack.push(s[i]);
            } else {
                const matchStr = map[s[i]];
                while (!stack.isEmpty()) {
                    const element = stack.pop();
                    if (left.includes(element) && matchStr !== element)  return false;
                    if (element === matchStr) break;
                }
            }
        }
        return stack.isEmpty();
    };
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
            if (this.isEmpty()) return undefined;
            const element = this.items[this.count - 1];
            delete this.items[this.count - 1];
            this.count--;
            return element;
        }
        isEmpty() {
            return this.size() === 0;
        }
        size() {
            return this.count;
        }
    }
    
    复制代码
    ```
    
- **44、简化路径【栈】**👉 [【LeetCode 直通车】：71 简化路径（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fsimplify-path%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/187011de-72b3-432f-893b-6ce8ab93d3e2/Untitled.png)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/2b1ebf56-7885-47d3-87ce-6ba8da43f161/Untitled.png)
    
    ```cpp
    */**
     * @param {string} path
     * @return {string}
     */*
    var simplifyPath = function(path) {
        let newPath = path.split('/');
        newPath = newPath.filter(item => item !== "");
        const stack = new Stack();
        for (let s of newPath) {
            if (s === '..') stack.pop();
            else if (s !== '.') stack.push(s);
        }
        if (stack.isEmpty()) return '/';
        let str = '';
        while (!stack.isEmpty()) {
            const element = stack.pop();
            str = '/' + element + str;
        }
        return str;
    };
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
            if (this.isEmpty()) return undefined;
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
    
    复制代码
    ```
    

### **【🔥】高频算法题系列：DFS**

- **45、岛屿的最大面积【DFS】**👉 [【LeetCode 直通车】：695 岛屿的最大面积（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fmax-area-of-island%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/80918966-7652-41db-8dcf-383131940c68/Untitled.png)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/335407cb-1b03-4229-8388-cff611403883/Untitled.png)
    
    ```cpp
    */**
     * @param {number[][]} grid
     * @return {number}
     */*
    let maxX, maxY;let visited;let globalMaxArea;
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
    
- **46、相同的树【DFS】**👉 [【LeetCode 直通车】：100 相同的树（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fsame-tree%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/cdab6365-ebf0-4115-8410-d9bfa1977fc3/Untitled.png)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/b9a4e93e-fc76-45ba-8dd8-ea96a67f1019/Untitled.png)
    
    ```cpp
    */**
     * Definition for a binary tree node.
     * function TreeNode(val) {
     *     this.val = val;
     *     this.left = this.right = null;
     * }
     *//**
     * @param {TreeNode} p
     * @param {TreeNode} q
     * @return {boolean}
     */*
    var isSameTree = function(p, q) {
        if (p == null && q == null) return true;
        if (p == null || q == null) return false;
        if (p.val !== q.val) return false;
        return isSameTree(p.left, q.left) && isSameTree(p.right, q.right);
    };
    ```
    

### **【🔥】高频算法题系列：回溯算法**

- **47、【面试真题】N皇后【回溯算法】**👉 [【LeetCode 直通车】：51 N皇后（困难）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fn-queens%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/41da1749-65db-445a-842a-2da8b530b6b2/Untitled.png)
    
    ```cpp
    */**
     * @param {number} n
     * @return {string[][]}
     */*
    let result = [];
    var solveNQueens = function(n) {
        result = [];
        let board = [];
        for (let i = 0; i < n; i++) {
    	      board[i] = [];
    	      for (let j = 0; j < n; j++) {
    		        board[i][j] = '.'
    	      }
        }
        backtrack(0, board, n);
        return result;
    };
    
    function backtrack(row, board, n) {
        if (row === n) {
    	      result.push(deepClone(board));
    	      return;
        }
        for (let j = 0; j < n; j++) {
    		    if (checkInValid(board, row, j, n)) continue;
            board[row][j] = 'Q';
            backtrack(row + 1, board, n);
            board[row][j] = '.';
        }
    }
    function checkInValid(board, row, column, n) {
    	  *// 行*
    		for (let i = 0; i < n; i++) {
    			  if (board[i][column] === 'Q') return true;
    	  }
    	  for (let i = row - 1, j = column + 1; i >= 0 && j < n; i--, j++) {
    			  if (board[i][j] === 'Q') return true;
    	  }
    	  for (let i = row - 1, j = column - 1; i >= 0 && j >= 0; i--, j--) {
    		    if (board[i][j] === 'Q') return true;
    	  }
    	  return false;
    }
    function deepClone(board) {
    	  let res = [];
    	  for (let i = 0; i < board.length; i++) {
    		    res.push(board[i].join(''));
    	  }
    	  return res;
    }
    ```
    
- **48、全排列【回溯算法】**👉 [【LeetCode 直通车】：46 全排列（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fpermutations%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/55787e69-41dd-4a3a-a507-c69f1dc2d2a0/Untitled.png)
    
    ```cpp
    */**
     * @param {number[]} nums
     * @return {number[][]}
     */*
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
    
- **49、括号生成【回溯算法】**👉 [【LeetCode 直通车】：22 括号生成（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fgenerate-parentheses%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/12c44214-b9b0-4110-840a-5fda9dc24d92/Untitled.png)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/f5844310-8d6a-4a06-bc6a-5664c0bc3b91/Untitled.png)
    
    ```cpp
    */**
     * @param {number} n
     * @return {string[]}
     */*
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
    function isValidCombination(bracket) {
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
    
- **50、复原 IP 地址【回溯算法】**👉 [【LeetCode 直通车】：93 复原 IP 地址（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Frestore-ip-addresses%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/41a195c2-cf6b-40d4-895a-444853f6eed2/Untitled.png)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/436b70e7-113c-4c19-8ed6-1bd3d56a6d42/Untitled.png)
    
    ```cpp
    */**
     * @param {string} s
     * @return {string[]}
     */*
    var restoreIpAddresses = function(s) {
        if (s.length > 12) return [];
        let res = [];
        const track = [];
        backtrack(s, track, res);
        return res;
    };
    backtrack('25525511135', [],[]);
    function backtrack(s, track, res) {
    		// 递归条件：字符串分完，正好四个
        if (track.length === 4 && s.length === 0) {
            res.push(track.join('.'));
            return;
        }
        let len = s.length >= 3 ? 3 : s.length;
        for (let i = 0; i < len; i++) {  // i=1
            const c = s.slice(0, i + 1); // 55
            if (parseInt(c) > 255) continue; 55 
            if (i >= 1 &&  parseInt(c) < parseInt((1 + '0'.repeat(i)))) 
    						continue; // 0 开头的情况
            track.push(c);
            backtrack(s.slice(i + 1), track, res);
            track.pop();
        }
    }
    
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
    
- **51、子集【回溯算法】**👉 [【LeetCode 直通车】：78 子集（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fsubsets%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/c3fa4fa0-4ad5-4b99-82f5-081936633a51/Untitled.png)
    
    ```cpp
    */**
     * @param {number[]} nums
     * @return {number[][]}
     */*
    var subsets = function(nums) {
        if (nums.length === 0) return [[]];
        let resArr = [];
        backtrack(nums, 0, [], resArr);
        return resArr;
    };
    function backtrack(nums, index, subArr, resArr) {
        if (Array.isArray(subArr)) {
            resArr.push(subArr.slice());          // [] [1] [1,2]
        }
        if (index === nums.length) {            //0 1 2
            return;
        } 
        for (let i = index; i < nums.length; i++) { // 0
            subArr.push(nums[i]);                //1 2  3
            backtrack(nums, i + 1, subArr, resArr); // 2
            subArr.pop(nums[i]);
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
    
- **C++实现大数相乘的算法**
    
    由于数字无法用一个整形变量存储，很自然的想到用字符串来表示一串数字。然后按照乘法的运算规则，用一个乘数的每一位乘以另一个乘数，然后将所有中间结果按正确位置相加得到最终结果。可以分析得出如果乘数为A和B，A的位数为m，B的位数为n，则乘积结果为m+n-1位（最高位无进位）或m+n位（最高位有进位）。因此可以分配一个m+n的辅存来存储最终结果。为了节约空间，所有的中间结果直接在m+n的辅存上进行累加。
    
    C++实现大数相乘代码如下：
    
    ```cpp
    #include<iostream>
    #include<string>
    using namespace std;
     
    string BigNumMultiply(string str1,string str2)
    {
    		int size1=str1.size(),size2=str2.size();
    		string str(size1+size2,'0');
    		for(int i=size2-1;i>=0;--i)
    		{
    				int mulflag=0,addflag=0;
    				for(int j=size1-1;j>=0;--j)
    				{
    						int temp1=(str2[i]-'0')*(str1[j]-'0')+mulflag;
    						mulflag=temp1/10;
    						temp1=temp1%10;
    						int temp2=str[i+j+1]-'0'+temp1+addflag;
    						str[i+j+1]=temp2%10+48;
    						addflag=temp2/10;
    				}
    				str[i]+=mulflag+addflag;
    		}
    		if(str[0]=='0')
    		str=str.substr(1,str.size());
    		return str;
    }
     
    int main()
    {
    		string str1,str2;
    		while(cin>>str1>>str2)
    		{
    				cout<<str1<<"*"<<str2<<"="<<endl;
    				cout<<BigNumMultiply(str1,str2)<<endl;
    		}
    		return 0;
    }
    ```