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
        } else if (Array.isArray(obj1[x]) && Array.isArray(obj2[x])) {
            if (obj1[x].length !== obj2[x].length) {
                return false;
            }
        
            if (obj1[x].length === 0) {
                return true;
            }
    
            obj1[x].sort();
            obj2[x].sort();
    
            let isEq = true;
                for (let i in obj1[x]) {
                    let z = obj1[x][i];
                    let y = obj2[x][i];
    
                    if (Array.isArray(z) && Array.isArray(y)) {
                        isEq = isEqual(z, y); 
                    } else if (Array.isArray(z) || Array.isArray(y)) {
                        return false;
                    } else if (typeof z !== typeof y) {
                        return false;
                    } else {
                    isEq = (z === y);
                    }
    
                    if (!isEq) {
                        return false;
                    }
                }
    
            return true;
        } else if (Array.isArray(obj1[x]) || Array.isArray(obj2[x])) {
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