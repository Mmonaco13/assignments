const axios = require('axios');
const express = require('express');
const router = express.Router();

router.get('/:id', async (req, res) => {
    try {
        const show = await axios.get(`http://api.tvmaze.com/shows/${req.params.id}`);
        let parsedShow = show['data'];
        parsedShow.summary = parsedShow.summary.replace(/(<([^>]+)>)/gi, '');
        res.render('shows/shows', {'show': parsedShow, 'title': parsedShow.name});
    } catch (e) {
        res.status(404).render('shows/error', {errorMessage: 'show not found'});
        return;
    }
});

module.exports = router;