const mongoCollections = require('../config/mongoCollections');
const movies = mongoCollections.movies;
let { ObjectId } = require('mongodb');

module.exports = {
    async create(title, plot, rating, runtime, genre, cast, info) {
        if ((typeof title   !== 'string') || (title.trim().length   === 0)) throw 'title is not a valid string input';
        if ((typeof plot    !== 'string') || (plot.trim().length    === 0)) throw 'plot is not a valid string input';
        if ((typeof rating  !== 'string') || (rating.trim().length  === 0)) throw 'rating is not a valid string input';
        if ((typeof runtime !== 'string') || (runtime.trim().length === 0)) throw 'runtime is not a valid string input';
        if ((typeof genre   !== 'string') || (genre.trim().length   === 0)) throw 'genre is not a valid string input';
        if ((!Array.isArray(cast)) || (cast.length === 0)) throw "cast is not a non-empty array";

        for (let x of cast) {
            if ((typeof x !== 'string') || (x.trim().length === 0)) throw 'cast must only contain valid strings';
            x = x.trim();
        }

        if (!(info instanceof Object)) throw 'info is not an object';
        if ((typeof info.director !== 'string') || (info.director.trim().length === 0)) throw 'director is not a valid string';
        info.director = info.director.trim();
        if ((typeof info.yearReleased !== 'number') || (info.yearReleased.toString().length !== 4)) throw 'yearReleased is not a 4 digit number';
        let d = new Date();
        if ((info.yearReleased < 1930) || (info.yearReleased > d.getFullYear() + 5)) throw 'yearReleased is outside the timeframe allowed';

        const movieCollection = await movies();
        let newMovie = {
            title:   title.trim(),
            plot:    plot.trim(),
            rating:  rating.trim(),
            runtime: runtime.trim(),
            genre:   genre.trim(),
            cast:    cast,
            info:    info
        };

        const insertInfo = await movieCollection.insertOne(newMovie);
        if (insertInfo.insertedCount === 0) throw 'Could not add movie';

        const newId = insertInfo.insertedId;

        const movie = await this.get(newId.toString());
        return movie;
    },

    async getAll() {
        const movieCollection = await movies();
        const movieList = await movieCollection.find({}).toArray();
        for (let x of movieList) {
            x._id = x._id.toString();
        }
        return movieList;
    },

    async get(id) {
        if ((typeof id !== 'string') || (id.trim().length === 0)) throw 'id is not a valid string';

        let parsedId = ObjectId(id);

        const movieCollection = await movies();
        let movie = await movieCollection.findOne({ _id: parsedId });
        if (movie === null) throw 'No movie with that id';
        movie._id = movie._id.toString();
        return movie;
    },

    async remove(id) {
        if ((typeof id !== 'string') || (id.trim().length === 0)) throw 'id is not a valid string';

        let parsedId = ObjectId(id);

        const movieCollection = await movies();
        const movie = await this.get(id);
        const deletionInfo = await movieCollection.deleteOne({ _id: parsedId });
    
        if (deletionInfo.deletedCount === 0) {
          throw `Could not delete movie with id of ${id}`;
        }
        return `${movie.title} has been successfully deleted`;
    },
    
    async rename(id, newTitle) {
        if ((typeof id !== 'string') || (id.trim().length === 0)) throw 'id is not a valid string';

        let parsedId = ObjectId(id);

        if ((typeof newTitle !== 'string') || (newTitle.trim().length === 0)) throw 'newTitle is not a valid string input';
        
        const movieCollection = await movies();
        const movie = await this.get(id);
        const updatedMovie = {
          title:   newTitle.trim(),
          plot:    movie.plot,
          rating:  movie.rating,
          runtime: movie.runtime,
          genre:   movie.genre,
          cast:    movie.cast,
          info:    movie.info
        };
    
        const updatedInfo = await movieCollection.updateOne(
          { _id: parsedId },
          { $set: updatedMovie }
        );
        if (updatedInfo.modifiedCount === 0) {
          throw 'could not update movie successfully';
        }
    
        return await this.get(id);
    }
};