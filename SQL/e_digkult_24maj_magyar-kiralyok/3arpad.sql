SELECT
	uralkodo.nev,
    hivatal.mettol,
    hivatal.meddig
FROM uralkodo
INNER JOIN
	hivatal ON uralkodo.azon = hivatal.uralkodo_az
INNER JOIN
	uralkodohaz ON uralkodo.uhaz_az = uralkodohaz.azon
WHERE
	uralkodohaz.nev = "Árpád-ház"
ORDER BY
	hivatal.mettol,
    hivatal.meddig;
