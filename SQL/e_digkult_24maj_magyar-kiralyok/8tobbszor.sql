SELECT
    uralkodo.nev,
    SUM(hivatal.meddig - hivatal.mettol + 1)
FROM
	uralkodo
INNER JOIN
	hivatal ON uralkodo.azon = hivatal.uralkodo_az
GROUP BY
	uralkodo.azon
HAVING
	COUNT(*) > 1;
