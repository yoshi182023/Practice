length = 10;//Since we declare length at a global level (i.e., at window level)  we can access it using this.length or window.length.
function func() {
	console.log(this.length);
}
var obj = {
  length: 5,
  thisFunc: function(func) {
    func();//When func is invoked, this (on line 3) will access length = 10 (declared globally) instead of length = 5, defined inside obj.
    arguments[0]();//当用 arguments[0]() 调用 func 时，func 的 this 会指向 arguments 对象（而不是 window 或 obj）。arguments 对象自带 length 属性，表示传入的参数个数。
  }
};
// We are passing it an argument, the function func, and an extra argument, the number 3.
obj.thisFunc(func, 3);
// We pass func to thisFunc at a global level, so the scope this of the function is window.
// thisFunc uses arguments[] to access the arguments we are passing into thisFunc. So arguments[0] returns the func function whereas arguments[1] returns 3. 
// 在 obj.thisFunc(func, 3) 中，传入了 2 个参数：
// func（函数）
// 3（数字）所以 arguments.length 是 2，而 this 指向 arguments，因此 this.length 就是 2。
const p = {
  greeting() {
    console.log(`hello from ${this.name}`);
  },
};
const person = {
  name: "alice",
  __proto__: p,
}; // person -> p

person.greeting();//hello from alice
console.log(person.greeting);//[Function: greeting]

console.log(person.__proto__ === p); // true
//person -> p 是原型链关系（proto chain）
// person 本身没有 greeting() 方法；
// 但它的原型 p 有这个方法；
// 所以调用 person.greeting() 的时候，JavaScript 会沿着原型链找到 p.greeting() 来执行。

const person2 = {
  name: "bob",
  greeting: "hello",//首先会在 person2 自己身上找这个属性；
// 发现 person2 自己就有 greeting: "hello"；
// 所以不会去原型链上找，也不会用到 p.greeting() 方法；
  __proto__: p,
};
// person2
//   ↓
// person2.__proto__ (即 p)
//   ↓
// Object.prototype
//   ↓
// null
console.log(person2.greeting);//hello
console.log(person2);

//class keyword is syntax sugar

//constructor function/ class

function Person(name) {
  this.name = name;

  // const p = {};
  // p.name = name;
  // p.__proto__ = Person;
  // return p
}
const p1 = new Person("alice");
console.log(p1);
//对于构造函数，人们惯例convention使用首字母大写方式来表示这是一个constructor构造函数.构造函数往往其use case是需要需要通过 new 关键字调用返回类似对象的场景，并且随后我们可以通过 instanceof 关键字来做实例类型检查的场景。
console.log(“======factory function====工厂函数 是一种手动创建并返回对象的方式，适用于不需要 prototype 继承的简单场景。”);
//function person(firstName, lastName, age) {
//   const person = {};
//   person.firstName = firstName;
//   person.lastName = lastName;
//   person.age = age;
//   return person;
// }
// factory function
function Person2(name) {
  const p = {};
  p.name = name;
  p.greeting = function () {
    console.log(`hello from ${this.name}`);
  };
  return p;
}
const p2 = Person2("bob");
console.log(p2);
//工厂函数是将返回一个新的object的任何不是类或者构造函数的函数。在js中，任何函数都能够返回一个object.如果我们不是通过new function()的方式来获得这个对象的，那么她就是一个factory工厂函数.

// class keyword
// abstraction, polymorphism, inheritance, encapsulation
// no abstraction in js
// inheritance, extends keyword
// no overloading in js: same method name, different arguments and implementation
// overriding: same method in child and parent class, but different implementation
// encapsulation: hiding information from the outside of the class

class Person3 {
  #age;// Private field declaration
  static count = 0;// Static property
  constructor(name, age) {
    this.name = name;// Public property
    this.#age = age; // Setting private field
    Person.count++; // Incrementing static counter
  }
  // Instance method
  greeting() {
    console.log(`hello from ${this.name}, age: ${this.#age}`);
  }

  // setter
  set age(newAge) {
    console.log("in age setter method");
    this.#age = newAge;
  }

  // getter
  get age() {
    console.log("in age getter method");
    return this.#age;
  }
}
const person11 = new Person3("张三", 30);
const person22 = new Person3("李四", 25);
console.log(Person2.count); // 2（已创建两个实例）
person11.greeting(); // 输出："hello from 张三, age: 30"
// 使用getter/setter
console.log(person11.age); // 先输出"正在执行age的getter方法"，然后返回30
person11.age = 31;    // 输出"正在执行age的setter方法"，更新age
console.log(person11.age); // 现在返回31
// 尝试访问私有字段
console.log(person11.name); // "张三"（公共属性可访问）
//console.log(person11.#age); // 报错SyntaxError: 私有字段必须在封闭类中声明


var employee = {
  
  name: 'Joe',
  age: 28,
  designation: 'developer',
  //function returning designation of the employee
  display() {
    return this.designation //using this to refer to the "employee" object
  }
}
//this will display the designation
console.log(employee.display())
// Here, the function display() was being used to get the value of the property designation. Another way to do this is by using the get keyword.

var employee = {
  
  name: 'Joe',
  age: 28,
  designation: 'developer',
  //function returning designation of the employee
  get display() {
    return this.designation //using this to refer to the "employee" object
  }
}
//this will display the designation
console.log(employee.display)

//Using get changes the way the function display() is called. It is now called in exactly the same way as how a property is called: employee.display, whereas without get, it is called as a function: employee.display().



var employee = {
  
  name: 'Joe',
  age: 28,
  designation: 'developer',
  //function setting the value of "designation" equal to the parameter being passed to the function
  setDesignation(desig) { 
    this.designation = desig
  }
}
//displaying the value of "designation" at start
console.log("Old designation was:",employee.designation)
//updating the value of designation
employee.setDesignation('engineer')
//  by calling setDesignation as a function and passing the parameter engineer to it. 
//displaying new value of designation
console.log("New designation is:",employee.designation)

var employee = {
  
  name: 'Joe',
  age: 28,
  designation: 'developer',
  //function setting designation of the employee
  set setDesignation(desig) {
    this.designation = desig //using this to refer to the "employee" object
  }
}
console.log("designation originally is:",employee.designation)
employee.setDesignation = 'engineer'
//when the set keyword is used, setDesignation sets the value of designation similarly to how any other property value would be set.
console.log("new designation is:",employee.designation)
