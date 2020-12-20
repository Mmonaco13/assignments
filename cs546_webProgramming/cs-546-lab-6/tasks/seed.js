const dbConnection = require('../config/mongoConnection');
const data = require('../data/');
const b = data.books;
const r = data.reviews;

async function main() {
  const db = await dbConnection();
  await db.dropDatabase();

  let bookList = [];
  for (let i = 1; i < 10; i++){
    bookList[i] = await b.create("title" + i, {authorFirstName: "firstname" + i, authorLastName: "lastname" + i}, ["genre" + i], new Date(), "summary" + i); 
    for (let x = 1; x < 4; x++) {
      await r.create("title" + i + x, "reviewer" + i + x, bookList[i]._id, x, new Date(), "review" + i + x);
    }
  }

  console.log('Done seeding database');

  //await db.serverConfig.close();
}

main();