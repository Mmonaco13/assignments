const arrayUtils  = require("./arrayUtils");
const stringUtils = require("./stringUtils");
const objUtils    = require("./objUtils");

// mean Tests
try { const meanOne = arrayUtils.mean([10, 100, 1000]); // Returns 370
    if (meanOne === 370) {
        console.log('mean passed successfully');
    } else {
        console.error('mean failed test case: wrong return value');
    }
} catch (e) { console.error('mean failed test case ' + e); }

try { const meanOne = arrayUtils.mean([2, 3, 5]); // Returns 3.33
    if (meanOne === 3.33) {
        console.log('mean passed successfully');
    } else {
        console.error('mean failed test case: wrong return value');
    }
} catch (e) { console.error('mean failed test case ' + e); }

try { const meanOne = arrayUtils.mean(); // throws an error
    console.error('mean did not error');
} catch (e) { console.log('mean failed successfully ' + e); }

try { const meanOne = arrayUtils.mean(["guitar", 1, 3, "apple"]); // throws an error
    console.error('mean did not error');
} catch (e) { console.log('mean failed successfully ' + e); }

try { const meanOne = arrayUtils.mean([]) // throws an error
    console.error('mean did not error');
} catch (e) { console.log('mean failed successfully ' + e); }

try { const meanTwo = arrayUtils.mean('Hello'); // throws an error
    console.error('mean did not error');
} catch (e) { console.log('mean failed successfully ' + e); }

// medianSquared Tests
console.log();
try { const medianOne = arrayUtils.medianSquared([2, 3, 5]); // Returns 9
    if (medianOne === 9) {
        console.log('medianSquared passed successfully');
    } else {
        console.error('medianSquared failed test case: wrong return value');
    }
} catch (e) { console.log(e); console.error('medianSquared failed test case ' + e); }

try { const meanOne = arrayUtils.medianSquared([2, 3, 4, 6]); // Returns 12.25
    if (meanOne === 12.25) {
        console.log('medianSquared passed successfully');
    } else {
        console.error('medianSquared failed test case: wrong return value');
    }
} catch (e) { console.error('medianSquared failed test case ' + e); }

try { const meanTwo = arrayUtils.medianSquared([]); // throws an error
    console.error('medianSquared did not error');
} catch (e) { console.log('medianSquared failed successfully ' + e); }

try { const meanTwo = arrayUtils.medianSquared("test"); // throws an error
    console.error('medianSquared did not error');
} catch (e) { console.log('medianSquared failed successfully ' + e); }

try { const meanTwo = arrayUtils.medianSquared(1, 2, 3); // throws an error
    console.error('medianSquared did not error');
} catch (e) { console.log('medianSquared failed successfully ' + e); }

try { const meanTwo = arrayUtils.medianSquared(["guitar", 1, 3, "apple"]); // throws an error
    console.error('medianSquared did not error');
} catch (e) { console.log('medianSquared failed successfully ' + e); }

try { const meanTwo = arrayUtils.medianSquared(); // throws an error
    console.error('medianSquared did not error');
} catch (e) { console.log('medianSquared failed successfully ' + e); }

//medianSquared Tests
console.log();
try { const x = arrayUtils.maxElement([2, 3, 4, 6]); // Returns '6': 3
    let keys = Object.keys(x);
    if ((keys.length == 1) && (keys[0] = "6") && (x[keys[0]] == 3)) {
        console.log('maxElement passed successfully');
    } else {
        console.error('maxElement failed test case: wrong return value');
    }
} catch (e) { console.error('maxElement failed test case ' + e); }

try { const x = arrayUtils.maxElement([-2, -3, -4, -6]); // Returns -2
    let keys = Object.keys(x);
    if ((keys.length == 1) && (keys[0] = "-2") && (x[keys[0]] == 0)) {
        console.log('maxElement passed successfully');
    } else {
        console.error('maxElement failed test case: wrong return value');
    }
} catch (e) { console.error('maxElement failed test case ' + e); }

try { const x = arrayUtils.maxElement(50, 60, 70); // throws an error
    console.error('maxElement did not error');
} catch (e) { console.log('maxElement failed successfully ' + e); }

try { const x = arrayUtils.maxElement([]); // throws an error
    console.error('maxElement did not error');
} catch (e) { console.log('maxElement failed successfully ' + e); }

try { const x = arrayUtils.maxElement(); // throws an error
    console.error('maxElement did not error');
} catch (e) { console.log('maxElement failed successfully ' + e); }

try { const x = arrayUtils.maxElement("hello"); // throws an error
    console.error('maxElement did not error');
} catch (e) { console.log('maxElement failed successfully ' + e); }

try { const x = arrayUtils.maxElement([1, 2, "nope"]); // throws an error
    console.error('maxElement did not error');
} catch (e) { console.log('maxElement failed successfully ' + e); }

// fill Tests
console.log();
try { const x = arrayUtils.fill(3); // Returns [0, 1, 2]
    if ((Array.isArray(x)) && (x.length === 3) && (x[0] === 0) && (x[1] === 1) && (x[2] === 2)) {
        console.log('fill passed successfully');
    } else {
        console.error('fill failed test case: wrong return value');
    }
} catch (e) { console.error('fill failed test case ' + e); }

try { const x = arrayUtils.fill(1, 'Hey'); // Returns ['Hey']
    if ((Array.isArray(x)) && (x.length === 1) && (x[0] === 'Hey')) {
        console.log('fill passed successfully');
    } else {
        console.error('fill failed test case: wrong return value');
    }
} catch (e) { console.error('fill failed test case ' + e); }

try { const x = arrayUtils.fill(); // throws an error
    console.error('fill did not error');
} catch (e) { console.log('fill failed successfully ' + e); }

try { const x = arrayUtils.fill("test"); // throws an error
    console.error('fill did not error');
} catch (e) { console.log('fill failed successfully ' + e); }

try { const x = arrayUtils.fill(0); // throws an error
    console.error('fill did not error');
} catch (e) { console.log('fill failed successfully ' + e); }

try { const x = arrayUtils.fill(-4); // throws an error
    console.error('fill did not error');
} catch (e) { console.log('fill failed successfully ' + e); }

try { const x = arrayUtils.fill(3.7); // throws an error
    console.error('fill did not error');
} catch (e) { console.log('fill failed successfully ' + e); }

// countRepeating Tests
console.log();
try { const x = arrayUtils.countRepeating([]); // Returns {}
    let keys = Object.keys(x);
    if ((keys.length == 0)) {
        console.log('countRepeating passed successfully');
    } else {
        console.error('countRepeating failed test case: wrong return value');
    }
} catch (e) { console.error('countRepeating failed test case ' + e); }

try { const x = arrayUtils.countRepeating([7, '7', 13, true, true, true, "Hello","Hello", "hello"]); // Returns {"7": 2, true: 3, "Hello": 2}
    let keys = Object.keys(x);
    if ((keys.length == 3) && ('7' in x)     && (x['7'] === 2) &&
                              ('true' in x)  && (x['true'] === 3) &&
                              ('Hello' in x) && (x['Hello'] === 2)) {
        console.log('countRepeating passed successfully');
    } else {
        console.error('countRepeating failed test case: wrong return value');
    }
} catch (e) { console.error('countRepeating failed test case ' + e); }

try { const x = arrayUtils.countRepeating([1, 'hi there', true, 78]); // Returns {}
    let keys = Object.keys(x);
    if ((keys.length == 0)) {
        console.log('countRepeating passed successfully');
    } else {
        console.error('countRepeating failed test case: wrong return value');
    }
} catch (e) { console.error('countRepeating failed test case ' + e); }

try { const x = arrayUtils.countRepeating([7, '7']); // Returns {}
    let keys = Object.keys(x);
    if ((keys.length == 1) && ('7' in x) && (x[7] === 2)) {
        console.log('countRepeating passed successfully');
    } else {
        console.error('countRepeating failed test case: wrong return value');
    }
} catch (e) { console.error('countRepeating failed test case ' + e); }

try { const x = arrayUtils.countRepeating(); // throws an error
    console.error('countRepeating did not error');
} catch (e) { console.log('countRepeating failed successfully ' + e); }

try { const x = arrayUtils.countRepeating('Greetings'); // throws an error
    console.error('countRepeating did not error');
} catch (e) { console.log('countRepeating failed successfully ' + e); }

// isEqual Tests
console.log();
try { const x = arrayUtils.isEqual([1, 2, 3], [3, 1, 2]); // Returns true
    if (x === true) {
        console.log('isEqual passed successfully');
    } else {
        console.error('isEqual failed test case: wrong return value');
    }
} catch (e) { console.error('isEqual failed test case ' + e); }

try { const x = arrayUtils.isEqual([1, 2, 'a', 'b'], ['b', 1, 'a', 2]); // Returns true
    if (x === true) {
        console.log('isEqual passed successfully');
    } else {
        console.error('isEqual failed test case: wrong return value');
    }
} catch (e) { console.error('isEqual failed test case ' + e); }

try { const x = arrayUtils.isEqual([ 'Z', 'R', 'B', 'C', 'A' ], ['R', 'B', 'C', 'A', 'Z']); // Returns true 
    if (x === true) {
        console.log('isEqual passed successfully');
    } else {
        console.error('isEqual failed test case: wrong return value');
    }
} catch (e) { console.error('isEqual failed test case ' + e); }

try { const x = arrayUtils.isEqual([1, 2, 3], [4, 5, 6]); // Returns false 
    if (x === false) {
        console.log('isEqual passed successfully');
    } else {
        console.error('isEqual failed test case: wrong return value');
    }
} catch (e) { console.error('isEqual failed test case ' + e); }

try { const x = arrayUtils.isEqual([1, 3, 2], [1, 2, 3, 4]); // Returns false
    if (x === false) {
        console.log('isEqual passed successfully');
    } else {
        console.error('isEqual failed test case: wrong return value');
    }
} catch (e) { console.error('isEqual failed test case ' + e); }

try { const x = arrayUtils.isEqual([1, 2], [1, 2, 3]); // Returns false
    if (x === false) {
        console.log('isEqual passed successfully');
    } else {
        console.error('isEqual failed test case: wrong return value');
    }
} catch (e) { console.error('isEqual failed test case ' + e); }

try { const x = arrayUtils.isEqual([[ 4, 5, 6 ], [ 1, 2, 3 ], [ 7, 8, 9 ]], [[ 3, 1, 2 ], [ 5, 4, 6 ], [ 9, 7, 8 ]]); // Returns true
    if (x === true) {
        console.log('isEqual passed successfully');
    } else {
        console.error('isEqual failed test case: wrong return value');
    }
} catch (e) { console.error('isEqual failed test case ' + e); }

try { const x = arrayUtils.isEqual([[ 1, 2, 3 ], [ 4, 5, 6 ], [ 7, 8, 9 ]], [[ 3, 1, 2 ], [ 5, 4, 11 ], [ 9, 7, 8 ]]); // Returns false
    if (x === false) {
        console.log('isEqual passed successfully');
    } else {
        console.error('isEqual failed test case: wrong return value');
    }
} catch (e) { console.error('isEqual failed test case ' + e); }

try { const x = arrayUtils.isEqual([], []); // Returns true
    if (x === true) {
        console.log('isEqual passed successfully');
    } else {
        console.error('isEqual failed test case: wrong return value');
    }
} catch (e) { console.error('isEqual failed test case ' + e); }

try { const x = arrayUtils.isEqual([[], []], [[], []]); // Returns true
    if (x === true) {
        console.log('isEqual passed successfully');
    } else {
        console.error('isEqual failed test case: wrong return value');
    }
} catch (e) { console.error('isEqual failed test case ' + e); }

try { const x = arrayUtils.isEqual(); // throws an error
    console.error('isEqual did not error');
} catch (e) { console.log('isEqual failed successfully ' + e); }

try { const x = arrayUtils.isEqual([]); // throws an error
    console.error('isEqual did not error');
} catch (e) { console.log('isEqual failed successfully ' + e); }

try { const x = arrayUtils.isEqual('hello'); // throws an error
    console.error('isEqual did not error');
} catch (e) { console.log('isEqual failed successfully ' + e); }

try { const x = arrayUtils.isEqual([], 12); // throws an error
    console.error('isEqual did not error');
} catch (e) { console.log('isEqual failed successfully ' + e); }

try { const x = arrayUtils.isEqual('hello', 'hi'); // throws an error
    console.error('isEqual did not error');
} catch (e) { console.log('isEqual failed successfully ' + e); }


//stringUtils


//camelCase Tests
console.log();
try { const x = stringUtils.camelCase('my function is GREAT');
    if (x === 'myFunctionIsGreat') {
        console.log('camelCase passed successfully');
    } else {
        console.error('camelCase failed test case: wrong return value');
    }
} catch (e) { console.error('camelCase failed test case ' + e); }

try { const x = stringUtils.camelCase('LETS GO');
    if (x === 'letsGo') {
        console.log('camelCase passed successfully');
    } else {
        console.error('camelCase failed test case: wrong return value');
    }
} catch (e) { console.error('camelCase failed test case ' + e); }

try { const x = stringUtils.camelCase("How now brown cow");
    if (x === 'howNowBrownCow') {
        console.log('camelCase passed successfully');
    } else {
        console.error('camelCase failed test case: wrong return value');
    }
} catch (e) { console.error('camelCase failed test case ' + e); }

try { const x = stringUtils.camelCase("How 7ow brown c");
    if (x === 'how7owBrownC') {
        console.log('camelCase passed successfully');
    } else {
        console.error('camelCase failed test case: wrong return value');
    }
} catch (e) { console.error('camelCase failed test case ' + e); }

try { const x = stringUtils.camelCase(); // throws an error
    console.error('camelCase did not error');
} catch (e) { console.log('camelCase failed successfully ' + e); }

try { const x = stringUtils.camelCase(''); // throws an error
    console.error('camelCase did not error');
} catch (e) { console.log('camelCase failed successfully ' + e); }

try { const x = stringUtils.camelCase(123); // throws an error
    console.error('camelCase did not error');
} catch (e) { console.log('camelCase failed successfully ' + e); }

try { const x = stringUtils.camelCase(["Hello", "World"]); // throws an error
    console.error('camelCase did not error');
} catch (e) { console.log('camelCase failed successfully ' + e); }

//replaceChar Tests
console.log();
try { const x = stringUtils.replaceChar("Babby");
    if (x === 'Ba*$y') {
        console.log('replaceChar passed successfully');
    } else {
        console.error('replaceChar failed test case: wrong return value');
    }
} catch (e) { console.error('replaceChar failed test case ' + e); }

try { const x = stringUtils.replaceChar("moM");
    if (x === 'mo*') {
        console.log('replaceChar passed successfully');
    } else {
        console.error('replaceChar failed test case: wrong return value');
    }
} catch (e) { console.error('replaceChar failed test case ' + e); }

try { const x = stringUtils.replaceChar("Hello, How are you? I hope you are well");
    if (x === "Hello, *ow are you? I $ope you are well") {
        console.log('replaceChar passed successfully');
    } else {
        console.error('replaceChar failed test case: wrong return value');
    }
} catch (e) { console.error('replaceChar failed test case ' + e); }

try { const x = stringUtils.replaceChar("babbbbble");
    if (x === "ba*$*$*le") {
        console.log('replaceChar passed successfully');
    } else {
        console.error('replaceChar failed test case: wrong return value');
    }
} catch (e) { console.error('replaceChar failed test case ' + e); }

try { const x = stringUtils.replaceChar(''); // throws an error
    console.error('replaceChar did not error');
} catch (e) { console.log('replaceChar failed successfully ' + e); }

try { const x = stringUtils.replaceChar(123); // throws an error
    console.error('replaceChar did not error');
} catch (e) { console.log('replaceChar failed successfully ' + e); }

try { const x = stringUtils.replaceChar(); // throws an error
    console.error('replaceChar did not error');
} catch (e) { console.log('replaceChar failed successfully ' + e); }

//mashUp Tests
console.log();
try { const x = stringUtils.mashUp("Matthew", "Monaco");
    if (x === "Motthew Manaco") {
        console.log('mashUp passed successfully');
    } else {
        console.error('mashUp failed test case: wrong return value');
    }
} catch (e) { console.error('mashUp failed test case ' + e); }

try { const x = stringUtils.mashUp("Ma", "po");
    if (x === "po Ma") {
        console.log('mashUp passed successfully');
    } else {
        console.error('mashUp failed test case: wrong return value');
    }
} catch (e) { console.error('mashUp failed test case ' + e); }

try { const x = stringUtils.mashUp(); // throws an error
    console.error('mashUp did not error');
} catch (e) { console.log('mashUp failed successfully ' + e); }

try { const x = stringUtils.mashUp("h","e"); // throws an error
    console.error('mashUp did not error');
} catch (e) { console.log('mashUp failed successfully ' + e); }

try { const x = stringUtils.mashUp("h", "Hello"); // throws an error
    console.error('mashUp did not error');
} catch (e) { console.log('mashUp failed successfully ' + e); }

try { const x = stringUtils.mashUp("John"); // throws an error
    console.error('mashUp did not error');
} catch (e) { console.log('mashUp failed successfully ' + e); }

try { const x = stringUtils.mashUp("Patrick", ""); // throws an error
    console.error('mashUp did not error');
} catch (e) { console.log('mashUp failed successfully ' + e); }


// objUtils

//makeArrays Tests
console.log();
const first = { x: 5, y: 4 };
const second = { a: 76 };
const third = { x: 90, y: 39, q: 13 };

try { const x = objUtils.makeArrays([first, second]); // Returns [[x, 5], [y, 4], [a, 76]]
    if ((Array.isArray(x)) && (x.length === 3) && (Array.isArray(x[0])) && (x[0][0] === 'x') && (x[0][1] === 5) &&
                                                  (Array.isArray(x[1])) && (x[1][0] === 'y') && (x[1][1] === 4) &&
                                                  (Array.isArray(x[2])) && (x[2][0] === 'a') && (x[2][1] === 76)) {
        console.log('makeArrays passed successfully');
    } else {
        console.error('makeArrays failed test case: wrong return value');
    }
} catch (e) { console.error('makeArrays failed test case ' + e); }

try { const x = objUtils.makeArrays(); // throws an error
    console.error('makeArrays did not error');
} catch (e) { console.log('makeArrays failed successfully ' + e); }

try { const x = objUtils.makeArrays("hello"); // throws an error
    console.error('makeArrays did not error');
} catch (e) { console.log('makeArrays failed successfully ' + e); }

try { const x = objUtils.makeArrays([1, 2]); // throws an error
    console.error('makeArrays did not error');
} catch (e) { console.log('makeArrays failed successfully ' + e); }

try { const x = objUtils.makeArrays([first, second, {}]); // throws an error
    console.error('makeArrays did not error');
} catch (e) { console.log('makeArrays failed successfully ' + e); }

try { const x = objUtils.makeArrays(first); // throws an error
    console.error('makeArrays did not error');
} catch (e) { console.log('makeArrays failed successfully ' + e); }

// isDeepEqual Tests
console.log();
const firstDeep  = {a: 2, b: 3};
const secondDeep = {a: 2, b: 4};
const thirdDeep  = {a: 2, b: 3};
const forthDeep  = {a: {sA: "Hello", sB: "There", sC: "Class"}, b: 7, c: true, d: "Test"}
const fifthDeep  = {c: true, b: 7, d: "Test", a: {sB: "There", sC: "Class", sA: "Hello"}}

try { const x = objUtils.isDeepEqual({}, {});
    if (x === true) {
        console.log('isDeepEqual passed successfully');
    } else {
        console.error('isDeepEqual failed test case: wrong return value');
    }
} catch (e) { console.error('isDeepEqual failed test case ' + e); }

try { const x = objUtils.isDeepEqual(forthDeep, thirdDeep);
    if (x === false) {
        console.log('isDeepEqual passed successfully');
    } else {
        console.error('isDeepEqual failed test case: wrong return value');
    }
} catch (e) { console.error('isDeepEqual failed test case ' + e); }

try { const x = objUtils.isDeepEqual(forthDeep, fifthDeep);
    if (x === true) {
        console.log('isDeepEqual passed successfully');
    } else {
        console.error('isDeepEqual failed test case: wrong return value');
    }
} catch (e) { console.error('isDeepEqual failed test case ' + e); }

try { const x = objUtils.isDeepEqual(firstDeep, secondDeep);
    if (x === false) {
        console.log('isDeepEqual passed successfully');
    } else {
        console.error('isDeepEqual failed test case: wrong return value');
    }
} catch (e) { console.error('isDeepEqual failed test case ' + e); }

try { const x = objUtils.isDeepEqual(); // throws an error
    console.error('isDeepEqual did not error');
} catch (e) { console.log('isDeepEqual failed successfully ' + e); }

try { const x = objUtils.isDeepEqual('Hello', 'Hello'); // throws an error
    console.error('isDeepEqual did not error');
} catch (e) { console.log('isDeepEqual failed successfully ' + e); }

try { const x = objUtils.isDeepEqual({}); // throws an error
    console.error('isDeepEqual did not error');
} catch (e) { console.log('isDeepEqual failed successfully ' + e); }

try { const x = objUtils.isDeepEqual({}, 'Hello'); // throws an error
    console.error('isDeepEqual did not error');
} catch (e) { console.log('isDeepEqual failed successfully ' + e); }

// computeObject Tests
console.log();

try { const x = objUtils.computeObject({ a: 3, b: 7, c: 5 }, n => n * 2);
    let keys = Object.keys(x);
    if ((keys.length == 3) && ('a' in x) && (x['a'] === 6) &&
                              ('b' in x) && (x['b'] === 14) &&
                              ('c' in x) && (x['c'] === 10)) {    
        console.log('computeObject passed successfully');
    } else {
        console.error('computeObject failed test case: wrong return value');
    }
} catch (e) { console.error('computeObject failed test case ' + e); }

try { const x = objUtils.computeObject(); // throws an error
    console.error('computeObject did not error');
} catch (e) { console.log('computeObject failed successfully ' + e); }

try { const x = objUtils.computeObject("hello", "hello"); // throws an error
    console.error('computeObject did not error');
} catch (e) { console.log('computeObject failed successfully ' + e); }

try { const x = objUtils.computeObject({}, "hello"); // throws an error
    console.error('computeObject did not error');
} catch (e) { console.log('computeObject failed successfully ' + e); }

try { const x = objUtils.computeObject({}); // throws an error
    console.error('computeObject did not error');
} catch (e) { console.log('computeObject failed successfully ' + e); }

console.log(objUtils.isDeepEqual(null, null));