SELECT
	szinhaz.nev,
    COUNT(eloadas.id) AS szam
FROM
	eloadas
INNER JOIN
	szinhaz ON eloadas.szinhazid = szinhaz.id
GROUP BY
	szinhaz.id
HAVING
	szam >= 100;
