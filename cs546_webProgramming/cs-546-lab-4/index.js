const movies = require('./data/movies');
const connection = require('./config/mongoConnection');

const main = async () => {
    const theShining = await movies.create('The Shining',
            'A family heads to an isolated hotel for the winter where a sinister presence influences the father into violence, while his psychic son sees horrific forebodings from both past and future.',
            'R', '2h26m', 'Horror', ['Jack Nicholson', 'Shelley Duvall', 'Danny Lloyd'], {director: 'Stanley Kubrik', yearReleased: 1980});
    console.log(theShining);
  
    const shutterIsland = await movies.create('Shutter Island',
            'In 1954, a U.S. Marshal investigates the disappearance of a murderer who escaped from a hospital for the criminally insane.',
            'R', '2h19m', 'Thriller', ['Leonardo DiCaprio', 'Mark Ruffalo'], {director: 'Martin Scorsese', yearReleased: 2010});

    const allMovies = await movies.getAll();
    console.log(allMovies);
  
    const lastChristmas = await movies.create('Last Christmas',
            'A selfish woman meets a mysterious young man during the Christmas period who brings out the best in her. But is he too good to be true?',
            'PG-13', '1h43m', 'Comedy', ['Emilia Clarke', 'Henry Golding'], {director: 'Paul Feig', yearReleased: 2019});
    console.log(lastChristmas);

    const newShining = await movies.rename(theShining._id.toString(), 'REDRUM');
    console.log(newShining);

    const remMessage = await movies.remove(shutterIsland._id.toString());

    const allMovies2 = await movies.getAll();
    console.log(allMovies2);
  
    try {const ret =  await movies.create('', '', '', '', '', [], {});
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create(1, 1, 1, 1, 1, 1, 1);
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create('e', '', '', '', '', [], {});
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create('e', 'e', '', '', '', [], {});
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create('  ', '  ', '  ', '  ', '  ', [], {});
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create('e', 'e', 'e', 'e', 'e', 3, {});
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create('e', 'e', 'e', 'e', 'e', ['e'], {});
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create('e', 'e', 'e', 'e', 'e', ['e'], 4);
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create('e', 'e', 'e', 'e', 'e', ['  ', '', ' '], {});
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create('e', 'e', 'e', 'e', 'e', ['e'], {director: ''});
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create('e', 'e', 'e', 'e', 'e', ['e'], {director: ' '});
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create('e', 'e', 'e', 'e', 'e', ['e'], {director: 'e', yearReleased: 'e'});
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create('e', 'e', 'e', 'e', 'e', ['e'], {director: 'e', yearReleased: 123});
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create('e', 'e', 'e', 'e', 'e', ['e'], {director: 'e', yearReleased: 1234});
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create('e', 'e', 'e', 'e', 'e', ['e'], {director: 'e', yearReleased: 3000});
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create('e', 'e', 'e', 'e', 'e');
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create('e', 'e', 'e', 'e', 'e', ['e']);
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create('', '', '', '');
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.create();
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.remove('12345');
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.rename('12345', 'e');
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.remove('12345', 4);
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.remove(3, 'e');
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.remove('12345');
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    try {const ret =  await movies.get('12345');
        console.log('FAIL [create]: expected an error');
    } catch (e) { console.log('SUCCEED [create]: error expected: ' + e); }

    const db = await connection();
    await db.serverConfig.close();
  
    console.log('Done!');
  };
  
  main().catch((error) => {
    console.log(error);
  });