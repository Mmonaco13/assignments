
const searchRoutes = require('./search');
const showsRoutes = require('./shows');

const constructorMethod = (app) => {
  app.use('/search', searchRoutes);
  app.use('/shows', showsRoutes);

  app.use('*', (req, res) => {
    res.redirect('/search');
  });
};

module.exports = constructorMethod;