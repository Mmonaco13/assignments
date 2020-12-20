const express = require('express');
const app = express();
const session = require('express-session');
const configRoutes = require('./routes');
const path = require('path');
const exphbs = require('express-handlebars');

app.use(express.json());
app.use(express.urlencoded({ extended: true }));

app.use(session({
    name: 'AuthCookie',
    secret: 'some secret string!',
    resave: false,
    saveUninitialized: true
}));

app.engine('handlebars', exphbs({ defaultLayout: 'main' }));
app.set('view engine', 'handlebars');

app.use('/private', (req, res, next) => {
    if (!req.session.user) {
      res.status(403).sendFile(path.resolve('static/error.html'));
    } else {
      next();
    }
});

app.use(async (req, res, next) => {
    const now = new Date();
    if (req.session.user) {
        console.log(now.toUTCString() + ": " + req.method + " " + req.originalUrl + " " + true);
    } else {
        console.log(now.toUTCString() + ": " + req.method + " " + req.originalUrl + " " + false);
    }
    next();
});

configRoutes(app);

app.listen(3000, () => {
  console.log("We've now got a server!");
  console.log('Your routes will be running on http://localhost:3000');
});