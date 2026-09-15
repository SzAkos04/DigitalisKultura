SELECT
	uzenet.tartalom
FROM
	uzenet
WHERE
	uzenet.tartalom LIKE "%bike%"
    OR uzenet.tartalom LIKE "%bicikli%";
