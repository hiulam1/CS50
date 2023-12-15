SELECT people.name FROM people
    JOIN stars AS kevinbacon ON kevinbacon.person_id = people.id
    JOIN movies ON movies.id = kevinbacon.movie_id
    WHERE people.name <> 'Kevin Bacon'
    AND movies.id IN (SELECT movies.id FROM movies
        JOIN stars AS kevinbacon ON kevinbacon.movie_id = movies.id
        JOIN people ON people.id = kevinbacon.person_id
        WHERE people.name = 'Kevin Bacon' AND people.birth = 1958);

