SELECT
	szinhaz.nev,
    eloadas.datum,
    eloadas.mufaj
FROM eloadas
INNER JOIN
	szinhaz ON eloadas.szinhazid = szinhaz.id
WHERE
	eloadas.cim = "A kis herceg"
ORDER BY
	eloadas.datum;
