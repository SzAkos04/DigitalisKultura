SELECT
	AVG(tulajdonsag.ertek) / 60 AS "atlag hossz"
FROM
	eloadas
INNER JOIN
	tulajdonsag ON eloadas.id = tulajdonsag.eloadasid
WHERE
	eloadas.mufaj = "opera"
    AND tulajdonsag.nev = "perc";
