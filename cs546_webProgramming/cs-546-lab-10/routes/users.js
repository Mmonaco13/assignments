const express = require('express');
const router = express.Router();
const bcrypt = require('bcrypt');
const path = require('path');
const users = require('../userList.js');

router.get('/', async (req, res) => {
    if (req.session.user) {
        res.redirect('/private');
    } else {
        res.render('bits/form', {'hasError': false});
    }
});

router.post('/login', async (req, res) => {
    const {username, password} = req.body;
    let compObj = {};
    for (let x of users) {
        if (x.username === username) compObj = x;
    }
    try {
        let match = await bcrypt.compare(password, compObj.hashedPassword);
        if (match) {
            req.session.user = { 
                username: compObj.username,
                firstName: compObj.firstName,
                lastName: compObj.lastName, 
                profession: compObj.profession,
                bio: compObj.bio
            };
            res.redirect('/private');
        }
    } catch (e) {
        res.status(401).render('bits/form', {'hasError': true, 'error': 'Error: incorrect login credentials'})
    }
});

router.get('/private', async (req, res) => {
    res.render('bits/info', {'user': req.session.user});
});

router.get('/logout', async (req, res) => {
  req.session.destroy();
  res.sendFile(path.resolve('static/logout.html'));
});

module.exports = router;