const axios = require('axios');
const express = require('express');
const router = express.Router();

router.post('/', async (req, res) => {
    let userInfo = req.body;
    if ((!userInfo.searchTerm) || (userInfo.searchTerm.trim().length === 0)) {
        res.status(404).render('shows/error', {errorMessage: 'You must provide a valid search term'});
        return;
    }

    try {
        const shows = await axios.get('http://api.tvmaze.com/search/shows?q=' + userInfo.searchTerm);
        let parsedShows = shows['data'];
        if (parsedShows.length > 20) {
            parsedShows = parsedShows.slice(0, 20);
        }
        let hasShows = (parsedShows.length > 0);

        res.render('shows/search', {'shows': parsedShows, 'title': 'Shows Found', 'hasShows': hasShows, 'searchTerm': userInfo.searchTerm});
    } catch (e) {
        res.status(404).json({message: 'not found!'});
    }

});

router.get('/', async (req, res) => {
    res.render('shows/form', {'title': 'Show Finder'});
});

module.exports = router;