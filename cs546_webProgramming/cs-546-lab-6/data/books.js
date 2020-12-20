const mongoCollections = require('../config/mongoCollections');
const books = mongoCollections.books;
let { ObjectId } = require('mongodb');

const isBook = function isBook(book) {
    if (typeof book !== "object") throw 'input was not an object';
    
    if ((typeof book.title !== "string") || book.title.length === 0) throw 'title must be a nonempty string';

    if (typeof book.author !== "object") throw 'author was not an object';
    if ((typeof book.author.authorFirstName !== "string") || book.author.authorFirstName.length === 0) throw 'authorFirstName must be a nonempty string';
    if ((typeof book.author.authorLastName  !== "string") || book.author.authorLastName.length === 0) throw 'authorLastName must be a nonempty string';
    
    if ((!Array.isArray(book.genre)) || (book.genre.length === 0)) throw 'genre must be a nonempty array';
    for (let x of book.genre) {
        if((typeof x !== "string") || (x.length === 0)) throw 'genre must be a nonempty string';
    }
    
    if (!(book.datePublished instanceof Date)) throw 'datePublished must be a date';
    
    if ((typeof book.summary !== "string") || book.summary.length === 0) throw 'summary must be a nonempty string';

    return;
}

const isPartBook = function isPartBook(book) {
    if (typeof book !== "object") throw 'input was not an object';
    
    if ((typeof book.title !== 'undefined') && ((typeof book.title !== "string") || book.title.length === 0)) throw 'title must be a nonempty string';

    if ((typeof book.author !== 'undefined') && (typeof book.author !== "object")) throw 'author was not an object';
    if ((typeof book.author !== 'undefined') && ((typeof book.author.authorFirstName !== "string") || book.author.authorFirstName.length === 0)) throw 'authorFirstName must be a nonempty string';
    if ((typeof book.author !== 'undefined') && ((typeof book.author.authorLastName  !== "string") || book.author.authorLastName.length === 0)) throw 'authorLastName must be a nonempty string';
    
    if ((typeof book.genre !== 'undefined') && ((!Array.isArray(book.genre)) || (book.genre.length === 0))) {
        throw 'genre must be a nonempty array';
    } else if ((Array.isArray(book.genre))) {
        for (let x of book.genre) {
            if((typeof x !== "string") || (x.length === 0)) throw 'genre must be a nonempty string';
        }
    }

    if ((typeof book.datePublished !== 'undefined') && (!(book.datePublished instanceof Date))) throw 'datePublished must be a date';
    
    if ((typeof book.summary !== 'undefined') && ((typeof book.summary !== "string") || book.summary.length === 0)) throw 'summary must be a nonempty string';

    return;
}

module.exports = {

    async readBook(bookId) { 
        if (typeof bookId === "undefined") {
            const bookCollection = await books();
            const bookList = await bookCollection.find({}).toArray();
            if (!bookList) throw 'No books in system!';
            for (let x of bookList) {
                x._id = x._id.toString();
            }
            return bookList;
        } else {
            if ((typeof bookId !== 'string') || (bookId.trim().length === 0)) throw 'bookId is not a valid string';

            let parsedId = ObjectId(bookId);

            const bookCollection = await books();
            let book = await bookCollection.findOne({ _id: parsedId });
            if (book === null) throw 'No book with that id';
            book._id = book._id.toString();
            return book;
        }
    },

    async create(title, author, genre, datePublished, summary){
        let newBook = {title: title, author: author, genre: genre, datePublished: datePublished, summary: summary};
        isBook(newBook);
    
        const bookCollection = await books();
    
        newBook.reviews = [];

        const insertInfo = await bookCollection.insertOne(newBook);
        if (insertInfo.insertedCount === 0) throw 'Could not add book';
    
        const newId = insertInfo.insertedId;
    
        const book = await this.readBook(newId.toString());
        return book;
    },

    async update(id, title, author, genre, datePublished, summary, reviews) {
        let newBook = {title: title, author: author, genre: genre, datePublished: datePublished, summary: summary, reviews: reviews};
        isPartBook(newBook);

        if ((typeof id !== 'string') || (id.trim().length === 0)) throw 'id is not a valid string';

        let parsedId = ObjectId(id);
        
        const bookCollection = await books();
        const book = await this.readBook(id);
        let updatedBook = {};
        for (const x in book) {
            if (x !== "_id") {
                if (typeof newBook[x] !== "undefined") {
                    updatedBook[x] = newBook[x];
                } else {
                    updatedBook[x] = book[x];
                }
            }
        }
    
        const updatedInfo = await bookCollection.updateOne(
          { _id: parsedId },
          { $set: updatedBook }
        );
        if (updatedInfo.modifiedCount === 0) {
          throw 'could not update book successfully';
        }
    
        return await this.readBook(id);
    },

    async delete(id){
        if ((typeof id !== 'string') || (id.trim().length === 0)) throw 'id is not a valid string';
        
        let parsedId = ObjectId(id);
        
        const bookCollection = await books();
        const book = await this.readBook(id);

        for (let x of book.reviews) {
            await reviews.delete(x);
        }

        const deletionInfo = await bookCollection.deleteOne({ _id: parsedId });
        if (deletionInfo.deletedCount === 0) {
          throw `Could not delete book with id of ${id}`;
        }
        return id;
    }
};

const reviews = require('./reviews');