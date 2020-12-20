const axios = require('axios');
const express = require('express');
const router = express.Router();

router.get("/", async (req, res) => {
    try {
        const shows = await axios.get('http://api.tvmaze.com/shows');
        parsedShows = shows['data'];
        res.json(parsedShows);
    } catch (e) {
        res.status(404).json({message: 'not found!'});
    }
});

router.get("/:id", async (req, res) => {
    
    try {
        let nums = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'];
        let allZero = true;
        for (let x of req.params.id) {
            if (!nums.includes(x)) throw 'id must be a positive whole number';
            if (x !== '0') allZero = false;
        }
        if (allZero) throw 'id must be a positive whole number';
        
        const shows = await axios.get('http://api.tvmaze.com/shows/' + req.params.id);
        parsedShows = shows['data'];
        res.json(parsedShows);
    } catch (e) {
        res.status(404).json({ message: 'not found!' });
    }
});

module.exports = router;