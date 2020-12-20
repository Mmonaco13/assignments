// Matthew Monaco
// I pledge my honor that I have abided by the Stevens Honor System.

const questionOne = function questionOne(arr) {
    if (typeof arr === 'undefined') {    
        return {};
    }else if (arr.length === 0) {
        return {};
    }

    let retObject = {};

    for (let num of arr) {
        if (num === 1) {
            retObject[num] = false;
        
        } else if (num === 2) {
            retObject[num] = true;
        
        } else {
            let isPrime = true;
            for (i = 2; i < num; i++) {
                if(num % i === 0) {
                    isPrime = false;
                    break;
                }
            }
            retObject[num] = isPrime;
        }
    }

    return retObject;
}

const questionTwo = function questionTwo(arr) { 
    if (typeof arr === 'undefined') {    
        return 0;
    }else if (arr.length === 0) {
        return 0;
    }

    let retNum = 0
    for (let num of arr) {
        retNum += Math.pow(num, 2);
    }

    retNum = Math.pow(retNum, 6);
    return Math.sqrt(retNum);
}

const questionThree = function questionThree(text) {
    let chars = {consonants: 0, vowels: 0, numbers: 0, spaces: 0, punctuation: 0, specialCharacters: 0};
    
    if (text.length === 0) {
        return chars;
    }

    text = text.toLowerCase();

    // Character Type Lists
    let consonants = ['b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'];
    let numbers = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'];
    let vowels = ['a', 'e', 'i', 'o', 'u'];
    let punctuation = ['.', '?', '"', '\'', ',', '-', '!', ':', ';', '(', ')', '–', '—', '[', ']', '/'];

    for (let char of text) {
        if (consonants.includes(char)) {
            chars.consonants++;
        }else if (vowels.includes(char)) {
            chars.vowels++;
        }else if (numbers.includes(char)) {
            chars.numbers++;
        }else if (char === ' ') {
            chars.spaces++;
        }else if (punctuation.includes(char)) {
            chars.punctuation++;
        }else {
            chars.specialCharacters++;
        }
    }

    return chars;
}

const questionFour = function questionFour(num1, num2, num3) {
    //Loan amount, interest rate (%), term
    let monthlyInterest = (num2 / 100) / 12;
    let numMonths = num3 * 12;
    let compoundInterest = Math.pow(1 + monthlyInterest, numMonths);
    let monthlyPayment = (num1 * monthlyInterest * compoundInterest) / (compoundInterest - 1);
    return Number(monthlyPayment.toFixed(2));
}

module.exports = {
    firstName: "MATTHEW", 
    lastName: "MONACO", 
    studentId: "10422822",
    questionOne,
    questionTwo,
    questionThree,
    questionFour
};