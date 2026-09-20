SELECT
	eloadas.cim,
    eloadas.datum
FROM
	eloadas
WHERE
	YEAR(eloadas.datum) = 2017
    AND eloadas.szinhazid IS NULL;
