function camelCase(string) {
    if (typeof string !== 'string') throw 'str is not of proper type';
    if (string.length < 1) throw 'string cannot be empty';
    let res = (string.toLowerCase()).trim();
    
    while(res.search(' ') != -1) {
        let pos = res.search(' ');
        let char = res.charAt(pos + 1);
        if (pos + 2  >= res.length) {
            res = res.substring(0, pos) + char.toUpperCase();
        } else {
            res = res.substring(0, pos) + char.toUpperCase() + res.substring(pos + 2);
        }
    }
    return res;
}

function replaceChar(string) {
    if (typeof string !== 'string') throw 'str is not of proper type';
    if (string.length < 1) throw 'string cannot be empty';
    let lowerChar = string.charAt(0).toLowerCase();
    let upperChar = string.charAt(0).toUpperCase();
    let res = string;
    let star = true;

    let x;
    for (x = 1; x < string.length; x++) {
        if ((string.charAt(x) === lowerChar) || (string.charAt(x) === upperChar)) {
            if (x + 1 >= string.length) {
                if (star) {
                    res = res.substring(0, x) + '*';
                } else {
                    res = res.substring(0, x) + '$';
                }
            } else {
                if (star) {
                    res = res.substring(0, x) + '*' + res.substring(x + 1);
                } else {
                    res = res.substring(0, x) + '$' + res.substring(x + 1);
                }
            }
            star = !star;
        }
    }
    return res;
}
function mashUp(string1, string2) {
    if (typeof string1 !== 'string') throw 'str1 is not of proper type';
    if (string1.length < 2) throw 'str1 must be at least 2 character';
    if (typeof string2 !== 'string') throw 'str2 is not of proper type';
    if (string2.length < 2) throw 'str2 must be at least 2 character';
    let rem1 = "";
    let rem2 = ""
    
    if (string1.length > 2) rem1 = string1.substring(2);
    if (string2.length > 2) rem2 = string2.substring(2);

    return string2.substring(0, 2) + rem1 + ' ' + string1.substring(0, 2) + rem2;
}

module.exports= {
    camelCase,
    replaceChar,
    mashUp
}