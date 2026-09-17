SELECT DISTINCT
	egyesulet.orszag
FROM bajnok
INNER JOIN
	egyesulet ON bajnok.egyesulet_id = egyesulet.id
WHERE
	bajnok.ev > 2000;