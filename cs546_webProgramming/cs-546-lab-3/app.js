const people = require("./people");
const work   = require("./work");

async function main() {
    // getPersonById Tests
    try { const ret = await people.getPersonById(115);
        if (typeof ret === 'object' && (ret['id'] === 115) &&
            (ret['first_name'] === 'Kinsley') && (ret['last_name'] === 'Stode') && (ret['ssn'] === '513-92-6347')) {
            console.log('SUCCEED [getPersonById]');
        } else { console.log('FAIL [getPersonById]: wrong return value'); }
    } catch(e) { console.log('FAIL [getPersonById]: unexpected error: ' + e); }

    try { const ret = await people.getPersonById();
        console.log('FAIL [getPersonById]: expected an error');
    } catch(e) { console.log('SUCCEED [getPersonBYId]: error expected: ' + e); }

    try { const ret = await people.getPersonById(-1);
        console.log('FAIL [getPersonById]: expected an error');
    } catch(e) { console.log('SUCCEED [getPersonBYId]: error expected: ' + e); }

    try { const ret = await people.getPersonById(1001);
        console.log('FAIL [getPersonById]: expected an error');
    } catch(e) { console.log('SUCCEED [getPersonBYId]: error expected: ' + e); }

    try { const ret = await people.getPersonById(10.5);
        console.log('FAIL [getPersonById]: expected an error');
    } catch(e) { console.log('SUCCEED [getPersonBYId]: error expected: ' + e); }

    try { const ret = await people.getPersonById('hello');
        console.log('FAIL [getPersonById]: expected an error');
    } catch(e) { console.log('SUCCEED [getPersonBYId]: error expected: ' + e); }

    // howManyPerState Tests
    try { const ret = await people.howManyPerState("NY");
        if (ret === 64) {
            console.log('SUCCEED [howManyPerState]');
        } else { console.log('FAIL [howManyPerState]: wrong return value'); }
    } catch(e) { console.log('FAIL [howManyPerState]: unexpected error: ' + e); }

    try { const ret = await people.howManyPerState("CO");
        if (ret === 27) {
            console.log('SUCCEED [howManyPerState]');
        } else { console.log('FAIL [howManyPerState]: wrong return value'); }
    } catch(e) { console.log('FAIL [howManyPerState]: unexpected error: ' + e); }

    try { const ret = await people.howManyPerState();
        console.log('FAIL [howManyPerState]: expected an error');
    } catch(e) { console.log('SUCCEED [howManyPerState]: error expected: ' + e); }

    try { const ret = await people.howManyPerState(-1);
        console.log('FAIL [howManyPerState]: expected an error');
    } catch(e) { console.log('SUCCEED [howManyPerState]: error expected: ' + e); }

    try { const ret = await people.howManyPerState("WY");
        console.log('FAIL [howManyPerState]: expected an error');
    } catch(e) { console.log('SUCCEED [howManyPerState]: error expected: ' + e); }

    // personByAge Tests
    try { const ret = await people.personByAge(0);
        if (typeof ret === 'object' && (ret['age'] === 90) &&
            (ret['first_name'] === 'Chaim') && (ret['last_name'] === 'Giovannacci') && (ret['date_of_birth'] === '01/30/1930')) {
            console.log('SUCCEED [personByAge]');
        } else { console.log('FAIL [personByAge]: wrong return value'); }
    } catch(e) { console.log('FAIL [personByAge]: unexpected error: ' + e); }

    try { const ret = await people.personByAge(43);
        if (typeof ret === 'object' && (ret['age'] === 85) &&
            (ret['first_name'] === 'Chen') && (ret['last_name'] === 'Sowthcote') && (ret['date_of_birth'] === '10/01/1934')) {
            console.log('SUCCEED [personByAge]');
        } else { console.log('FAIL [personByAge]: wrong return value'); }
    } catch(e) { console.log('FAIL [personByAge]: unexpected error: ' + e); }

    try { const ret = await people.personByAge(500);
        if (typeof ret === 'object' && (ret['age'] === 46) &&
            (ret['first_name'] === 'Guglielmo') && (ret['last_name'] === 'Kubera') && (ret['date_of_birth'] === '05/07/1974')) {
            console.log('SUCCEED [personByAge]');
        } else { console.log('FAIL [personByAge]: wrong return value'); }
    } catch(e) { console.log('FAIL [personByAge]: unexpected error: ' + e); }

    try { const ret = await people.personByAge(999);
        if (typeof ret === 'object' && (ret['age'] === 0) &&
            (ret['first_name'] === 'Jacenta') && (ret['last_name'] === 'Gowrich') && (ret['date_of_birth'] === '08/21/2020')) {
            console.log('SUCCEED [personByAge]');
        } else { console.log('FAIL [personByAge]: wrong return value'); }
    } catch(e) { console.log('FAIL [personByAge]: unexpected error: ' + e); }

    try { const ret = await people.personByAge();
        console.log('FAIL [personByAge]: expected an error');
    } catch(e) { console.log('SUCCEED [personByAge]: error expected: ' + e); }

    try { const ret = await people.personByAge(-1);
        console.log('FAIL [personByAge]: expected an error');
    } catch(e) { console.log('SUCCEED [personByAge]: error expected: ' + e); }

    try { const ret = await people.personByAge(1001);
        console.log('FAIL [personByAge]: expected an error');
    } catch(e) { console.log('SUCCEED [personByAge]: error expected: ' + e); }

    try { const ret = await people.personByAge('hello');
        console.log('FAIL [personByAge]: expected an error');
    } catch(e) { console.log('SUCCEED [personByAge]: error expected: ' + e); }
    
    // peopleMetrics Test
    console.log(await people.peopleMetrics());


    // work.js


    // listEmployees Test
    console.log(await work.listEmployees());

    // fourOneOne Tests
    try { const ret = await work.fourOneOne("240-144-7553");
        if (typeof ret === 'object' && (ret.company_name === 'Kassulke, Towne and Davis') &&
            (ret.company_address.street_address === '1 Claremont Plaza') && (ret.company_address.city === 'Frederick') && 
            (ret.company_address.state === 'MD') && (ret.company_address.zip_code === '21705')) {
            console.log('SUCCEED [fourOneOne]');
        } else { console.log('FAIL [fourOneOne]: wrong return value'); }
    } catch(e) { console.log('FAIL [fourOneOne]: unexpected error: ' + e); }

    try { const ret = await work.fourOneOne();
        console.log('FAIL [fourOneOne]: expected an error');
    } catch(e) { console.log('SUCCEED [fourOneOne]: error expected: ' + e); }

    try { const ret = await work.fourOneOne(10);
        console.log('FAIL [fourOneOne]: expected an error');
    } catch(e) { console.log('SUCCEED [fourOneOne]: error expected: ' + e); }

    try { const ret = await work.fourOneOne('212-208-8374');
        console.log('FAIL [fourOneOne]: expected an error');
    } catch(e) { console.log('SUCCEED [fourOneOne]: error expected: ' + e); }

    try { const ret = await work.fourOneOne('1234567890');
        console.log('FAIL [fourOneOne]: expected an error');
    } catch(e) { console.log('SUCCEED [fourOneOne]: error expected: ' + e); }

    // whereDoTheyWork Tests
    try { const ret = await work.whereDoTheyWork("299-63-8866");
        if (ret === 'Marga Dawidowitsch works at Durgan LLC.') {
            console.log('SUCCEED [whereDoTheyWork]');
        } else { console.log('FAIL [whereDoTheyWork]: wrong return value'); }
    } catch(e) { console.log('FAIL [whereDoTheyWork]: unexpected error: ' + e); }

    try { const ret = await work.whereDoTheyWork("277-85-0056");
        if (ret === 'Toby Ginsie works at Hirthe, Adams and Reilly.') {
            console.log('SUCCEED [whereDoTheyWork]');
        } else { console.log('FAIL [whereDoTheyWork]: wrong return value'); }
    } catch(e) { console.log('FAIL [whereDoTheyWork]: unexpected error: ' + e); }

    try { const ret = await work.whereDoTheyWork();
        console.log('FAIL [whereDoTheyWork]: expected an error');
    } catch(e) { console.log('SUCCEED [whereDoTheyWork]: error expected: ' + e); }
    
    try { const ret = await work.whereDoTheyWork("123456789000");
        console.log('FAIL [whereDoTheyWork]: expected an error');
    } catch(e) { console.log('SUCCEED [whereDoTheyWork]: error expected: ' + e); }

    try { const ret = await work.whereDoTheyWork("264-67-0084");
        console.log('FAIL [whereDoTheyWork]: expected an error');
    } catch(e) { console.log('SUCCEED [whereDoTheyWork]: error expected: ' + e); }
}

main();