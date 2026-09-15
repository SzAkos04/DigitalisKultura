SELECT
	fuvar.mikor,
    SUM(fuvar.tav)
FROM
	fuvar
INNER JOIN
	gepkocsi ON fuvar.rendszam = gepkocsi.rendszam
WHERE
	gepkocsi.sofor = "Stofin Keve"
GROUP BY
	fuvar.mikor
ORDER BY
	SUM(fuvar.tav)
LIMIT 1;
