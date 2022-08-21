---
draft: true
---
<!--more-->

字节跳动最爱考的 64 道算法题（JS版）本篇内容包括如下模块：

### **高频算法题系列：链表**

- 1、**前序遍历判断回文链表** 👉 [【LeetCode 直通车】：234 回文链表（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fpalindrome-linked-list%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/6688ac7d-f4c7-44a8-bd87-37b6284bb457/Untitled.png)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/bf24ddd9-3ef8-4a5e-91ee-1f500f004638/Untitled.png)
    
    ```cpp
    **题解1**
    利用链表的后续遍历，使用函数调用栈作为后序遍历栈，来判断是否回文
    /**
     * Definition for singly-linked list.
     * function ListNode(val, next) {
     *     this.val = (val===undefined ? 0 : val)
     *     this.next = (next===undefined ? null : next)
     * }
     */
    /**
     * @param {ListNode} head
     * @return {boolean}
     */
    
    let left ;
    var isPalindrome = function(head) {
        left = head;
        return traverse(head);
    };
    
    function traverse(right) {
        if (right == null) return true;
        let res = traverse(right.next);
        res = res && (right.val === left.val);
        left = left.next;
        return res;
    }
    **题解2**
    通过 快、慢指针找链表中点，然后反转链表，比较两个链表两侧是否相等，来判断是否是回文链表→点击展开查看
    var isPalindrome = function(head) {
        *// 反转 slower 链表*
    		let right = reverse(findCenter(head));
        let left = head;
        *// 开始比较*
    		while (right != null) {
            if (left.val !== right.val) {
                return false;
            }
            left = left.next;
            right = right.next;
        }
        return true;
    }
    function findCenter(head) {
        let slower = head, faster = head;
        while (faster && faster.next != null) {
            slower = slower.next;
            faster = faster.next.next;
        }
        *// 如果 faster 不等于 null，说明是奇数个，slower 再移动一格*
    		if (faster != null) {
            slower = slower.next;
        }
        return slower;
    }
           ->     ->
    prev cur next
    		<-							next
    				pre      
    function reverse(head) {
        let prev = null, cur = head, nxt = head;
        while (cur != null) {
            nxt = cur.next;
            cur.next = prev;
            prev = cur;
            cur = nxt;
        }
        return prev;
    }
    ```
    
- **2、反转链表**👉 [【LeetCode 直通车】：206 反转链表（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Freverse-linked-list%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/f36b2010-e3db-4848-8dff-9da9b890b8f2/Untitled.png)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/08eba000-068f-40f4-8a5d-9c3eaaf1ecff/Untitled.png)
    
    ```cpp
    */**
     * Definition for singly-linked list.
     * function ListNode(val) {
     *     this.val = val;
     *     this.next = null;
     * }
     *//**
     * @param {ListNode} head
     * @return {ListNode}
     */*
    var reverseList = function(head) {
        if (head == null || head.next == null) return head;
        let last = reverseList(head.next);
        head.next.next = head;
        head.next = null;
        return last;
    };
    var reverseList = function(head) {
        let prev = null, cur = head, nxt = head;
        while (cur != null) {
            nxt = cur.next;
            cur.next = prev;
            prev = cur;
            cur = nxt;
        }
        return prev;
    };
    ```
    
- **3、合并K个升序链表**👉 [【LeetCode 直通车】：23 合并K个升序链表（困难）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fmerge-k-sorted-lists%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/4dc84945-1092-45da-a34d-6ec3538cc749/Untitled.png)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/dee02044-7052-4d3e-9cd1-a9d5a25d2c89/Untitled.png)
    
    ```cpp
    */**
     * Definition for singly-linked list.
     * function ListNode(val) {
     *     this.val = val;
     *     this.next = null;
     * }
     *//**
     * @param {ListNode[]} lists
     * @return {ListNode}
     */*
    var mergeKLists = function(lists) {
        if (lists.length === 0) return null;
        return mergeArr(lists);
    };
    function mergeArr(lists) {
        if (lists.length <= 1) return lists[0];
        let index = Math.floor(lists.length / 2);
        const left = mergeArr(lists.slice(0, index))
        const right = mergeArr(lists.slice(index));
        return merge(left, right);
    }
    function merge(l1, l2) {
        if (l1 == null && l2 == null) return null;
        if (l1 != null && l2 == null) return l1;
        if (l1 == null && l2 != null) return l2;
        let newHead = null, head = null;
        while (l1 != null && l2 != null) {
            if (l1.val < l2.val) {
                if (!head) {
                    newHead = l1;
                    head = l1;
                } else {
                    newHead.next = l1;
                    newHead = newHead.next;
                }
                l1 = l1.next;
            } else {
                if (!head) {
                    newHead = l2;
                    head = l2;
                } else {
                    newHead.next = l2;
                    newHead = newHead.next;
                }
                l2 = l2.next;
            }
        }
        newHead.next = l1 ? l1 : l2;
        return head;
    }
    ```
    
- **4、K 个一组翻转链表**👉 [【LeetCode 直通车】：25 K 个一组翻转链表（困难）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Freverse-nodes-in-k-group%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/5ee2e2e5-cf38-4428-a021-e33b326061c3/Untitled.png)
    
    ```cpp
    */**
     * Definition for singly-linked list.
     * function ListNode(val) {
     *     this.val = val;
     *     this.next = null;
     * }
     *//**
     * @param {ListNode} head
     * @param {number} k
     * @return {ListNode}
     */*
    var reverseKGroup = function(head, k) {
        let a = head, b = head;
        for (let i = 0; i < k; i++) {
            if (b == null) return head;
            b = b.next;
        }
        const newHead = reverse(a, b);
        a.next = reverseKGroup(b, k);
        return newHead;
    };
    function reverse(a, b) {
        let prev = null, cur = a, nxt = a;
        while (cur != b) {
            nxt = cur.next;
            cur.next = prev;
            prev = cur;
            cur = nxt;
        }
        return prev;
    }
    ```
    
- **5、环形链表** 👉 [【LeetCode 直通车】：141 环形链表（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Flinked-list-cycle%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/fa49bc7c-7e96-460a-b50f-8886e453a956/Untitled.png)
    
    ```cpp
    */**
     * Definition for singly-linked list.
     * function ListNode(val) {
     *     this.val = val;
     *     this.next = null;
     * }
     *//**
     * @param {ListNode} head
     * @return {boolean}
     */*
    var hasCycle = function(head) {
        if (head == null || head.next == null) return false;
        let slower = head, faster = head;
        while (faster != null && faster.next != null) {
            slower = slower.next;
            faster = faster.next.next;
            if (slower === faster) return true;
        }
        return false;
    };
    ```
    
- 6、**排序链表**👉 [【LeetCode 直通车】：148 排序链表（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fsort-list%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/32fe8667-1025-466e-aaf8-32d9894eccab/Untitled.png)
    
    ```cpp
    */**
     * Definition for singly-linked list.
     * function ListNode(val) {
     *     this.val = val;
     *     this.next = null;
     * }
     *//**
     * @param {ListNode} head
     * @return {ListNode}
     */*
    var sortList = function(head) {
        if (head == null) return null;
        let newHead = head;
        return mergeSort(head);
    };
    function mergeSort(head) {
        if (head.next != null) {
            let slower = getCenter(head);
            let nxt = slower.next;
            slower.next = null;
            console.log(head, slower, nxt);
            const left = mergeSort(head);
            const right = mergeSort(nxt);
            head = merge(left, right);
        }
        return head;
    }
    function merge(left, right) {
        let newHead = null, head = null;
        while (left != null && right != null) {
            if (left.val < right.val) {
                if (!head) {
                    newHead = left;
                    head = left;
                } else {
                    newHead.next = left;
                    newHead = newHead.next;
                }
                left = left.next;
            } else {
                if (!head) {
                    newHead = right;
                    head = right;
                } else {
                    newHead.next = right;
                    newHead = newHead.next;
                }
                right = right.next;
            }
        }
        newHead.next = left ? left : right;
        return head;
    }
    function getCenter(head) {
        let slower = head, faster = head.next;
        while (faster != null && faster.next != null) {
            slower = slower.next;
            faster = faster.next.next;
        }
        return slower;
    }
    ```
    
- **7、相交链表**👉 [【LeetCode 直通车】：160 相交链表（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fintersection-of-two-linked-lists%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/02dcddcc-5c37-43bb-907c-f4ab617983c5/Untitled.png)
    
    ```cpp
    */**
     * Definition for singly-linked list.
     * function ListNode(val) {
     *     this.val = val;
     *     this.next = null;
     * }
     *//**
     * @param {ListNode} headA
     * @param {ListNode} headB
     * @return {ListNode}
     */*
    var getIntersectionNode = function(headA, headB) {
        let lastHeadA = null;
        let lastHeadB = null;
        let originHeadA = headA;
        let originHeadB = headB;
        if (!headA || !headB) {
            return null;
        }
        while (true) {
            if (headB == headA) {
                return headB;
            }
            if (headA && headA.next == null) {
                lastHeadA = headA;
                headA = originHeadB;
            } else {
                headA = headA.next;
            }
            if (headB && headB.next == null) {
                lastHeadB = headB
                headB = originHeadA;
            } else {
                headB = headB.next;
            }
            if (lastHeadA && lastHeadB && lastHeadA != lastHeadB) {
                return null;
            }
        }
        return null;
    };
    ```
    

### **【🔥】高频算法题系列：字符串**

- 8、**【面试真题】最长回文子串【双指针】**👉 [【LeetCode 直通车】：5 最长回文子串（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Flongest-palindromic-substring%2F)
    
    ```objectivec
    给你一个字符串 s，找到 s 中最长的回文子串。
    
    示例 1：
    输入：s = "babad"
    输出："bab"
    解释："aba" 同样是符合题意的答案。
    
    示例 2：
    输入：s = "cbbd"
    输出："bb"
    */**
     * @param {string} s
     * @return {string}
     */*
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
    

### **【🔥】高频算法题系列：数组问题**

- 12**【面试真题】俄罗斯套娃信封问题**👉 [【LeetCode 直通车】：354 俄罗斯套娃信封问题（困难）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Frussian-doll-envelopes%2F)
    
    ```objectivec
    给定一些标记了宽度和高度的信封，宽度和高度以整数对形式 (w, h) 出现。当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。
    
    请计算最多能有多少个信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。
    
    说明: 不允许旋转信封。
    */*****【排序+最长上升子序列】**
     ** @param {number[][]} envelopes
     * @return {number}
     */*
    var maxEnvelopes = function(envelopes) {
    	  if (envelopes.length === 1) return 1;
        envelopes.sort((a, b) => {
            if (a[0] !== b[0]) return a[0] - b[0];
            else return b[1] - a[1];
        });
        let LISArr = [];
        for (let [key, value] of envelopes) {
    	      LISArr.push(value);
        }
        console.log( LISArr);
        return LIS(LISArr);
    };
    // w: 2 -> 3 -> 4 -> 4 -> 5 -> 6
    // h: 4 -> 2 -> 2 -> 3 -> 6 -> 5
    // [最长上升子序列](https://www.geekxh.com/1.2.动态规划系列/203.html#_01、题目分析)
    function LIS(arr) {
    	  let dp = [];  // dp[i]表示以arr[i]结尾的最长递增子序列
    	  let maxAns = 0;
    	  for (let i = 0; i < arr.length; i++) {
    		    dp[i] = 1;
    	  }
    	  for (let i = 1; i < arr.length; i++) {
    		    for (let j = i; j >= 0; j--) {
    			      if (arr[i] > arr[j]) {
    				        dp[i] = Math.max(dp[i], dp[j] + 1)
    			      }
    			      maxAns = Math.max(maxAns, dp[i]);
    							// 一轮从零开始的循环即可。。。
    					// if (nums[i + 1] > nums[i]) { // 连续记录
    					//		dp[i + 1] = dp[i] + 1;
    					// }
    					// result = Math.max(result, dp[i + 1]);
    		    }
    	  }
    	  return maxAns;
    }
    ```
    
- 13**最长连续递增序列【快慢指针】**👉 [【LeetCode 直通车】：674 最长连续递增序列（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Flongest-continuous-increasing-subsequence%2F)
    
    ```objectivec
    给定一个未经排序的整数数组，找到最长且 连续递增的子序列，并返回该序列的长度。
    
    连续递增的子序列 可以由两个下标 l 和 r（l < r）确定，如果对于每个 l <= i < r，都有 nums[i] < nums[i + 1] ，那么子序列 [nums[l], nums[l + 1], ..., nums[r - 1], nums[r]] 就是连续递增子序列。
    
    示例 1：
    输入：nums = [1,3,5,4,7]
    输出：3
    解释：最长连续递增序列是 [1,3,5], 长度为3。
    尽管 [1,3,5,7] 也是升序的子序列, 但它不是连续的，因为 5 和 7 在原数组里被 4 隔开。
    */**
     * @param {number[]} nums
     * @return {number}
     */*
    var findLengthOfLCIS = function(nums) {
        if (nums.length === 0) return 0;
        const n = nums.length;
        let left = 0, right = 1;
        let globalMaxLen = 1, maxLen = 1;
        while (right < n) {
            if (nums[right] > nums[left]) maxLen++;
            else {
                maxLen = 1;
            }
            left++;
            right++;
            globalMaxLen = Math.max(globalMaxLen, maxLen);
        }
        return globalMaxLen;
    };
    // 动态规划解法
    // 与最长子序列相比多了个连续，也正是多了这个连续得：不用再遍历之前的取最大值了，只比较前面一个就行，也就变成了纸哟一轮循环即可解决问题。
    var findLengthOfLCISCIS = function (nums) {
    		if (nums.length === 0) return;
    		console.log(nums.length)
    		let result=1;
    		let dp = [];
    		for (let i = 0; i < nums.length; i++) {
    				dp[i] = 1;
    		}
    		for (let i = 0; i < nums.length - 1; i++) {
    				if (nums[i + 1] > nums[i]) { // 连续记录
    					dp[i + 1] = dp[i] + 1;
    				}
    				if (dp[i + 1] > result) result = dp[i + 1];
    		}
    		return result;
    }
    class Solution {
    public:
        int findLengthOfLCIS(vector<int>& nums) {
            if (nums.size() == 0) return 0;
            int result = 1;
            vector<int> dp(nums.size() ,1);
            for (int i = 0; i < nums.size() - 1; i++) {
                if (nums[i + 1] > nums[i]) { // 连续记录
                    dp[i + 1] = dp[i] + 1;
                }
                if (dp[i + 1] > result) result = dp[i + 1];
            }
            return result;
        }
    };
    ```
    
- 14**最长连续序列 【哈希表】**👉 [【LeetCode 直通车】：128 最长连续序列（困难）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Flongest-consecutive-sequence%2F)
    
    ```objectivec
    给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
    请你设计并实现时间复杂度为 O(n) 的算法解决此问题。
    输入：nums = [100,4,200,1,3,2]
    输出：4
    解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。
    // 查找是否连续，即查找 +1 或 -1 是否存在，查找用哈希
    // 双层循环的查找可以解决问题，但是时间复杂度 n^2
    // 优化：尽可能从最小值开始找，怎么尽可能，存在 -1 的数，肯定不是最小。
    */**
     * @param {number[]} nums
     * @return {number}
     */*
    var longestConsecutive = function(nums) {
        if (nums.length === 0) return 0;
        const set = new Set(nums);
        const n = nums.length;
        let globalLongest = 1;
        for (let i = 0; i < n; i++) {
            if (!set.has(nums[i] - 1)) {
                let longest = 1;
                let currentNum = nums[i];
                while (set.has(currentNum + 1)) {
                    currentNum += 1;
                    longest++;
                }
                globalLongest = Math.max(globalLongest, longest);
            }
        }
        return globalLongest;
    };
    ```
    

---

- 15**【面试真题】盛最多水的容器【哈希表】**👉 [【LeetCode 11】： 盛最多水的容器（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fcontainer-with-most-water%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/09a062c3-d1bc-4fd3-94c4-01f7885ecd94/Untitled.png)
    
    ```cpp
    // 双循环肯定能借=解，但是肯定不是最优方案
    // 双头往中间走，双层循环变单层循环，走的条件即 放弃短的那个，短的装水少
    */**
     * @param {number[]} height
     * @return {number}
     */*
    var maxArea = function(height) {
        let n = height.length;
        let left = 0, right = n - 1;
        let maxOpacity = 0;
        while (left < right) {
            let res = Math.min(height[left], height[right]) * (right - left);
            maxOpacity = Math.max(maxOpacity, res);
            if (height[left] < height[right]) left++
            else right--;
        }
        return maxOpacity;
    };
    ```
    
- 16**寻找两个正序数组的中位数【双指针】**👉 [LeetCode 4 寻找两个正序数组的中位数（困难）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fmedian-of-two-sorted-arrays%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/61967f60-da00-4075-99f5-91d46f474aa5/Untitled.png)
    
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
    
- 17**删除有序数组中的重复项【快慢指针】**👉 [【LeetCode 26】删除有序数组中的重复项（简单](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fremove-duplicates-from-sorted-array%2F))
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/f7ea396d-7fbb-407d-a05f-b49748d684a6/Untitled.png)
    
    ```cpp
    */**
     * @param {number[]} nums
     * @return {number}
     */*
    var removeDuplicates = function(nums) {
    	  if (nums.length <= 1) return nums.length;
    	  let lo = 0, hi = 0;
    	  while (hi < nums.length) {
    		    while (nums[lo] === nums[hi] && hi < nums.length) hi++;
    		    if (nums[lo] !== nums[hi] && hi < nums.length) {
    			      lo++;
    			      nums[lo] = nums[hi];
    		    }
    		    hi++;
    	  }
    	  return lo + 1;
    };
    ```
    
- 18、**和为K的子数组【哈希表】**👉 [【LeetCode 560】：和为K的子数组（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fsubarray-sum-equals-k%2F)
    
    ```cpp
    给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。
    */**
     * @param {number[]} nums
     * @param {number} k
     * @return {number}
     */
    var subarraySum = function(nums, k) {
        const mp = new Map();
        mp.set(0, 1);
        let count = 0, pre = 0;
        for (const x of nums) {
            pre += x;
            if (mp.has(pre - k)) {
                count += mp.get(pre - k);
            }
            if (mp.has(pre)) {
                mp.set(pre, mp.get(pre) + 1);
            } else {
                mp.set(pre, 1);
            }
        }
        return count;
    };*
    ```
    

19**nSum问题【哈希表】【系列】**

- 👉 [【LeetCode 直通车】：1 两数之和（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Ftwo-sum%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/e16db3a8-63a1-4ca3-b13a-97714b06eb6e/Untitled.png)
    
    ```cpp
    *1、两数之和*
    var twoSum = function(nums, target) {
    		let map2 = new Map();
    		for (let i = 0; i < nums.length; i++) {
    				map2.set(nums[i], i);
    		}
    		for (let i = 0; i < nums.length; i++) {
    				if (map2.has(target - nums[i]) && map2.get(target - nums[i]) !== i)
    						return [i, map2.get(target - nums[i])]
    		}
    };
    ```
    

• 👉 [【LeetCode 直通车】：167 两数之和 II - 输入有序数组（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Ftwo-sum-ii-input-array-is-sorted%2F)
• 👉 [【LeetCode 直通车】：15 三数之和（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2F3sum%2F)

- 👉 [【LeetCode 直通车】：18 四数之和（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2F4sum%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/8f3a40ef-1390-453c-9e93-d939b8608fa1/Untitled.png)
    
    ```cpp
    */**
     * @param {number[]} nums
     * @param {number} target
     * @return {number[]}
     */*
    18、四数之和
    var fourSum = function(nums, target) {
        const quadruplets = [];
        if (nums.length < 4) {
            return quadruplets;
        }
        nums.sort((x, y) => x - y);
        const length = nums.length;
        for (let i = 0; i < length - 3; i++) {
            if (i > 0 && nums[i] === nums[i - 1]) {
                continue;
            }
            if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) {
                break;
            }
            if (nums[i] + nums[length - 3] + nums[length - 2] + nums[length - 1] < target) {
                continue;
            }
            for (let j = i + 1; j < length - 2; j++) {
                if (j > i + 1 && nums[j] === nums[j - 1]) {
                    continue;
                }
                if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) {
                    break;
                }
                if (nums[i] + nums[j] + nums[length - 2] + nums[length - 1] < target) {
                    continue;
                }
                let left = j + 1, right = length - 1;
                while (left < right) {
                    const sum = nums[i] + nums[j] + nums[left] + nums[right];
                    if (sum === target) {
                        quadruplets.push([nums[i], nums[j], nums[left], nums[right]]);
                        while (left < right && nums[left] === nums[left + 1]) {
                            left++;
                        }
                        left++;
                        while (left < right && nums[right] === nums[right - 1]) {
                            right--;
                        }
                        right--;
                    } else if (sum < target) {
                        left++;
                    } else {
                        right--;
                    }
                }
            }
        }
        return quadruplets;
    };
    ```
    
- 20**【面试真题】接雨水【暴力+备忘录优化】**👉 [【LeetCode 直通车】：42 接雨水（困难](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Ftrapping-rain-water%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/6675c10c-ea70-4c99-b509-f66a3b93889d/Untitled.png)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/439190d7-b292-49ec-8509-1b8e77518783/Untitled.png)
    
    ```cpp
    heigh: 0 1 0 2 1 0 1 3 2 1 2 1
    l_max: [0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3]
    r_max: [3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 1]
    max  : 001 012 100 100
    */**
     * @param {number[]} height
     * @return {number}
     */*
    var trap = function(height) {
        let l_max = [], r_max = [];
        let len = height.length;
        let maxCapacity = 0;
        for (let i = 0; i < len; i++) {
            l_max[i] = height[i];
            r_max[i] = height[i];
        }
        for (let i = 1; i < len; i++) {
            l_max[i] = Math.max(l_max[i - 1], height[i]);
        }
        for (let j = len - 2; j >= 0; j--) {
            r_max[j] = Math.max(r_max[j + 1], height[j]);
        }
        for (let i = 0; i < len; i++) {
            maxCapacity += Math.min(l_max[i], r_max[i]) - height[i];
        }
        return maxCapacity;
    };
    ```
    

### **跳跃游戏【贪心算法】【系列】**

- 21• 👉 [【LeetCode 直通车】：55 跳跃游戏（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fjump-game%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/2575bdd1-5fe2-49f0-92d9-ff40768c4490/Untitled.png)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/86b499b6-8ff8-4585-ac77-ebd7f670206c/Untitled.png)
    
    ```cpp
    */**
     * @param {number[]} nums
     * @return {boolean}
     */*
    var canJump = function(nums) {
        let faster = 0;
        for (let i = 0; i < nums.length - 1; i++) {
            faster = Math.max(faster, i + nums[i]);
            if (faster <= i) return false;
        }
        return faster >= nums.length - 1;
    };
    ```
    

• 👉 [【LeetCode 直通车】：45 跳跃游戏 II（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fjump-game-ii%2F)

### **高频算法题系列：二叉树**

- **22、二叉树的最近公共祖先【二叉树】**👉 [【LeetCode 236】 二叉树的最近公共祖先（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Flowest-common-ancestor-of-a-binary-tree%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/36ccc5d3-4d00-4513-9211-827828beff47/Untitled.png)
    
    ```cpp
    */**
     * Definition for a binary tree node.
     * function TreeNode(val) {
     *     this.val = val;
     *     this.left = this.right = null;
     * }
     *//**
     * @param {TreeNode} root
     * @param {TreeNode} p
     * @param {TreeNode} q
     * @return {TreeNode}
     */*
    let visited;let parent;
    var lowestCommonAncestor = function(root, p, q) {
        visited = new Set();
        parent = new Map();
        dfs(root);
        while (p != null) {
            visited.add(p.val);
            p = parent.get(p.val);
        }
        while (q != null) {
            if (visited.has(q.val)) {
                return q;
            }
            q = parent.get(q.val);
        }
        return null;
    };
    function dfs(root) {
        if (root.left != null) {
            parent.set(root.left.val, root);
            dfs(root.left);
        }
        if (root.right != null) {
            parent.set(root.right.val, root);
            dfs(root.right);
        }
    }
    ```
    
- **23、二叉搜索树中的搜索【二叉树】**👉 [【LeetCode 700】 二叉搜索树中的搜索（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fsearch-in-a-binary-search-tree%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/940d2ac7-2c46-4b62-b8db-15e68c48189e/Untitled.png)
    
    ```cpp
    */**
     * Definition for a binary tree node.
     * function TreeNode(val) {
     *     this.val = val;
     *     this.left = this.right = null;
     * }
     *//**
     * @param {TreeNode} root
     * @param {number} val
     * @return {TreeNode}
     */*
    var searchBST = function(root, val) {
        if (root == null) return null;
        if (root.val === val) return root;
        if (root.val > val) {
            return searchBST(root.left, val);
        } else if (root.val < val) {
            return searchBST(root.right, val);
        }
    };
    ```
    
- **24、删除二叉搜索树中的节点【二叉树】**👉 [【LeetCode 450】 删除二叉搜索树的节点（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fdelete-node-in-a-bst%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/f23ffdda-9147-471a-9081-7728e57e7445/Untitled.png)
    
    ```cpp
    */**
     * Definition for a binary tree node.
     * function TreeNode(val) {
     *     this.val = val;
     *     this.left = this.right = null;
     * }
     *//**
     * @param {TreeNode} root
     * @param {number} key
     * @return {TreeNode}
     */
    // 做的最后*
    var deleteNode = function(root, key) {
        if (root == null) return null;
        if (root.val === key) {
            if (root.left == null && root.right == null) return null;
            if (root.left == null) return root.right;
            if (root.right == null) return root.left;
            if (root.left != null && root.right != null)  {// 左的最右，或右的最左
                let target = getMinTreeMaxNode(root.left);
                root.val = target.val;
                root.left = deleteNode(root.left, target.val);
            }
        }
        if (root.val < key) {
            root.right = deleteNode(root.right, key);
        } else if (root.val > key) {
            root.left = deleteNode(root.left, key);
        }
        return root;
    };
    function getMinTreeMaxNode(root) {   
        if (root.right == null) return root;
        return getMinTreeMaxNode(root.right);
    }
    // 右的最左
    var deleteNode = function(root, key) {
        if (root == null) return null;
        if (root.val === key) {
            if (root.left == null && root.right == null) return null;
            if (root.left == null) return root.right;
            if (root.right == null) return root.left;
            if (root.left != null && root.right != null)  {
                let target = getMinTreeMaxNode(root.right);
                root.val = target.val;
                root.right = deleteNode(root.right, target.val);
            }
        }
        if (root.val < key) {
            root.right = deleteNode(root.right, key);
        } else if (root.val > key) {
            root.left = deleteNode(root.left, key);
        }
        return root;
    };
    function getMinTreeMaxNode(root) {
        if (root.left == null) return root;
        return getMinTreeMaxNode(root.left);
    }
    ```
    
- **25、完全二叉树的节点个数【二叉树】**👉 [【LeetCode 222】 完全二叉树的节点个数（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fcount-complete-tree-nodes%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/7783c86b-2341-4f76-a1b2-8d8c9f285e1c/Untitled.png)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/b059e816-60da-4907-8124-29b02f2236ae/Untitled.png)
    
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
    var countNodes = function(root) {
        if (root == null) return 0;
        let l = root, r = root;
        let lh = 0, rh = 0;
        while (l != null) {
          l = l.left;
          lh++;
        }
        while (r != null) {
          r = r.right;
          rh++;
        }
        if (lh === rh) {
          return Math.pow(2, lh) - 1;
        }
        return 1 + countNodes(root.left) + countNodes(root.right);
    };
    ```
    
- **26、二叉树的锯齿形层序遍历【二叉树】**👉 [【LeetCode 103】锯齿形层序遍历（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fbinary-tree-zigzag-level-order-traversal%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/59d5c6ce-bd07-4f2a-9ddc-f7a158d30cd2/Untitled.png)
    
    ```cpp
    */**
     * Definition for a binary tree node.
     * function TreeNode(val) {
     *     this.val = val;
     *     this.left = this.right = null;
     * }
     *//**
     * @param {TreeNode} root
     * @return {number[][]}
     */*
    let res;
    var zigzagLevelOrder = function(root) {
        if (root == null) return [];
        res = [];
        BFS(root, true);
        return res;
    };
    function BFS(root, inOrder) {
        let resItem = []; let node;
        let stack1 = new Stack(); let stack2 = new Stack();
        *// 判断交换时机*
    		let flag;
        stack1.push(root); res.push([root.val]);
        inOrder = !inOrder;
        while (!stack1.isEmpty() || !stack2.isEmpty()) {
            if (stack1.isEmpty()) flag = 'stack1';
            else if (stack2.isEmpty()) flag = 'stack2';
            *// 决定取那个栈里面的元素*
    				if (flag === 'stack2' && !stack1.isEmpty()) node = stack1.pop();
            else if (flag === 'stack1' && !stack2.isEmpty()) node = stack2.pop();
            if (inOrder) {
                if (node.left) {
                    if (flag === 'stack1') stack1.push(node.left);
                    else stack2.push(node.left)
                    resItem.push(node.left.val);
                }
                if (node.right) {
                    if (flag === 'stack1') stack1.push(node.right);
                    else stack2.push(node.right);
                    resItem.push(node.right.val);
                }
            } else {
                if (node.right) {
                    if (flag === 'stack1') stack1.push(node.right);
                    else stack2.push(node.right);
                    resItem.push(node.right.val);
                }
                if (node.left) {
                    if (flag === 'stack1') stack1.push(node.left);
                    else stack2.push(node.left);
                    resItem.push(node.left.val);
                }
            }
            *// 判断下次翻转的时机*
    				if ((flag === 'stack2' && stack1.isEmpty()) || (flag === 'stack1' && stack2.isEmpty())) {
                inOrder = !inOrder;
                *// 需要翻转了，就加一轮值*
    					  if (resItem.length > 0) res.push(resItem);
                resItem = [];
            }
        }
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
    

### **【🔥】高频算法题系列：排序算法**

- **27、用最少数量的箭引爆气球【排序算法】**👉 [【LeetCode 451】最少数量的箭（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fminimum-number-of-arrows-to-burst-balloons%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/71e490dc-1607-466e-afec-a7dcac4171d4/Untitled.png)
    
    ```cpp
    [1,6][2,8][7,12][10,16]
    */**
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
    
- **28、合并区间【排序算法+区间问题】**👉 [【LeetCode 56】 合并区间（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fmerge-intervals%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/5b783814-3933-4037-bd6f-8e539a269a25/Untitled.png)
    
    ```cpp
    intervals = [[1,3],[2,6],[8,10],[15,18]]
    */**
     * @param {number[][]} intervals
     * @return {number[][]}
     */*
    var merge = function(intervals) {
        if (intervals.length === 0) return [];
        intervals.sort((a, b) => a[0] - b[0]);
        let mergeArr = [intervals[0]];
        let last, curr;
        for (let j = 1; j < intervals.length; j++) {
            last = mergeArr[mergeArr.length - 1];
            curr = intervals[j];
    				// last[1] : 已合并的最右(最大)
    				// curr[0] : 待合并的最左(最小) 
            if (last[1] >= curr[0]) { 
                last[1] = Math.max(curr[1], last[1]);
            } else {
                mergeArr.push(curr);
            }
        }
        return mergeArr;
    };
    ```
    

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
    

### **【🔥】高频算法题系列：动态规划**

- **32、最长递增子序列【动态规划】**👉 [【LeetCode 300】 最长递增子序列（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Flongest-increasing-subsequence%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/a747c76c-d944-46ba-9de0-96c3e4876cc7/Untitled.png)
    
    ```cpp
    */**
     * @param {number[]} nums
     * @return {number}
     */*
    var lengthOfLIS = function(nums) {
        let maxLen = 0, n = nums.length;
        let dp = [];
        for (let i = 0; i < n; i++) {
            dp[i] = 1;
        }
        for (let i = 0; i < n; i++) {
            for (let j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = Math.max(dp[i], dp[j] + 1);
                }
            }
            maxLen = Math.max(maxLen, dp[i]);
        }
        return maxLen;
    };
    ```
    
- **33、【面试真题】 零钱兑换【动态规划】**👉 [【LeetCode 322】 零钱兑换（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fcoin-change%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/e01c7d81-cf7f-4a72-94c3-6fdaa0ea0cf4/Untitled.png)
    
    ```cpp
    */**
     * @param {number[]} coins
     * @param {number} amount
     * @return {number}
     */*
    var coinChange = function(coins, amount) {
    	  if (amount === 0) return 0;
    	  let dp = [];
    	  for (let i = 0; i <= amount; i++) {
    		    dp[i] = amount + 1;
    	  }
    	  dp[0] = 0;
    	  for (let i = 0; i <= amount; i++) {
    		    for (let j = 0; j < coins.length; j++) {
    			      if (i >= coins[j]) { 1>=1 2>=1
    								// dp[1]=1 dp[2]=1 dp[5]=1 
    				        dp[i] = Math.min(dp[i - coins[j]] + 1, dp[i])
    			      }
    		    }
    	  }
    	  return dp[amount] === amount + 1 ? -1 : dp[amount];
    };
    ```
    
- **34X【面试真题】 最长公共子序列【动态规划】**👉 [【LeetCode 1143】 最长公共子序列（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Flongest-common-subsequence%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/e07fc339-5ee0-480d-9d99-7bb727b52f1d/Untitled.png)
    
    ```cpp
    */**
     * @param {string} text1
     * @param {string} text2
     * @return {number}
     */
    var longestCommonSubsequence = function(text1, text2) {
        const m = text1.length, n = text2.length;
        const dp = new Array(m + 1).fill(0).map(() => new Array(n + 1).fill(0));
        for (let i = 1; i <= m; i++) {
            const c1 = text1[i - 1];
            for (let j = 1; j <= n; j++) {
                const c2 = text2[j - 1];
                if (c1 === c2) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    };*
    ```
    
- **35X编辑距离【动态规划】**👉 [【LeetCode 直通车】：72 编辑距离（困难）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fedit-distance%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/74728090-0ea9-4102-822f-28874345e3c9/Untitled.png)
    
    ```cpp
    */**
     * @param {string} word1
     * @param {string} word2
     * @return {number}
     */*
    var minDistance = function(word1, word2) {
      let len1 = word1.length, len2 = word2.length;
      let dp = [];
      for (let i = 0; i <= len1; i++) {
        dp[i] = [];
        for (let j = 0; j <= len2; j++) {
          dp[i][j] = 0;
          if (i === 0) {
            dp[i][j] = j;
          }
          if (j === 0) {
            dp[i][j] = i;
          }
        }
      }
      for (let i = 1; i <= len1; i++) {
        for (let j = 1; j <= len2; j++) {
          if (word1[i - 1] === word2[j - 1]) {
            dp[i][j] = dp[i - 1][j - 1];
          } else {
            dp[i][j] = Math.min(dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1);
          }
        }
      }
      return dp[len1][len2];
    };
    
    复制代码
    ```
    
- **36X【面试真题】最长回文子序列【动态规划】**👉 [【LeetCode 516】最长回文子序列（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Flongest-palindromic-subsequence%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/62f794df-839d-453f-8ae5-9ecc1f197ea7/Untitled.png)
    
    ```cpp
    */**
     * @param {string} s
     * @return {number}
     */*var longestPalindromeSubseq = function(s) {
        let dp = [];
        for (let i = 0; i < s.length; i++) {
            dp[i] = [];
            for (let j = 0; j < s.length; j++) {
                dp[i][j] = 0;
            }
            dp[i][i] = 1;
        }
        for (let i = s.length - 1; i >= 0; i--) {
            for (let j = i + 1; j < s.length; j++) {
                if (s[i] === s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = Math.max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][s.length - 1];
    };
    
    复制代码
    ```
    
- **37X【面试真题】💁 最大子序和【动态规划】**👉 [【LeetCode 53】最大子序和（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fmaximum-subarray%2F)
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/e43a7096-b458-4597-8d57-1388aeb8b3a2/Untitled.png)
    
    ```cpp
    */**
     * @param {number[]} nums
     * @return {number}
     */*var maxSubArray = function(nums) {
        let maxSum = -Infinity;
        let dp = [], n = nums.length;
        for (let i = -1; i < n; i++) {
            dp[i] = 0;
        }
        for (let i = 0; i < n; i++) {
            dp[i] = Math.max(nums[i], dp[i - 1] + nums[i]);
            maxSum = Math.max(maxSum, dp[i]);
        }
        return maxSum;
    };
    
    复制代码
    ```
    

**38X【面试真题】💁 买卖股票的最佳时机【动态规划】**

- 👉 [【LeetCode 直通车】：121 买卖股票的最佳时机（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fcontainer-with-most-water%2F)【面试真题】
    
    ![Untitled](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/ce9ad51b-483b-4cb9-854f-3e4c5fc9fe10/Untitled.png)
    
    ```cpp
    */**
     * @param {number[]} prices
     * @return {number}
     */*var maxProfit = function(prices) {
      let dp = [];
      for (let i = -1; i < prices.length; i++) {
        dp[i] = []
        for (let j = 0; j <= 1; j++) {
          dp[i][j] = [];
          dp[i][j][0] = 0;
          dp[i][j][1] = 0;
          if (i === -1) {
            dp[i][j][1] = -Infinity;
          }
          if (j === 0) {
            dp[i][j][1] = -Infinity;
          }
          if (j === -1) {
            dp[i][j][1] = -Infinity;
          }
        }
      }
      for (let i = 0; i < prices.length; i++) {
        for (let j = 1; j <= 1; j++) {
          dp[i][j][0] = Math.max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
          dp[i][j][1] = Math.max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
        }
      }
      return dp[prices.length - 1][1][0];
    };
    
    复制代码
    ```
    

• 👉 [【LeetCode 直通车】：122 买卖股票的最佳时机 II（简单）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fbest-time-to-buy-and-sell-stock-ii%2F)
• 👉 [【LeetCode 直通车】：123 买卖股票的最佳时机 III（困难）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fbest-time-to-buy-and-sell-stock-iii%2F)
• 👉 [【LeetCode 直通车】：188 买卖股票的最佳时机IV（困难）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fcontainer-with-most-water%2F)
• 👉 [【LeetCode 直通车】：309 买卖股票的最佳时机含冷冻期（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fbest-time-to-buy-and-sell-stock-with-cooldown%2F)
• 👉 [【LeetCode 直通车】：714 买卖股票的最佳时机含手续费（中等）](https://link.juejin.cn/?target=https%3A%2F%2Fleetcode-cn.com%2Fproblems%2Fbest-time-to-buy-and-sell-stock-with-transaction-fee%2F)

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