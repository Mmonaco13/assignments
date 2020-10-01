function mean(array) {
    if (!Array.isArray(array)) throw 'array is not proper type';
    if (array.length === 0)    throw 'array is empty';
    
    let mean = 0;
    for (let x of array) {
        if (typeof x !== 'number') throw 'array element not a number';
        mean += x;
    }

    return Math.round((mean / array.length) * 100) / 100;
}

function medianSquared(array) {
    if (!Array.isArray(array)) throw 'array is not proper type';
    if (array.length === 0)    throw 'array is empty';
    for (let x of array) {
        if (typeof x !== 'number') throw 'array element not a number';
    }

    array.sort(function(a, b){return a - b});
    if ((array.length % 2) == 0) {
        let diff = (array[array.length / 2] + array[(array.length / 2) - 1]) / 2;
        return Math.pow(diff, 2);
    } else {
        return Math.pow(array[Math.floor(array.length / 2)], 2);
    }
}

function maxElement(array) {
    if (!Array.isArray(array)) throw 'array is not proper type';
    if (array.length === 0)    throw 'array is empty';
    
    let maxValue = Number.MIN_SAFE_INTEGER;
    let maxIndex = 0;
    let curIndex = 0;
    for (let x of array) {
        if (typeof x !== 'number') throw 'array element not a number';
        if (x > maxValue) {
            maxValue = x;
            maxIndex = curIndex;
        }
        curIndex++;
    }
    let obj = {};
    obj[maxValue] = maxIndex;
    return obj;
}

function fill(end, value) {
    if (typeof end !== 'number') throw 'end is not a number';
    if (end < 1) throw 'end is not a number greater than 1';
    if (end % 1 != 0) throw 'end is not an integer';

    let array = [];
    let count = 0;

    if (typeof value === 'undefined') {
        while (count < end) {
            array.push(count);
            count++;
        }
    } else {
        while (count < end) {
            array.push(value);
            count++;
        }
    }
    return array;
}

function countRepeating(array) {
    if (!Array.isArray(array)) throw 'array is not proper type';
    let obj = {};
    let hasRepeats = false;
    for (let x of array) {
        if (x in obj) {
            hasRepeats = true;
            obj[x] = obj[x] + 1;
        } else {
            obj[x] = 1;
        }
    }

    for (let x of array) {
        if (obj[x] === 1){
            delete obj[x];
        }
    }

    return obj;
}

function isEqual(arrayOne, arrayTwo) {
    if (!Array.isArray(arrayOne)) throw 'arrayOne is not proper type';
    if (!Array.isArray(arrayTwo)) throw 'arrayTwo is not proper type';
    
    if (arrayOne.length !== arrayTwo.length) {
        return false;
    }
    
    if (arrayOne.length === 0) {
        return true;
    }

    arrayOne.sort();
    arrayTwo.sort();

    let isEq = true;
    for (let i in arrayOne) {
        let x = arrayOne[i];
        let y = arrayTwo[i];

        if (Array.isArray(x) && Array.isArray(y)) {
            isEq = isEqual(x, y); 
        } else if (Array.isArray(x) || Array.isArray(y)) {
            return false;
        } else if (typeof x !== typeof y) {
            return false;
        } else {
            isEq = (x === y);
        }

        if (!isEq) {
            return false;
        }
    }

    return true;
}

module.exports = {
    mean,
    medianSquared,
    maxElement,
    fill,
    countRepeating,
    isEqual
}