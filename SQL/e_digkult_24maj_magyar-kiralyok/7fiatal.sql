SELECT
	uralkodo.nev,
    hivatal.mettol - uralkodo.szul AS kor
FROM
	uralkodo
INNER JOIN
	hivatal ON uralkodo.azon = hivatal.uralkodo_az
WHERE
	hivatal.mettol - uralkodo.szul < 15
ORDER BY
	kor ASC;
