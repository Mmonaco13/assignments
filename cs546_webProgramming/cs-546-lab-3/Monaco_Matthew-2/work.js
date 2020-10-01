const axios = require('axios');

async function listEmployees() {
    const rawPeople = await axios.get('https://gist.githubusercontent.com/graffixnyc/31e9ef8b7d7caa742f56dc5f5649a57f/raw/43356c676c2cdc81f81ca77b2b7f7c5105b53d7f/people.json');
    let people = rawPeople['data'];
    
    const rawWork = await axios.get('https://gist.githubusercontent.com/graffixnyc/febcdd2ca91ddc685c163158ee126b4f/raw/c9494f59261f655a24019d3b94dab4db9346da6e/work.json');
    let work = rawWork['data'];
    
    let retArr = [];
    for (let company of work) {
        let companyObj = {'company_name': company.company_name, 'employees': []};
        for (let employee of people) {
            if (company.employees.includes(employee.id)) {
                let empObj = {'first_name': employee.first_name, 'last_name': employee.last_name}
                companyObj.employees.push(empObj);
            }
        }
        retArr.push(companyObj);
    }
    return retArr;
}

async function fourOneOne(phoneNumber) {
    if (typeof phoneNumber !== 'string') throw 'phoneNumber is not a string';

    let nums = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'];
    if ((phoneNumber.length !== 12) || 
            (!nums.includes(phoneNumber.charAt(0))) || (!nums.includes(phoneNumber.charAt(1)))  || (!nums.includes(phoneNumber.charAt(2))) || 
            (phoneNumber.charAt(3) !== '-')         || (!nums.includes(phoneNumber.charAt(4)))  || (!nums.includes(phoneNumber.charAt(5))) || 
            (!nums.includes(phoneNumber.charAt(6))) || (phoneNumber.charAt(7) !== '-')          || (!nums.includes(phoneNumber.charAt(8))) || 
            (!nums.includes(phoneNumber.charAt(9))) || (!nums.includes(phoneNumber.charAt(10))) || (!nums.includes(phoneNumber.charAt(11)))) {
        throw 'phoneNumber not in ###-###-#### format';
    }

    const rawWork = await axios.get('https://gist.githubusercontent.com/graffixnyc/febcdd2ca91ddc685c163158ee126b4f/raw/c9494f59261f655a24019d3b94dab4db9346da6e/work.json');
    let work = rawWork['data'];

    for (let company of work) {
        if (company.company_phone == phoneNumber) {
            return {'company_name': company.company_name, 'company_address': company.company_address};
        }
    }
    throw 'No company with given phone number';
}
async function whereDoTheyWork(ssn) {
    if (typeof ssn !== 'string') throw 'ssn is not a string';

    let nums = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'];
    if ((ssn.length !== 11)             || (!nums.includes(ssn.charAt(0))) || (!nums.includes(ssn.charAt(1)))  || 
        (!nums.includes(ssn.charAt(2))) || (ssn.charAt(3) !== '-')         || (!nums.includes(ssn.charAt(4)))  || 
        (!nums.includes(ssn.charAt(5))) || (ssn.charAt(6) !== '-')         || (!nums.includes(ssn.charAt(7)))  || 
        (!nums.includes(ssn.charAt(8))) || (!nums.includes(ssn.charAt(9))) || (!nums.includes(ssn.charAt(10)))) {
        throw 'ssn not in ###-##-#### format';
    }

    const rawPeople = await axios.get('https://gist.githubusercontent.com/graffixnyc/31e9ef8b7d7caa742f56dc5f5649a57f/raw/43356c676c2cdc81f81ca77b2b7f7c5105b53d7f/people.json');
    let people = rawPeople['data'];
    
    const rawWork = await axios.get('https://gist.githubusercontent.com/graffixnyc/febcdd2ca91ddc685c163158ee126b4f/raw/c9494f59261f655a24019d3b94dab4db9346da6e/work.json');
    let work = rawWork['data'];

    for (let x of people) {
        if (x.ssn === ssn) {
            for (let y of work) {
                if (y.employees.includes(x.id)) {
                    return `${x.first_name} ${x.last_name} works at ${y.company_name}.`;
                }
            }
        }
    }
    throw 'no one exists with that ssn';
}

module.exports = {
    listEmployees,
    fourOneOne,
    whereDoTheyWork
}