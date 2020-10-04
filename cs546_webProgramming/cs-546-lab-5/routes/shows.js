const axios = require('axios');
const express = require('express');
const router = express.Router();

router.get("/", async (req, res) => {
    try {
        const {shows} = await axios.get('http://api.tvmaze.com/shows');
        res.json(shows);
    } catch (e) {
        res.status(404).json({message: 'not found!'});
    }
});

router.get("/:id", async (req, res) => {
    if ((typeof req.params.id !== 'number') || (req.params.id % 1 !== 0) || (req.params.id < 1)) throw 'id must be a positive whole number';

    try {
        const user = await axios.get('http://api.tvmaze.com/shows/' + req.params.id);
        res.json(user);
    } catch (e) {
        res.status(404).json({ message: 'not found!' });
    }
});

module.exports = router;