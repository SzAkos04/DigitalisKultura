SELECT DISTINCT
	eloadas.nyelv
FROM
	eloadas
WHERE
	eloadas.nyelv <> "magyar"
    AND eloadas.nyelv IS NOT NULL;
