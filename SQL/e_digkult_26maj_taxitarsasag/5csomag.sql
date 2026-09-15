SELECT DISTINCT
	gepkocsi.sofor
FROM
	gepkocsi
INNER JOIN
	fuvar ON gepkocsi.rendszam = fuvar.rendszam
WHERE
	fuvar.mikor = "2025-10-12"
    AND fuvar.tav >= 10
    AND fuvar.tav <= 15
    AND
    	(fuvar.rendszam LIKE "%3%"
         OR fuvar.rendszam LIKE "%5%")
ORDER BY
	gepkocsi.sofor ASC;
