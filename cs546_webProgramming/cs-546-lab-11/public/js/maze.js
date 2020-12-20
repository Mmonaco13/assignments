$(document).ready(() => {
    $.ajax({
        url: 'http://api.tvmaze.com/shows',
        method: 'GET',
        dataType: 'json'
    }).then((allShows) => {
        $('#showList').empty();
        $('#showList').show();
        $('#show').hide();
        $('#homeLink').hide();
        $('#error').hide();

        for (let x of allShows) {
            $('#showList').append(`<li><a class='showLink' href='${x._links.self.href}'>${x.name}</a></li>`);
        } 

        $('a.showLink').click((e) => {
            e.preventDefault();
            goToShow(e.target.href);
        });
    });

    $('#searchForm').submit((e) => {
        e.preventDefault();
        if ($('#search_term').val().trim().length === 0) {
            $('#showList').show();
            $('#show').hide();
            $('#homeLink').show();
            $('#error').show();

        } else {
            $.ajax({
                url: `http://api.tvmaze.com/search/shows?q=${$('#search_term').val().trim()}`,
                method: 'GET',
                dataType: 'json'
            }).then((shows) => {
                $('#showList').empty();
                $('#showList').show();
                $('#show').hide();
                $('#homeLink').show();
                $('#error').hide();

                for (let x of shows) {
                    $('#showList').append(`<li><a class='showLink' href='${x.show._links.self.href}'>${x.show.name}</a></li>`);
                }
                
                $('a.showLink').click((e) => {
                    e.preventDefault();
                    goToShow(e.target.href);
                });
            });
        }
    });

    function goToShow(link) {
        $.ajax({
            url: link,
            method: 'GET',
            dataType: 'json'
        }).then((show) => {
            $('#showList').hide();
            $('#show').empty();
            $('#show').show();
            $('#homeLink').show();
            $('#error').hide();
            let genres = '<li>NA</li>';
            if ((show.genres) && (show.genres.length !== 0)) {
                genres = '<ul>';
                for (let x of show.genres) {
                    genres = genres + `<li>${x}</li>`;
                }
                genres = genres + '</ul>';
            }

            let name     = 'NA';
            let language = 'NA';
            let img      = '/public/images/no_image.jpeg';
            let rating   = 'NA';
            let network  = 'NA';
            let summary  = 'NA';

            if (show.name)     name     = show.name;
            if (show.language) language = show.language;
            if (show.summary)  summary  = show.summary;
            if ((show.image)   && (show.image.medium))   img     = show.image.medium;
            if ((show.rating)  && (show.rating.average)) rating  = show.rating.average;
            if ((show.network) && (show.network.name))   network = show.network.name; 


            let res = `
                <h1>${name}</h1>
                <img alt="${name}" src="${img}">
                <dl>
                    <dt>Language</dt>
                    <dd>${language}</dd>
                    <dt>Genres</dt>
                    <dd>${genres}</dd>
                    <dt>Average Rating</dt>
                    <dd>${rating}</dd>
                    <dt>Network Name</dt>
                    <dd>${network}</dd>
                    <dt>Summary</dt>
                    <dd>${summary}</dd>
                </dl>`;

            $('#show').append(res);
        });
    }
});