# 栈 相关


<!--more-->

## 最小栈
[【LeetCode 直通车】：155 最小栈（简单）](https://leetcode-cn.com/problems/min-stack/)
```js
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

实现 MinStack 类:

MinStack() 初始化堆栈对象。
void push(int val) 将元素val推入堆栈。
void pop() 删除堆栈顶部的元素。
int top() 获取堆栈顶部的元素。
int getMin() 获取堆栈中的最小元素。

示例 1:
输入：
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

输出：
[null,null,null,null,-3,null,0,-2]

解释：
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.
```
```js
/**
* Your MinStack object will be instantiated and called as such:
* var obj = new MinStack()
* obj.push(x)
* obj.pop()
* var param_3 = obj.top()
* var param_4 = obj.getMin()
*/
/**
* initialize your data structure here.
*/
var MinStack = function () {
    this.stack = []; // 记录栈中所有元素
    this.minArr = []; // 记录当前数目下的最小值
    this.min = Number.MAX_SAFE_INTEGER; // 栈的最小值
    this.count = 0; // 栈中的元素个数
};

/** 
 * @param {number} val
 * @return {void}
 */
MinStack.prototype.push = function (val) {
    this.min = Math.min(val, this.min);
    this.minArr[this.count] = this.min;
    this.stack[this.count] = val;
    this.count++;
};

/**
 * @return {void}
 */
MinStack.prototype.pop = function () {
    const element = this.stack[this.count - 1];
    if (this.count - 2 >= 0)
        this.min = this.minArr[this.count - 2];
    else
        this.min = Number.MAX_SAFE_INTEGER;
    delete this.minArr[this.count - 1];
    delete this.stack[this.count - 1];
    this.count--;
    return element;
};

/**
 * @return {number}
 */
MinStack.prototype.top = function () {
    if (this.count >= 1)
        return this.stack[this.count - 1];
    else
        return null;
};

/**
 * @return {number}
 */
MinStack.prototype.getMin = function () {
    return this.minArr[this.count - 1];
};
```

## 下一个更大元素 I
[【LeetCode 直通车】：496 下一个更大元素 I（简单)](https://leetcode.cn/problems/next-greater-element-i/)
```js
nums1 中数字 x 的下一个更大元素是指 x 在 nums2 中对应位置右侧的第一个比 x 大的元素。

给你两个没有重复元素的数组 nums1 和 nums2 ，下标从 0 开始计数，其中 nums1 是 nums2 的子集。

对于每个 0 <= i < nums1.length ，找出满足 nums1[i] == nums2[j] 的下标 j ，并且在 nums2 确定 nums2[j] 的下一个更大元素 。
如果不存在下一个更大元素，那么本次查询的答案是 -1 。

返回一个长度为 nums1.length 的数组 ans 作为答案，满足 ans[i] 是如上所述的下一个更大元素 。

示例 1：
输入：nums1 = [4,1,2], nums2 = [1,3,4,2].
输出：[-1,3,-1]
解释：nums1 中每个值的下一个更大元素如下所述：
- 4 ，用加粗斜体标识，nums2 = [1,3,4,2]。不存在下一个更大元素，所以答案是 -1 。
- 1 ，用加粗斜体标识，nums2 = [1,3,4,2]。下一个更大元素是 3 。
- 2 ，用加粗斜体标识，nums2 = [1,3,4,2]。不存在下一个更大元素，所以答案是 -1 。

示例 2：
输入：nums1 = [2,4], nums2 = [1,2,3,4].
输出：[3,-1]
解释：nums1 中每个值的下一个更大元素如下所述：
- 2 ，用加粗斜体标识，nums2 = [1,2,3,4]。下一个更大元素是 3 。
- 4 ，用加粗斜体标识，nums2 = [1,2,3,4]。不存在下一个更大元素，所以答案是 -1 。
```
```js
/**
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
    const res = new Array(nums1.length).fill(0).map((_, i) => map.get(nums1[i]));
    return res;
}；
```

## 下一个更大元素 II
[【LeetCode 直通车】：503 下一个更大元素 II（中等）](https://leetcode-cn.com/problems/next-greater-element-ii/)
```js
给定一个循环数组 nums （ nums[nums.length - 1] 的下一个元素是 nums[0] ），返回 nums 中每个元素的 下一个更大元素 。

数字 x 的 下一个更大的元素 是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1 。

示例 1:
输入: nums = [1,2,1]
输出: [2,-1,2]
解释: 第一个 1 的下一个更大的数是 2；
数字 2 找不到下一个更大的数； 
第二个 1 的下一个最大的数需要循环搜索，结果也是 2。

示例 2:
输入: nums = [1,2,3,4,3]
输出: [2,3,4,-1,4]
```
## 有效的括号
[【LeetCode 直通车】：20 有效的括号（中等）](https://leetcode.cn/problems/valid-parentheses/)

```js
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
每个右括号都有一个对应的相同类型的左括号。
 
示例 1：
输入：s = "()"
输出：true

示例 2：
输入：s = "()[]{}"
输出：true

示例 3：
输入：s = "(]"
输出：false
```
```js
/**
* @param {string} s
* @return {boolean}
*/
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
```

## 简化路径
[【LeetCode 直通车】：71 简化路径（中等）](https://leetcode.cn/problems/simplify-path/)
```js
给你一个字符串 path ，表示指向某一文件或目录的 Unix 风格绝对路径 （以 '/' 开头），请你将其转化为更加简洁的规范路径。

在 Unix 风格的文件系统中，一个点（.）表示当前目录本身；此外，两个点 （..） 表示将目录切换到上一级（指向父目录）；
两者都可以是复杂相对路径的组成部分。任意多个连续的斜杠（即，'//'）都被视为单个斜杠 '/' 。
对于此问题，任何其他格式的点（例如，'...'）均被视为文件/目录名称。

请注意，返回的规范路径 必须遵循下述格式：

始终以斜杠 '/' 开头。
两个目录名之间必须只有一个斜杠 '/' 。
最后一个目录名（如果存在）不能 以 '/' 结尾。
此外，路径仅包含从根目录到目标文件或目录的路径上的目录（即，不含 '.' 或 '..'）。
返回简化后得到的 规范路径 。

示例 1：
输入：path = "/home/"
输出："/home"
解释：注意，最后一个目录名后面没有斜杠。 

示例 2：
输入：path = "/../"
输出："/"
解释：从根目录向上一级是不可行的，因为根目录是你可以到达的最高级。

示例 3：
输入：path = "/home//foo/"
输出："/home/foo"
解释：在规范路径中，多个连续斜杠需要用一个斜杠替换。

示例 4：
输入：path = "/a/./b/../../c/"
输出："/c"

```
```js
/**
* @param {string} path
* @return {string}
*/
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
```

