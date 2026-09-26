SELECT
	film.magyarszoveg,
    film.cim
FROM film
WHERE
    film.rendezo = "Christopher Nolan"
    AND film.studio = "Mafilm Audio Kft."
ORDER BY film.magyarszoveg;