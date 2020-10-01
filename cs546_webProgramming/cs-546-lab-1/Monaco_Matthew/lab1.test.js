// Matthew Monaco
// I pledge my honor that I have abided by the Stevens Honor System.

const lab1 = require("./lab1");

/* Question 1: Prime Numbers */
console.log(lab1.questionOne([4, 5, 6]));           // {4: false, 5: true, 6: false}
console.log(lab1.questionOne([7, 11, 13]));         // {7: true, 11: true, 13: true} 
console.log(lab1.questionOne([4]));                 // {4: false} 
console.log(lab1.questionOne([23]));                // {23: true}
console.log(lab1.questionOne([9967, 9970, 9973]));  // {9967: true, 9970: false, 9973: true}

/* Question 2: Exponential Math */
console.log(lab1.questionTwo([1]));             // 1
console.log(lab1.questionTwo([1, 5, 10]));      // 2000376 
console.log(lab1.questionTwo([3, 3, 3]));       // 19683
console.log(lab1.questionTwo([1, 2, 3, 4]));    // 27000
console.log(lab1.questionTwo([15, 20]));        // 244140625

/* Question 3: String Decomposition */
console.log(lab1.questionThree("This loan calculator will help you determine the monthly payments on a loan.")); 
// {consonants: 40, vowels: 23, numbers: 0, spaces: 12, punctuation: 1, specialCharacters: 0}
console.log(lab1.questionThree("How : now : brown : cow!!!"));
// {consonants: 10, vowels: 4, numbers: 0, spaces: 6, punctuation: 6, specialCharacters: 0}
console.log(lab1.questionThree("What is your DTI, or debt-to-income ratio?"));
// {consonants: 18, vowels: 14, numbers: 0, spaces: 6, punctuation: 4, specialCharacters: 0}
console.log(lab1.questionThree("+*Should you take out a 15-year mortgage or a 30-year?*+")); 
// {consonants: 18, vowels: 18, numbers: 4, spaces: 9, punctuation: 3, specialCharacters: 4}
console.log(lab1.questionThree("5 + 4 > 5 + 6 = 11")); 
// {consonants: 0, vowels: 0, numbers:6, spaces: 8, punctuation: 0, specialCharacters: 4}

/* Question 4: Loan Payments */
console.log(lab1.questionFour(10000, 1.1, 5));  // 171.37
console.log(lab1.questionFour(20000, 12.2, 6)); // 393.09
console.log(lab1.questionFour(30000, 4, 30));   // 143.22
console.log(lab1.questionFour(40000, 8.3, 6));  // 707.20
console.log(lab1.questionFour(100000, 4.5, 2)); // 4364.78