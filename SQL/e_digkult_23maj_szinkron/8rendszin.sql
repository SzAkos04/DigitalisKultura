SELECT DISTINCT film.rendezo AS "Színész-rendező"
FROM film
WHERE
	film.rendezo IN
    	(SELECT DISTINCT szinkron.szinesz FROM szinkron);