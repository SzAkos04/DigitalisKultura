SELECT
	orak.csoport,
    orak.targy,
    orak.datum
FROM
	orak
WHERE
	(orak.targy = "matematika"
    OR orak.targy = "fizika")
    AND orak.csoport LIKE "9%"
ORDER BY
	orak.targy;
