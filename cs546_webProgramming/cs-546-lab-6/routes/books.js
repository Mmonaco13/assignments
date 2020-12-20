const express = require('express');
const router = express.Router();
const data = require('../data');
const booksData = data.books;

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
    
    if ((typeof book.summary !== "string") || book.summary.length === 0) throw 'summary must be a nonempty string';

    return;
}

const isPartBook = function isPartBook(book) {
    if (typeof book !== "object") throw 'input was not an object';

    if (('title' in book) && ((typeof book.title !== "string") || book.title.length === 0)) throw 'title must be a nonempty string';

    if (('author' in book) && (typeof book.author !== "object")) throw 'author was not an object';
    if (('author' in book) && ((typeof book.author.authorFirstName !== "string") || book.author.authorFirstName.length === 0)) throw 'authorFirstName must be a nonempty string';
    if (('author' in book) && ((typeof book.author.authorLastName  !== "string") || book.author.authorLastName.length === 0)) throw 'authorLastName must be a nonempty string';

    if (('genre' in book) && ((!Array.isArray(book.genre)) || (book.genre.length === 0))) {
        throw 'genre must be a nonempty array';
    } else {
        if (typeof book.genre !== 'undefined') {
            for (let x of book.genre) {
                if((typeof x !== "string") || (x.length === 0)) throw 'genre must be a nonempty string';
            }
        }
    }

    if (('summary' in book) && ((typeof book.summary !== "string") || book.summary.length === 0)) throw 'summary must be a nonempty string';

    return;
}

router.get('/', async (req, res) => {
    try {
        let books = await booksData.readBook();
        let retArr = [];
        for (let x of books) {
            retArr.push({"_id": x._id, "title": x.title});
        }
        res.status(200).json(retArr);
    } catch(e) {
        console.log(e);
        res.status(404).json({message: 'not found'});
    }
});

router.post('/', async (req, res) => {
    let mydate;
    try {
        isBook(req.body);
        var parts =req.body.datePublished.split('/');
        mydate = new Date(parts[2], parts[0] - 1, parts[1]); 
    } catch(e) {
        res.status(400).json({message: e});
        return;
    }

    try {
        const {title, author, genre, datePublished, summary} = req.body;
        const newBook = await booksData.create(title, author, genre, mydate, summary);
        res.status(200).json(newBook);
    } catch(e) {
        console.log(e);
        res.status(404).json({message: e});
    }
});

router.get('/:id', async (req, res) => {
    try {
        if ((typeof req.params.id !== "string") || req.params.id.length === 0) throw 'id must be a nonempty string';
        const book = await booksData.readBook(req.params.id);
        res.status(200).json(book);
    } catch(e) {
        res.status(404).json({message: e});
    }
});

router.put('/:id', async (req, res) => {
    let mydate;
    try {
        isBook(req.body);
        var parts =req.body.datePublished.split('/');
        mydate = new Date(parts[2], parts[0] - 1, parts[1]); 
        if (mydate.getTime() !== mydate.getTime()) throw "improper date"; 
    } catch(e) {
        res.status(400).json({message: e});
        return;
    }

    try {
        if ((typeof req.params.id !== "string") || req.params.id.length === 0) throw 'id must be a nonempty string';
        const {title, author, genre, datePublished, summary} = req.body;
        const updatedBook = await booksData.update(req.params.id, title, author, genre, mydate, summary);
        res.status(200).json(updatedBook);
    } catch(e) {
        res.status(404).json({message: e});
    }
});

router.patch('/:id', async (req, res) => {
    let mydate;
    try {
        isPartBook(req.body);
        if (typeof req.body.datePublished === "string") {
            var parts =req.body.datePublished.split('/');
            mydate = new Date(parts[2], parts[0] - 1, parts[1]);
        } 
    } catch(e) {
        res.status(400).json({message: e});
        return;
    }

    try {
        if ((typeof req.params.id !== "string") || req.params.id.length === 0) throw 'id must be a nonempty string';
        const updatedBook = await booksData.update(req.params.id, req.body.title, req.body.author, req.body.genre, mydate, req.body.summary);
        res.status(200).json(updatedBook);
    } catch(e) {
        console.log(e);
        res.status(404).json({message: e});
    }
});

router.delete('/:id', async (req, res) => {
    
    try {
        if ((typeof req.params.id !== "string") || req.params.id.length === 0) throw 'id must be a nonempty string';
        const book = await booksData.delete(req.params.id);
        res.status(200).json({bookId: book, deleted: true});
    } catch(e) {
        res.status(404).json({message: e});
    }
});

module.exports = router;