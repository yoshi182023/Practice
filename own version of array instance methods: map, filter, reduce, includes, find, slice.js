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


Array.prototype.myReduce = function(cb, initialValue) {
  let accumulator;
    let start = 0; // Start index for the loop
    if (initialValue === undefined) { // If no initial value is provided
        accumulator = this[0]; // Set the accumulator to the first element
        start = 1; // Start the loop from the second element
    }
     if (arguments.length >= 2) {
    accumulator = initialValue; // 显式初始值
     }

    for (let i = start; i < this.length; i++) { // Loop through the array
        if (i in this) {

        accumulator = cb(accumulator, this[i], i, this); // Call the callback function on each element
    }
}
    return accumulator; // Return the accumulated value
};
console.log([1, 2, 3].myReduce((sum, n) => sum + n, 0)); // 6

console.log([1, , 3].myReduce((sum, n) => sum + n,10)); // 13
console.log([1, 2, 3].myReduce((sum, n) => sum + n)); // 6

Array.prototype.myIncludes = function(searchElement) {
  if (this == null) {
    throw new TypeError('Array.prototype.myIncludes called on null or undefined');
  }
for (let i = 0; i < this.length; i++) {
    if (i in this && (
      this[i] === searchElement ||
      (Number.isNaN(searchElement) && Number.isNaN(this[i]))
    )) {
      return true;
    }
  }
  return false;
};
  const arr = [1, 2, NaN, 'a'];
 console.log(arr.myIncludes(2));      // true
 console.log(arr.myIncludes(3));      // false
 console.log("myIncludesNaN",arr.myIncludes(NaN));    // true (原生includes的特殊行为)
 console.log(arr.includes(NaN))
console.log(arr.myIncludes('a', 3)); // true
// console.log(arr.myIncludes('a', 4)); // false
//   return false;
// };
const pets = ["cat", "dog", "bat"];
console.log(pets.myIncludes("cat"));
console.log([].includes(undefined))
console.log([].myIncludes(undefined))
console.log([].includes(3))
console.log([].myIncludes(3))




