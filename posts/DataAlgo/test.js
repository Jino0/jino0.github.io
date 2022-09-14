var generateParenthesis = function(n) {
    let validRes = [];
    backtrack(n * 2, validRes, '');
    return validRes;
};
function backtrack(len, validRes, bracket) {
    console.log(bracket);
    if (bracket.length === len) {
        if (isValidCombination(bracket)) {
            validRes.push(bracket);
        }
        return;
    }
    for (let str of ['(', ')']) {
        bracket += str;  // 一直走
        backtrack(len, validRes, bracket);  // 回溯
        bracket = bracket.slice(0, bracket.length - 1); // 回
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

generateParenthesis(3);