SELECT
	hirfolyam.megnevezes,
    felhasznalo.veznev,
    felhasznalo.utonev,
    felhasznalo.email
FROM
	hirfolyam
INNER JOIN
	felhasznalo ON hirfolyam.moderator = felhasznalo.id;
