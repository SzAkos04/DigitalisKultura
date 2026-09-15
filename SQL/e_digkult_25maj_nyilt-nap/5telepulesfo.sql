SELECT
	diakok.telepules,
	COUNT(diakok.id) AS db
FROM
	diakok
GROUP BY
	diakok.telepules
ORDER BY
	db DESC;
