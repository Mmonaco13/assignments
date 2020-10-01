function makeArrays(objects) {
    if (!Array.isArray(objects)) throw 'array is not proper type';
    if (objects.length < 2) throw 'array must have at least two elements';
    let ret = [];
    for (let x of objects) {
        if (!(x instanceof Object)) throw 'element is not an object';
        if (Object.keys(x).length === 0) throw 'object cannot be empty';

        for (let y in x) {
            let pair = [];
            pair.push(y);
            pair.push(x[y]);
            ret.push(pair);
        }
    }
    return ret;
}

function isDeepEqual(obj1, obj2) {
    if (!(obj1 instanceof Object)) throw 'element is not an object';
    if (!(obj2 instanceof Object)) throw 'element is not an object';

    let keys1 = Object.keys(obj1);
    let keys2 = Object.keys(obj2);
    let isEqual = true;

    if (keys1.length !== keys2.length) {
        return false;
    }

    for (x of keys1) {
        if ((obj1[x] instanceof Object) && (obj2[x] instanceof Object)) {
            isEqual = isDeepEqual(obj1[x], obj2[x]);
        } else if ((obj1[x] instanceof Object) || (obj2[x] instanceof Object)) {
            return false;
        } else {
            isEqual = (obj1[x] === obj2[x]);
        }
        if (!isEqual) {
            return false;
        }
    }
    return true;
}

function computeObject (object, func) {
    if (!(object instanceof Object)) throw 'element is not an object';
    if (!(func instanceof Function)) throw 'element is not a function';
    let retObj = {};
    let keys = Object.keys(object);

    for (x of keys) {
        retObj[x] = func(object[x]);
    }

    return retObj;
}

module.exports = {
    makeArrays,
    isDeepEqual,
    computeObject
}