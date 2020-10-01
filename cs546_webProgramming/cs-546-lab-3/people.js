const axios = require('axios');

async function getPersonById(id) {
    const data = await axios.get('https://gist.githubusercontent.com/graffixnyc/31e9ef8b7d7caa742f56dc5f5649a57f/raw/43356c676c2cdc81f81ca77b2b7f7c5105b53d7f/people.json');
    let parsedData = data['data'];

    if (typeof id !== 'number') throw 'id is not a number';

    for (let x of parsedData) {
        if (x.id === id) {
            return x;
        }
    }

    throw 'No person with given id';
}

async function howManyPerState(stateAbbrv) {
    const data = await axios.get('https://gist.githubusercontent.com/graffixnyc/31e9ef8b7d7caa742f56dc5f5649a57f/raw/43356c676c2cdc81f81ca77b2b7f7c5105b53d7f/people.json');
    let parsedData = data['data'];

    if (typeof stateAbbrv !== 'string') throw 'stateAbbrv is not a string';

    let count = 0;
    for (let x of parsedData) {
        if (x.address.state === stateAbbrv) {
            count++;
        }
    }

    if (count === 0) throw 'no person lives in given state';
    return count;
}

async function personByAge(index) {
    const data = await axios.get('https://gist.githubusercontent.com/graffixnyc/31e9ef8b7d7caa742f56dc5f5649a57f/raw/43356c676c2cdc81f81ca77b2b7f7c5105b53d7f/people.json');
    let parsedData = data['data'];
    if (typeof index !== 'number') throw 'index is not a number';

    for (let x of parsedData) {
        x.dateType = new Date(x.date_of_birth);
    }
    parsedData.sort((a, b) => a.dateType - b.dateType);
    
    if (typeof parsedData[index] === 'undefined') throw 'invalid index';
    
    let ageDate = new Date(Date.now() - parsedData[index].dateType.getTime()); 
    parsedData[index].age = Math.abs(ageDate.getUTCFullYear() - 1970);
    delete parsedData[index].id;
    delete parsedData[index].ssn;
    delete parsedData[index].email;
    delete parsedData[index].ip_address;
    delete parsedData[index].address;
    delete parsedData[index].dateType;

    return parsedData[index];
}

async function peopleMetrics() {
    const data = await axios.get('https://gist.githubusercontent.com/graffixnyc/31e9ef8b7d7caa742f56dc5f5649a57f/raw/43356c676c2cdc81f81ca77b2b7f7c5105b53d7f/people.json');
    let parsedData = data['data'];
    
    let count = 0;
    let cityCount = {};
    let ageSum = 0;
    let obj = {'totalLetters': 0, 'totalVowels': 0, 'totalConsonants': 0, 'longestName': '', 'shortestName': '', 'mostRepeatingCity': '', 'averageAge': 0};

    for (let x of parsedData) {
        count++;
        let lowerFirst = x.first_name.toLowerCase();
        let lowerLast = x.last_name.toLowerCase(); 
        for (let y of lowerFirst) {
            if ((y === 'a') || (y === 'e') || (y === 'i') || (y === 'o') || (y === 'u')) {
                obj.totalVowels++;
            } else if ((y === 'b') || (y === 'c') || (y === 'd') || (y === 'f') || (y === 'g') || (y === 'h') || (y === 'j') || 
                       (y === 'k') || (y === 'l') || (y === 'm') || (y === 'n') || (y === 'p') || (y === 'q') || (y === 'r') || 
                       (y === 's') || (y === 't') || (y === 'v') || (y === 'w') || (y === 'x') || (y === 'y') || (y === 'z')) {
                obj.totalConsonants++;
            }
        }
        
        for (let y of lowerLast) {
            if ((y === 'a') || (y === 'e') || (y === 'i') || (y === 'o') || (y === 'u')) {
                obj.totalVowels++;
            } else if ((y === 'b') || (y === 'c') || (y === 'd') || (y === 'f') || (y === 'g') || (y === 'h') || (y === 'j') || 
                       (y === 'k') || (y === 'l') || (y === 'm') || (y === 'n') || (y === 'p') || (y === 'q') || (y === 'r') || 
                       (y === 's') || (y === 't') || (y === 'v') || (y === 'w') || (y === 'x') || (y === 'y') || (y === 'z')) {
                obj.totalConsonants++;
            }
        }

        if (x.first_name.length + x.last_name.length > obj.longestName.length) {
            obj.longestName = x.first_name + ' ' + x.last_name;
        }

        if ((x.first_name.length + x.last_name.length < obj.shortestName.length) || (obj.shortestName.length == 0)) {
            obj.shortestName = x.first_name + ' ' + x.last_name;
        }

        if (x.address.city in cityCount) {
            cityCount[x.address.city] += 1;
        } else {
            cityCount[x.address.city] = 1;
        }
        
        let dateType = new Date(x.date_of_birth);
        let ageDate = new Date(Date.now() - dateType.getTime()); 
        ageSum += Math.abs(ageDate.getUTCFullYear() - 1970);
    }
    
    obj.totalLetters = obj.totalConsonants + obj.totalVowels;

    obj.averageAge = ageSum / count;

    let most = 0;
    for (let z in cityCount) {
        if (cityCount[z] > most) {
            most = cityCount[z];
            obj.mostRepeatingCity = z;
        }
    }

    return obj;
}

module.exports = {
    getPersonById,
    howManyPerState,
    personByAge,
    peopleMetrics
}