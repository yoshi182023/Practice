function findFirstNonRepeatingCharacter(str ) {
  const charCount = {};

  for (const char of str) {
    charCount[char] = (charCount[char] ?? 0) + 1;
  }
  for (const char of str) {
    if (charCount[char] === 1) {
      return char;
    }
  }
  return undefined;
}
console.log(findFirstNonRepeatingCharacter('abacddbec'))

function bubbleSort(arr) {
  let swapped = false;

  while (!swapped) {
    swapped = true;
    for (let i = 0; i < arr.length; i++) {
      if (arr[i] > arr[i + 1]) {
        const temp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = temp;
        swapped = false;
      }
    }
  }
  return arr;
}

function LongestCountryName(countryNames){
     if (!countryNames || countryNames.length === 0) {
        return "";  
    }
    let longestName = countryNames[0];
    for (let i = 1; i < countryNames.length; i++) {
        if (countryNames[i].length > longestName.length) {
            longestName = countryNames[i];
        }
    }
    return longestName;
}



var lengthOfLongestSubstring = function(s) {
    let longestStringLength = 0;
    let left = 0;
    let currentStringSet = new Set();
    
    for (let right = 0; right < s.length; right++) {
        while (currentStringSet.has(s[right])) {
            currentStringSet.delete(s[left]);
            left++;
        }
        currentStringSet.add(s[right]);
        longestStringLength = Math.max(
            longestStringLength,
            right - left + 1
        );
    }
    
    return longestStringLength;
};

console.log(LongestCountryName(["Australia","Germany","United States of America"]))

var longestPalindrome = function(s) {
   let longest = "";
   function isPal (s,left,right){
       while(left >=0 && right < s.length && s[left] === s[right]){
            left--;
            right++;
       }//we don't want to include left value 
 //slice method is non-inclusive  so it doesn't include the current right value 
       return s.slice(left+1,right)
   }
   for(let i=0; i<s.length; i++){
      // for odd length strings 
      let oddPal = isPal(s,i,i);
      //for even strings 
      let evenPal = isPal(s,i,i+1);

      let longestPal = oddPal.length > evenPal.length? oddPal:evenPal;
      if(longestPal.length > longest.length){
          longest = longestPal;
      }
   }
   return longest; 
};

console.log(longestPalindrome("babad"))


// Function that will be passed as parameter
function greet(name) {
  return `Hello, ${name}!`;
}
console.log(greet('shuzi'))
// Function that accepts another function as parameter
function executeFunction(fn, parameter) {
  return fn(parameter);
}

// Passing the greet function as argument
const result = executeFunction(greet, "Alice");
console.log(result); // Output: "Hello, Alice!"

function getFunctionName(fn) {
  return fn.name;
}
function myCoolFunction() {
    return undefined
}

console.log(getFunctionName(myCoolFunction));  

function generateId(length) {
  const chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  let result = "";

  for (let i = 0; i < length; i++) {
    const randomIndex = Math.floor(Math.random() * chars.length);
    result += chars[randomIndex];
  }

  return result;
}

function removeDuplicateKeepFirst(str) {
  let result = "";
  const seen = new Set();
  for (const char of str) {
    if (!seen.has(char)) {
      seen.add(char);
      result += char;
    }
  }
  return result;
}
console.log(removeDuplicateKeepFirst("thequickbrownfoxjumpsoverthelazydog"))

function reverse(num){
 
  let numstring = num.toString().split("")
  console.log(numstring)//[ '3', '2', '2', '4', '3' ]
  return numstring.reverse().join("");
}



//  Write a JavaScript function that checks whether a passed string is palindrome or not?
// A palindrome is word, phrase, or sequence that reads the same backward as forward, e.g., madam or nurses run.
function isPalindrome(str) {
    // Use the replace method with a regular expression to remove any non-alphanumeric characters from the string. That way we can compare the string without worrying about spaces or punctuation, such as 'racecar' and 'race car'.
    const formattedStr = str.toLocaleLowerCase().replace(/[^a-z0-9]/g, '');
  const reversedStr = formattedStr.split('').reverse().join('');
  return formattedStr === reversedStr;
}
console.log(isPalindrome("nurses run"))


function stringCombinations(str) {
  let result = [];

  for (let i = 0; i < str.length; i++) {
    for (let j = i + 1; j <= str.length; j++) {
      const sub = str.slice(i, j);
      console.log(`slice(${i}, ${j}) = "${sub}"`);
      result.push(sub);
    }
  }

  return result;
}

console.log(stringCombinations("dog"));



