var merge = function (intervals) {
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