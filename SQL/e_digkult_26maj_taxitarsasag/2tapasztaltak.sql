SELECT
	gepkocsi.sofor,
    gepkocsi.rendszam,
    gepkocsi.engedely
FROM
	gepkocsi
WHERE
	gepkocsi.vizsga = 1;
