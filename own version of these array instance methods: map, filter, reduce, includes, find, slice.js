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
