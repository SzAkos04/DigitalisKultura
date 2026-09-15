SELECT
	orak.datum,
    orak.terem,
    orak.orasorszam
FROM
	orak
WHERE
	orak.targy = "angol"
ORDER BY
	orak.datum ASC,
    orak.orasorszam ASC;
