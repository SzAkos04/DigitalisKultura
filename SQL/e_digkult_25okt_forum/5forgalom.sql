SELECT
	hirfolyam.megnevezes,
    COUNT(uzenet.id) AS "db"
FROM
	uzenet
INNER JOIN
	hirfolyam ON uzenet.h_id = hirfolyam.id
GROUP BY
	hirfolyam.megnevezes
ORDER BY
	db DESC;
