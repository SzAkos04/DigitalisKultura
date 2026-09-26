SELECT
	film.cim,
    film.eredeti,
    szinkron.szinesz,
    szinkron.szerep
FROM
	film
INNER JOIN
	szinkron ON film.filmaz = szinkron.filmaz
WHERE
	szinkron.hang = "Anger Zsolt";