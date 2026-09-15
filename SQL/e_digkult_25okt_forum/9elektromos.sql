SELECT DISTINCT
	felhasznalo.veznev,
    felhasznalo.utonev
FROM
	uzenet
INNER JOIN
	felhasznalo ON uzenet.f_id = felhasznalo.id
INNER JOIN
	hirfolyam ON uzenet.h_id = hirfolyam.id
WHERE
	hirfolyam.megnevezes = "e-bike"
    AND uzenet.kuldido BETWEEN "12:00" AND "16:00";
