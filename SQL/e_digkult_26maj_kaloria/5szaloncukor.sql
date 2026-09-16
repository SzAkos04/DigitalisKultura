SELECT
	etkezes.datum
FROM
	fogyasztas
INNER JOIN
	etkezes ON fogyasztas.etkezesid = etkezes.id
INNER JOIN
	etel ON fogyasztas.etelid = etel.id
WHERE
	YEAR(etkezes.datum) = 2023
    AND MONTH(etkezes.datum) = 12
    AND etel.nev LIKE "%szaloncukor%"
GROUP BY
	etkezes.datum
ORDER BY
	etkezes.datum ASC
LIMIT 1 OFFSET 1;