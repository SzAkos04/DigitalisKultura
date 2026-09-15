SELECT DISTINCT
	felhasznalo.veznev,
    felhasznalo.utonev
FROM
	felhasznalo
HAVING
	COUNT(*) > 1
ORDER BY
	felhasznalo.veznev ASC,
    felhasznalo.utonev ASC;
