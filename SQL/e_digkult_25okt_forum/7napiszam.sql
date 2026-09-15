SELECT
	COUNT(DISTINCT felhasznalo.id)
FROM
	uzenet
INNER JOIN
	felhasznalo ON uzenet.f_id = felhasznalo.id;
