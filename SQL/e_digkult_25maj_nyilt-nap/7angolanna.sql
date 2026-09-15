SELECT
	diakok.nev,
    diakok.email,
    diakok.telefon
FROM
	kapcsolo
INNER JOIN
	diakok ON kapcsolo.diakid = diakok.id
INNER JOIN
	orak ON kapcsolo.oraid = orak.id
WHERE
	orak.tanar = "Angol Anna"
    AND orak.datum = "2028-11-10";
