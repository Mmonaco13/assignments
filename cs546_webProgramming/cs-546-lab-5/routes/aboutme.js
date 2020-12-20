const express = require('express');
const router = express.Router();

router.get("/", async (req, res) => {
    try {
        const me = {'name': 'Matthew Monaco',
                    'cwid': '10422822',
                    'biography': "I was born October 13th, 1998 in Branchburg New Jersey. I am a fourth year student at Stevens Institute of Technology studying computer science. I will also be getting a masters degree in management.\nI enjoy watching soccer and football. My favorite number is 13. I have two siblings.",
                    'favoriteShows': ['friends', 'Game of Thrones', 'The Good Place']};
        res.json(me);
    } catch (e) {
        res.status(500).send();
    }
});

module.exports = router;