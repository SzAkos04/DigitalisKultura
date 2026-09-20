SELECT DISTINCT
	szinhaz.nev
FROM
	eloadas
INNER JOIN szinhaz ON eloadas.szinhazid = szinhaz.id
WHERE
	szinhaz.id NOT IN
    	(SELECT
            szinhaz.id
        FROM
            eloadas
        INNER JOIN
            szinhaz ON eloadas.szinhazid = szinhaz.id
        WHERE
            szinhaz.szekhely = "Szeged"
            AND eloadas.mufaj = "operett")
    AND szinhaz.szekhely = "Szeged";
