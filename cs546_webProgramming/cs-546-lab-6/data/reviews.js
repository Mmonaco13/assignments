const mongoCollections = require('../config/mongoCollections');
const reviews = mongoCollections.reviews;
const booksm = require('./books');
let { ObjectId } = require('mongodb');

const isReview = function isReview(review) {
    if (typeof review !== "object") throw 'input was not an object';
    
    if ((typeof review.title !== "string") || review.title.length === 0) throw 'title must be a nonempty string';
    if ((typeof review.reviewer !== "string") || review.title.reviewer === 0) throw 'reviewer must be a nonempty string';
    if ((typeof review.bookBeingReviewed !== "string") || review.title.bookBeingReviewed === 0) throw 'bookBeingReviewed must be a nonempty string';
    if ((typeof review.rating !== "number") || (review.rating < 1) || (review.rating > 5) || (review.rating % 1 !== 0)) throw "rating must be a whole number from 1 to 10";
    if ((typeof review.review !== "string") || review.review.length === 0) throw 'review must be a nonempty string';

    return;
}

const exportedMethods = {
    async create(title, reviewer, bookBeingReviewed, rating, dateOfReview, review) {
        let newReview = {title: title, reviewer: reviewer, bookBeingReviewed: bookBeingReviewed, rating: rating, dateOfReview: dateOfReview, review: review};
        isReview(newReview);
    
        const reviewCollection = await reviews();

        const insertInfo = await reviewCollection.insertOne(newReview);
        if (insertInfo.insertedCount === 0) throw 'Could not add review';
    
        const newId = insertInfo.insertedId;
        const finreview = await this.read(newId.toString());

        const booke = await booksm.readBook(newReview.bookBeingReviewed);
        let reviewArr = booke.reviews;
        reviewArr.push(newId.toString());
        const updatedBook = await booksm.update(newReview.bookBeingReviewed, undefined, undefined, undefined, undefined, undefined, reviewArr);

        return finreview;
    },

    async read(reviewId){
        if (typeof reviewId === "undefined") {
            const reviewCollection = await reviews();
            const reviewList = await reviewCollection.find({}).toArray();
            for (let x of reviewList) {
                x._id = x._id.toString();
            }
            return reviewList;
        } else {
            if ((typeof reviewId !== 'string') || (reviewId.trim().length === 0)) throw 'reviewId is not a valid string';

            let parsedId = ObjectId(reviewId);
        
            const reviewCollection = await reviews();
            let review = await reviewCollection.findOne({ _id: parsedId });
            if (review === null) throw 'No review with that id';
            review._id = review._id.toString();
            return review;
        }
    },

    async delete(id){
        if ((typeof id !== 'string') || (id.trim().length === 0)) throw 'id is not a valid string';

        let parsedId = ObjectId(id);
        
        const reviewCollection = await reviews();
        const review = await this.read(id);

        const book = await booksm.readBook(review.bookBeingReviewed);
        let reviewArr = book.reviews;
        let index = reviewArr.indexOf(id);
        if (index > -1) reviewArr.splice(index, 1);
        const updatedBook = await booksm.update(review.bookBeingReviewed, undefined, undefined, undefined, undefined, undefined, reviewArr);
    
        const deletionInfo = await reviewCollection.deleteOne({ _id: parsedId });

        if (deletionInfo.deletedCount === 0) {
          throw `Could not delete review with id of ${id}`;
        }
        return; 
    }
};

module.exports = exportedMethods;