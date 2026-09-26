SELECT
	film.eredeti,
    film.cim,
	COUNT(szinkron.szerep) AS szerepek
FROM
	film
INNER JOIN
	szinkron ON film.filmaz = szinkron.filmaz
GROUP BY
	film.filmaz;