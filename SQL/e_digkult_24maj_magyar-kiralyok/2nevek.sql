SELECT
	uralkodo.nev,
    uralkodo.ragnev
FROM
	uralkodo
WHERE
	uralkodo.ragnev IS NOT NULL
ORDER BY
	uralkodo.szul;
