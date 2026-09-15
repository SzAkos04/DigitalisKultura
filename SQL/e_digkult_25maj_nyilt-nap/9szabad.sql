SELECT
	orak.datum,
    orak.orasorszam,
    orak.targy,
    orak.tanar,
    (orak.ferohely - COUNT(diakok.id)) AS szabad
FROM
	orak
INNER JOIN
	kapcsolo ON orak.id = kapcsolo.oraid
INNER JOIN
	diakok ON kapcsolo.diakid = diakok.id
GROUP BY
	orak.id
ORDER BY
	szabad DESC;
