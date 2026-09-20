SELECT
	uralkodohaz.nev,
	COUNT(*) AS uralkodok
FROM
	uralkodo
INNER JOIN
	uralkodohaz ON uralkodo.uhaz_az = uralkodohaz.azon
GROUP BY
	uralkodohaz.azon
ORDER BY
	uralkodok DESC;
