SELECT
	uzenet.kuldido
FROM
	uzenet
INNER JOIN
	felhasznalo ON uzenet.f_id = felhasznalo.id
WHERE
	felhasznalo.id IN
    	(SELECT
        	uzenet.f_id
        FROM
        	uzenet
        WHERE
        	uzenet.kuldido = (SELECT MIN(uzenet.kuldido) FROM uzenet)
        )
ORDER BY
	uzenet.kuldido DESC
LIMIT 1;
