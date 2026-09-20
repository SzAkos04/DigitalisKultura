SELECT
	uralkodo.nev,
	hivatal.meddig - hivatal.mettol + 1 AS hossz
FROM
	uralkodo
INNER JOIN
	hivatal ON uralkodo.azon = hivatal.uralkodo_az
GROUP BY
	hivatal.azon
ORDER BY
	hossz DESC
LIMIT 1;
