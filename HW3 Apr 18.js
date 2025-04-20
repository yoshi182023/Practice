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


console.log(LongestCountryName(["Australia","Germany","United States of America"]))
