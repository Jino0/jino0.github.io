# 字符串那个串


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
    
- 9、**最长公共前缀【双指针】**👉 [【LeetCode 直通车】：14 最长公共前缀（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Flongest-common-prefix%2F)
    
    ```objectivec
    编写一个函数来查找字符串数组中的最长公共前缀
    如果不存在公共前缀，返回空字符串 ""。
    示例 1：
    
    输入：strs = ["flower","flow","flight"]
    输出："fl"
    示例 2：
    
    输入：strs = ["dog","racecar","car"]
    输出：""
    解释：输入不存在公共前缀。
    
    */**
     * @param {string[]} strs
     * @return {string}
     */*
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
    思路二： 判断字符串2 是否在字符串1 里是否为子串。
    	是：在判断2 是否在3.4.5...n 里
    	否：字符串2 长度减1，再判。判断方法 string.iindexof 返回的下标是否为0
    // GO 语言实现
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
    
- 10**无重复字符的最长子串【双指针】**👉 [【LeetCode 直通车】：3 无重复字符的最长子串（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Flongest-substring-without-repeating-characters%2F)
    
    ```objectivec
    */**
     * @param {string} s
     * @return {number}
     */ //     pwwkew
    右移一直  减减  到重复元素处。取左边的值减减，减至左边元素与右边相等处即，不再减*
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
    
- 11**【面试真题】 最小覆盖子串【滑动窗口】**👉 [【LeetCode 直通车】：76 最小覆盖子串（困难）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fminimum-window-substring%2F)
    
    ```objectivec
    */**
     * @param {string} s
     * @param {string} t
     * @return {string}
     * 给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字母的最小子串。
     *   “ebd”
     *   “eabcdebdfg”
     */
    窗口往右移动，right++。左移动的条件是移动到长度不再相等。*
    var minWindow = function(s, t) {
        let need = {}, window = {};
        for (let c of t) {
            if (!need[c]) need[c] = 1;
            else need[c]++; //need:包含 t 数组的元素的
        }
        let left = 0, right = 0;
        let valid = 0, len = Object.keys(need).length;
        let minLen = s.length + 1, minStr = '';
        while (right < s.length) {
            const d = s[right];
            right++;
            if (!window[d]) window[d] = 1;
            else window[d]++;
            if (need[d] && need[d] === window[d]) {
                valid++;
            }
            console.log('left - right', left, right);
            while (valid === len) {
                if (right - left < minLen) {
                    minLen = right - left;
                    minStr = s.slice(left, right);
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
    

