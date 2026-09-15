SELECT
	fuvar.mikor,
    SUM(IF(tipus='alkalmi', 1, gepkocsi.utasszam)) AS 'utasok száma'
FROM fuvar
INNER JOIN
	gepkocsi ON fuvar.rendszam = gepkocsi.rendszam
INNER JOIN
	tarifa ON fuvar.tarifaid = tarifa.id
WHERE sofor='Tari Norbert'
GROUP BY mikor;
