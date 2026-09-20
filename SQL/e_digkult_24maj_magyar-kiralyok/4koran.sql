SELECT
	uralkodo.nev
FROM
	uralkodo
INNER JOIN
	hivatal ON uralkodo.azon = hivatal.uralkodo_az
WHERE
	hivatal.mettol < hivatal.koronazas;
