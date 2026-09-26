SELECT DISTINCT
	szinkron.hang,
    film.cim
FROM szinkron
INNER JOIN
	film ON szinkron.filmaz = film.filmaz
WHERE szinkron.filmaz IN
	(SELECT
        szinkron.filmaz
    FROM
        szinkron
    WHERE
        szinkron.hang = "Pap Kati")
    AND szinkron.hang <> "Pap Kati"
ORDER BY
	film.cim,
    szinkron.hang;