SELECT film.ev, szinkron.hang
FROM film
INNER JOIN
	szinkron ON film.filmaz = szinkron.filmaz
WHERE
	film.studio <> "Mafilm Audio Kft."
    AND (film.ev, szinkron.hang) IN
    	(SELECT film.ev, szinkron.hang
        FROM film
        INNER JOIN
            szinkron ON film.filmaz = szinkron.filmaz
        WHERE
            film.studio = "Mafilm Audio Kft.");