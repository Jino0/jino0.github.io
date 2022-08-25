# 字符串那个串

本文中介绍些字符串相关的高频算法题，LeetCode 实战分享。

<!--more-->

## 最长回文子串【双指针】
[【LeetCode 直通车】：5 最长回文子串（中等）](https://leetcode-cn.com/problems/longest-palindromic-substring)

给你一个字符串 s，找到 s 中最长的回文子串。

```js
示例 1：
输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。

示例 2：
输入：s = "cbbd"
输出："bb"
```

思路：首先是奇数和偶数的不同，即 aba 和 abba 两种情况，是两种思路和算法。核心是判断**左右两侧是否相等**。     
利用 for 循环开始遍历，从 i 开始依次向左、右，左-k 与 右+k 依次比较，相等就是回文看回文的长度。    
情况二就是从 i 和 i+1 开始依次比较，获取长度。    

```js
var longestPalindrome = function(s) {
    if (s.length === 1) return s;
        let maxRes = 0, maxStr = '';
        for (let i = 0; i < s.length; i++) {
            let str1 = palindrome(s, i, i);
            let str2 = palindrome(s, i, i + 1);   
        if (str1.length > maxRes) {
            maxStr = str1;
            maxRes = str1.length;
        }
        if (str2.length > maxRes) {
            maxStr = str2;
            maxRes = str2.length;
        }
    }
    return maxStr;
};
function palindrome(s, l, r) {
    while (l >= 0 && r < s.length && s[l] === s[r]) {
        l--;
        r++;
    }
    return s.slice(l + 1, r);
}
```
    
## 最长公共前缀【双指针】
[【LeetCode 直通车】：14 最长公共前缀（简单）](https://leetcode-cn.com/problems/longest-common-prefix)
    
```
编写一个函数来查找字符串数组中的最长公共前缀
如果不存在公共前缀，返回空字符串 ""。

示例 1：
输入：strs = ["flower","flow","flight"]
输出："fl"

示例 2：
输入：strs = ["dog","racecar","car"]
输出：""
解释：输入不存在公共前缀。
```
### 遍历两两依次比
拿第一个依次与后面的去取去比较，取公共的最小值即可。
```js
var longestCommonPrefix = function(strs) {
    if (strs.length === 0) return "";
    let first = strs[0];
    if (first === "") return "";
    let minLen = Number.MAX_SAFE_INTEGER;
    for (let i = 1; i < strs.length; i++) {
        const len = twoStrLongestCommonPrefix(first, strs[i]);
        minLen = Math.min(len, minLen);
    }
    return first.slice(0, minLen);
};
function twoStrLongestCommonPrefix (s, t) {
    let i = 0, j = 0;
    let cnt = 0;
    while (i < s.length && j < t.length) {
        console.log(s[i], t[j], cnt)
        if (s[i] === t[j])  {
            cnt++;
        } else {
            return cnt;
        }
        i++;
        j++;
    }
    return cnt;
}
```
### 判断是否为子串
思路二： 判断字符串 2 是否在字符串 1 里是否为子串。
    是：在判断 2 是否在 3.4.5...n 里
    否：字符串 2 长度减 1，再判。判断方法 string.indexof 返回的下标是否为 0
```go
func longestCommonPrefix(strs []string) string {
    if len(strs) < 1 {
        return ""
    }
    prefix := strs[0]
    for _,k := range strs {
        for strings.Index(k,prefix) != 0 {
            if len(prefix) == 0 {
                return ""
            }
            prefix = prefix[:len(prefix) - 1]
        }
    }
    return prefix
}
```

## 无重复字符的最长子串【双指针】
[【LeetCode 直通车】：3 无重复字符的最长子串（中等）](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters)

```js
给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:
输入: s = "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

示例 2:
输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

示例 3:
输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
```
右移一直  减减  到重复元素处。取左边的值减减，减至左边元素与右边相等处即，不再减
```js
var lengthOfLongestSubstring = function(s) {
    let window = {};
    let left = 0, right = 0;
    let maxLen = 0, maxStr = '';
    while (right < s.length) {
        let c = s[right]; //a
        right++;     //1
        if (window[c]) window[c]++; 
        else window[c] = 1
        while (window[c] > 1) {
            let d = s[left];
            left++;
            window[d]--;
        }
        if (maxLen < right - left) {
            maxLen = right - left;
        }
    }
    return maxLen;
};
```
    
## 最小覆盖子串
 [【LeetCode 直通车】：76 最小覆盖子串（困难）](https://leetcode-cn.com/problems/minimum-window-substring)

```js
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
注意：
对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
如果 s 中存在这样的子串，我们保证它是唯一的答案。
 
示例 1：
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"

示例 2：
输入：s = "a", t = "a"
输出："a"

示例 3:
输入: s = "a", t = "aa"
输出: ""
解释: t 中两个字符 'a' 均应包含在 s 的子串中，
因此没有符合条件的子字符串，返回空字符串。
```

```js
var minWindow = function(s, t) {
    let need = {}, window = {};
    for (let c of t) {
        if (!need[c]) need[c] = 1;
        else need[c]++; //need:包含 t 数组的元素的
    }
    let left = 0, right = 0;
    let valid = 0, len = Object.keys(need).length;
    let minLen = s.length + 1, minStr = '';
    while (right < s.length) {  // "ADOBECODEBANC", t = "ABC"
        const d = s[right];              l    r
        right++;
        if (!window[d]) window[d] = 1;
        else window[d]++;
        if (need[d] && need[d] === window[d]) {
            valid++;
        }
        console.log('left - right', left, right);
        while (valid === len) {
            if (right - left < minLen) {
                minLen = right - left;         // 5
                minStr = s.slice(left, right); //ADOBEC   CODEBA
            }
            
            let c = s[left];
            left++;
            window[c]--;
            if (need[c] && window[c] < need[c]) {
                valid--;
            }
        }
    }
    return minStr;
};
```


