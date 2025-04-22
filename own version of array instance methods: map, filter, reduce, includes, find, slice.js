const arr = ['abc', 'def', 'ghi'];

Array.prototype.myMap = function(callback, thisArg) {
  if (this == null) {
    throw new TypeError('Array.prototype.myMap called on null or undefined');
  }
  if (typeof callback !== 'function') {
    throw new TypeError(callback + ' is not a function');
  }
 
  const newArr = [];
  for (let i = 0; i < this.length; i++) {
    if (i in this) {
      newArr[i] = callback.call(thisArg, this[i], i, this);
    }
  }
  return newArr;
};

function makeUpperCase(str) {
  return str.toUpperCase();
}

// 测试1
console.log(arr.myMap(makeUpperCase)); // ['ABC', 'DEF', 'GHI']

// 测试2
['a', 'b'].myMap((char, i, arr) => console.log(char, i, arr));
// 输出:
// 'a', 0, ['a', 'b']
// 'b', 1, ['a', 'b']


Array.prototype.myFilter = function(callback, thisArg) {
 const filteredArr = [];
  for (let i = 0; i < this.length; i++) {
    if (i in this) {

      // 调用callback，传入当前元素、索引和原数组
      // 使用thisArg作为callback的this值
      if (callback.call(thisArg, this[i], i, this)) {
        filteredArr.push(this[i]);
      }
    }
  }
  return filteredArr;
}
const numbers = [1, 2, 3, 4, 5,6];
const evenNative = numbers.filter(x => x % 2 === 0);
console.log(evenNative); // [2, 4]
// 使用自定义myFilter
const evenCustom = numbers.myFilter(x => x % 2 === 0);
console.log(evenCustom); // [2, 4]


