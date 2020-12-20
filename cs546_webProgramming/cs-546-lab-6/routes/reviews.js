const express = require('express');
const { books, reviews } = require('../config/mongoCollections');
const router = express.Router();
const data = require('../data');
const booksData = data.books;
const reviewsData = data.reviews;

const isReview = function isReview(review) {
    if (typeof review !== "object") throw 'input was not an object';
    
    if ((typeof review.title !== "string") || review.title.length === 0) throw 'title must be a nonempty string';
    if ((typeof review.reviewer !== "string") || review.title.reviewer === 0) throw 'reviewer must be a nonempty string';
    if ((typeof review.bookBeingReviewed !== "string") || review.title.bookBeingReviewed === 0) throw 'bookBeingReviewed must be a nonempty string';
    if ((typeof review.rating !== "number") || (review.rating < 1) || (review.rating > 5) || (review.rating % 1 !== 0)) throw "rating must be a whole number from 1 to 10";

    if ((typeof review.review !== "string") || review.review.length === 0) throw 'review must be a nonempty string';

    return;
}

router.get('/:bookId', async (req, res) => {
    try {
        if ((typeof req.params.bookId !== "string") || req.params.bookId.length === 0) throw 'bookId must be a nonempty string';
        const book = await booksData.readBook(req.params.bookId);
        res.status(200).json(book.reviews);
    } catch(e) {
        res.status(404).json({message: e});
    }
});

router.post('/:bookId', async (req, res) => {
    let mydate;
    try {
        isReview(req.body);
        var parts = req.body.dateOfReview.split('/');
        mydate = new Date(parts[2], parts[0] - 1, parts[1]);
        if (mydate.getTime() !== mydate.getTime()) throw "improper date"; 
    } catch(e) {
        res.status(400).json({message: e});
        return;
    }
    try {
        const {title, reviewer, bookBeingReviewed, rating, dateOfReview, review} = req.body;
        const newReview = await reviewsData.create(title, reviewer, bookBeingReviewed, rating, mydate, review);
        res.status(200).json(newReview);
    } catch(e) {
        res.status(400).json({message: 'not found'});
    }
});

router.get('/:bookId/:reviewId', async (req, res) => {
    try {
        if ((typeof req.params.reviewId !== "string") || req.params.reviewId.length === 0) throw 'reviewId must be a nonempty string';
        const review = await reviewsData.read(req.params.reviewId);
        if (req.params.reviewId !== review.bookBeingReviewed) throw "Specified book does not have specified review";
        res.status(200).json(review);
    } catch(e) {
        res.status(404).json({message: e});
    }
});

router.delete('/:bookId/:reviewId', async (req, res) => {
    try {
        if ((typeof req.params.reviewId !== "string") || req.params.reviewId.length === 0) throw 'reviewId must be a nonempty string';
        await reviewsData.delete(req.params.reviewId);
        res.status(200).json({reviewId: req.params.reviewId, deleted: true});
    } catch(e) {
        res.status(404).json({message: e});
    }
});

module.exports = router;